/**
 * @file Polygon.cpp
 * @author Ian Prentice (iprentic@uwo.ca)
 * @brief Implementation of the Polygon class
 */

#include "Polygon.hpp"

Polygon::Polygon(GL_GLBEGIN_ENUM type): type{type} {

}

Polygon::~Polygon(){
    
}

bool Polygon::addVertex(Vertex v){
    // if (isComplete()){
    //     return false;
    // }
    // else{
        this->vertices.push_back(v);
        return true;
    // }
}

// void Polygon::drawPolygon(){
//     if (isComplete()){
//         glMatrixMode(GL_MODELVIEW);
//         glBegin(this->type);

//         for (auto v : this->vertices){
//             glVertex3v16(v.x, v.y, v.z);
//         }

//         glEnd();
//     }
// }
bool Polygon::isComplete(){
    if ( (this->type == GL_TRIANGLE || this->type == GL_TRIANGLES) && this->vertices.size() < 3){
        return false; //did not add vertex as we already have the 3 vertices of a triangle polygon
    }
    else if ( (this->type == GL_QUAD || this->type == GL_QUADS) && this->vertices.size() < 4){
        return false; //did not add vertex as we already have the 4 vertices of a quad polygon
    }
    //otherwise, we are either a strip polygon and can have as many vertices as we want
    //or we still don't have the necessary 3 vertices
    else{
        return true;
    }
}
void Polygon::copyVertices(const Polygon &p){
    int n = 0, pSize = p.vertices.size();
    if (this->type == GL_TRIANGLE || this->type == GL_TRIANGLES){
        n = 3;
    }
    else if (this->type == GL_QUADS || this->type == GL_QUAD){
        n = 4;
    }
    //n is max between current polygon and the copy source (p.vertices.size <= n)
    n = (pSize > n) ? pSize : n;
    this->vertices = std::vector<Vertex>(n);
    for (int i = 0; i < pSize; i++){
        this->vertices[i] = p.vertices[i];
    }
}