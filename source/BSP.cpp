/**
 * @file BSP.cpp
 * @author Ian Prentice (iprentic@uwo.ca)
 * @brief Implementation of Binary Space Partitioning
 * 
 */

#include "BSP.hpp"
#include <nds/arm9/postest.h>
#include <stdio.h>

//implement Plane class
Plane::Plane(){

}
Plane::Plane(Vertex p1, Vertex p2, Vertex p3){
    Vertex l1 = p2 - p1;
    Vertex l2 = p3 - p1;
    Vertex N = l1.cross(l2);
    this->A = N.x;
    this->B = N.y;
    this->C = N.z;

    //calculate D from Ax+By+Cz+D = 0 -> D = -Ax - By - Cz
    //leverage f32 fixed point math bc were already in v16 (4.12) fixed point, and f32 is 20.12, 
    //so f32 is a strict superset and its operations can take v16 params
    this->D = f32tov16(-mulf32(this->A, p1.x) - mulf32(this->B, p1.y) - mulf32(this->C, p1.z));
}

PlaneClasses Plane::classifyPoint(Vertex p){
    int32 pEquationResult = mulf32(this->A, p.x) + mulf32(this->B, p.y) + mulf32(this->C, p.z) + this->D;
    if (pEquationResult == 0){
        return pCoincident;
    }
    else if (pEquationResult > 0){
        return pFront;
    }
    else{
        return pBack;
    }
}

//implement Line class
Line::Line(Vertex p1, Vertex p2){
    this->l0 = p1;
    this->l1 = p2;
    this->l = p2-p1;
}
Vertex Line::intersectionPoint(const Plane &plane){
    int32 nDotL = mulf32(plane.A, this->l0.x) + mulf32(plane.B, this->l0.y) + mulf32(plane.C, this->l0.z);
    int32 t = divf32(nDotL + plane.D, nDotL - mulf32(plane.A, this->l1.x) - mulf32(plane.B, this->l1.y) - mulf32(plane.C, this->l1.z));
    Vertex intersection;
    intersection.x = f32tov16(l0.x + mulf32(l.x, t));
    intersection.y = f32tov16(l0.y + mulf32(l.y, t));
    intersection.z = f32tov16(l0.z + mulf32(l.z, t));

    return intersection;
}

//implement BSPNode class

//implementation inspired by pseudocode on the OpenGL BSP faq page: https://www.opengl.org/archives/resources/code/samples/bspfaq/index.html#7.txt
//assume the polygon pointers we receive will not be freed by anything else (ROUGH LOL)
void BSPNode::buildBSPTree(std::vector<Polygon *> plist){
    //only create copies when we are adding polygon to its final location (i.e. a BSPNode's coincidentList)
    Polygon *root = plist.back();
    plist.pop_back();
    this->mesh->addPolygon(root); //by definition, this polygon is coincident to the plane
    //all well-formed polygons have at least 3 vertices, use them to get the partitioning plane
    this->partition = Plane(root->vertices[0], root->vertices[1], root->vertices[2]);

    Polygon *current;
    std::vector<Polygon *> frontList, backList;
    while (!plist.empty()){
        current = plist.back();
        plist.pop_back();

        std::vector<Vertex> frontVertices, backVertices, coinVertices;
        for (auto v : current->vertices){
            switch (this->partition.classifyPoint(v)){
                case pCoincident:
                    coinVertices.push_back(v);
                    break;
                case pFront:
                    frontVertices.push_back(v);
                    break;
                case pBack:
                    backVertices.push_back(v);
                    break;
            }
        }
        //polygon is coincident in this plane
        if (coinVertices.size() == current->vertices.size()){
            this->mesh->addPolygon(current);
        }
        else if(frontVertices.size() == current->vertices.size()){
            frontList.push_back(current);
        }
        else if(backVertices.size() == current->vertices.size()){
            backList.push_back(current);
        }
        else if(!coinVertices.empty()){
            if (coinVertices.size() + frontVertices.size() == current->vertices.size()){
                frontList.push_back(current);
            }
            else if (coinVertices.size() + backVertices.size() == current->vertices.size()){
                backList.push_back(current);
            }
            //polygon gets split, there are some vertices on either side
            else{
                //quad with 2 points on plane, split into 2 triangles
                if (coinVertices.size() == 2){
                    frontVertices.insert(std::end(frontVertices), std::begin(coinVertices), std::end(coinVertices));
                    backVertices.insert(std::end(backVertices), std::begin(coinVertices), std::end(coinVertices));
                    
                    Polygon *fPoly = current->createCopy(), *bPoly = current->createCopy();
                    //replace both vertices lists with the new ones
                    fPoly->vertices = frontVertices;
                    bPoly->vertices = backVertices;
                    frontList.push_back(fPoly);
                    backList.push_back(bPoly);
                    delete current;
                }
                //must be one point on the plane, otherwise euclidian parallel geometry would be broken
                else{
                    //triangle, just find intersection of line between the 2 points not on the plane
                    if (current->vertices.size() == 3){
                        Line l1(frontVertices.back(), backVertices.back());
                        Vertex newp = l1.intersectionPoint(this->partition);

                        frontVertices.push_back(newp);
                        backVertices.push_back(newp);
                        
                        Polygon *fPoly = current->createCopy(), *bPoly = current->createCopy();
                        //replace both vertices lists with the new ones
                        fPoly->vertices = frontVertices;
                        bPoly->vertices = backVertices;

                        frontList.push_back(fPoly);
                        backList.push_back(bPoly);
                        delete current;
                    }
                    //must split up quad into a quad and a triangle
                    else if (current->vertices.size() == 4){
                        Line *l;
                        if (frontVertices.size() == 2){
                            int32 d1 = (frontVertices.front() - backVertices.back()).magnitude(), d2 = (frontVertices.back() - backVertices.back()).magnitude();
                            if (d1 < d2){
                                l = new Line(frontVertices.front(), backVertices.back());
                            }
                            else{
                                l = new Line(frontVertices.back(), backVertices.back());
                            }

                        }
                        else if (backVertices.size() == 2){
                            int32 d1 = (backVertices.front() - frontVertices.back()).magnitude(), d2 = (backVertices.back() - frontVertices.back()).magnitude();
                            if (d1 < d2){
                                l = new Line(backVertices.front(), frontVertices.back());
                            }
                            else{
                                l = new Line(backVertices.back(), frontVertices.back());
                            }
                        }
                        if (l != nullptr){
                            Vertex newp = l->intersectionPoint(this->partition);

                            //insert vertices that are on the plane
                            frontVertices.push_back(newp);
                            frontVertices.push_back(coinVertices.back());
                            backVertices.push_back(newp);
                            backVertices.push_back(coinVertices.back());

                            Polygon *fPoly = current->createCopy(), *bPoly = current->createCopy();
                            //replace both vertices lists with the new ones
                            fPoly->vertices = frontVertices;
                            bPoly->vertices = backVertices;

                            frontList.push_back(fPoly);
                            backList.push_back(bPoly);
                            delete current;
                        }
                    }
                }
            }
        }
        //plane cuts this polygon
        else{
            Line l1(frontVertices.front(), backVertices.back()), l2(frontVertices.back(), backVertices.front());
            Vertex newp1 = l1.intersectionPoint(this->partition), newp2 = l2.intersectionPoint(this->partition);

            frontVertices.push_back(newp1);
            frontVertices.push_back(newp2);
            backVertices.push_back(newp1);
            backVertices.push_back(newp2);

            Polygon *fPoly = current->createCopy(), *bPoly = current->createCopy();
            //replace both vertices lists with the new ones
            fPoly->vertices = frontVertices;
            bPoly->vertices = backVertices;

            frontList.push_back(fPoly);
            backList.push_back(bPoly);
            delete current;
        }
    }
    //recursive calls
    if (!frontList.empty()){
        this->front = new BSPNode(this->mesh->getFormat());
        this->front->parent = this;
        this->front->buildBSPTree(frontList);
    }
    if (!backList.empty()){
        this->back = new BSPNode(this->mesh->getFormat());
        this->back->parent = this;
        this->back->buildBSPTree(backList);
    }
}

int BSPNode::render(){
    int retVal = 0;
    if (this->isActive()){
        glPushMatrix();
        this->transform.doTransform();
        PosTest(0, 0, 0);
        // printf("%f, %f, %f\n", f32tofloat(PosTestXresult()), f32tofloat(PosTestYresult()), f32tofloat(PosTestZresult()));
        Vertex eye;
        eye.x = f32tov16(PosTestXresult());
        eye.y = f32tov16(PosTestYresult());
        eye.z = f32tov16(PosTestZresult());
        // printf("hello");
        switch(this->partition.classifyPoint(eye)){
            case pFront:{
                retVal += this->back->render();
                bool isVisible = true;
                if (this->box != nullptr){
                    isVisible = this->box->checkBoxTest();
                }
                if (this->mesh != nullptr && isVisible){
                    this->mesh->renderMesh();
                    retVal += this->mesh->numPolygons();
                }
                retVal += this->front->render();
                break;
            }
            case pBack:{
                retVal += this->front->render();
                bool isVisible = true;
                if (this->box != nullptr){
                    isVisible = this->box->checkBoxTest();
                }
                if (this->mesh != nullptr && isVisible){
                    this->mesh->renderMesh();
                    retVal += this->mesh->numPolygons();
                }
                retVal += this->back->render();
                break;
            }
            case pCoincident:{
                retVal += this->front->render();
                retVal += this->back->render();
                break;
            }

        }
        glPopMatrix(1);

    }
    return retVal;
}
BSPNode::BSPNode(u32 pFmt): GameObject{}{
    this->mesh = new PolyMesh(pFmt);
}