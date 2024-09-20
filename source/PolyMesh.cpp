/**
 * @file PolyMesh.cpp
 * @author Ian Prentice (iprentic@uwo.ca)
 * @brief Implementation of PolyMesh class
 * 
 */

#include "PolyMesh.hpp"

PolyMesh::PolyMesh(u32 pFmt): polyFormat{pFmt}{

}

void PolyMesh::addPolygon(Polygon *p){
    this->polyList.push_back(p);
}

void PolyMesh::renderMesh(){
    //ensure that the modelview stack is the current matrix stack
    glMatrixMode(GL_MODELVIEW);
    //create copy of current top matrix and push it onto stack
    // glPushMatrix();
    //set polygon rendering format
    glPolyFmt(this->polyFormat);
    for (auto p : this->polyList){
        p->drawPolygon();
    }
}

int PolyMesh::numPolygons(){
    return this->polyList.size();
}

PolyMesh::~PolyMesh(){
    //free all polygon pointers in this mesh
    for (auto p : this->polyList){
        delete p;
    }
}
u32 PolyMesh::getFormat(){
    return this->polyFormat;
}