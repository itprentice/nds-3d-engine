/**
 * @file VColPolygon.cpp
 * @author Ian Prentice (iprentic@uwo.ca)
 * @brief implementation of the VColPolygon class
 * 
 */

#include "VColPolygon.hpp"

VColPolygon::VColPolygon(GL_GLBEGIN_ENUM t): Polygon{t}{

}

bool VColPolygon::addVertex(Vertex v, uint8 r, uint8 g, uint8 b){
    if (this->isComplete()){
        return false;
    }
    else{
        this->vertices.push_back(v);
        this->rgb.push_back({r, g, b});
        return true;
    }
}

bool VColPolygon::addVertex(Vertex v){
    return this->addVertex(v, 0, 0, 0);
}

void VColPolygon::drawPolygon(){
    if (this->isComplete() && this->rgb.size() == this->vertices.size()){
        glMatrixMode(GL_MODELVIEW);
        glBegin(this->type);

        auto itV = this->vertices.begin();
        auto itC = this->rgb.begin();
        for (; itV != this->vertices.end() && itC != this->rgb.end(); itV++, itC++){
            glColor3b(itC->at(0), itC->at(1), itC->at(2));
            glVertex3v16(itV->x, itV->y, itV->z);
        }
        glEnd();
    }
}

Polygon *VColPolygon::createCopy(){
    return new VColPolygon(*this);
}