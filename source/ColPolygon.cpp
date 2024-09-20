/**
 * @file ColPolygon.cpp
 * @author Ian Prentice (iprentic@uwo.ca)
 * @brief implementation of derived ColPolygon class
 * 
 */
#include "ColPolygon.hpp"
#include <stdio.h>

ColPolygon::ColPolygon(GL_GLBEGIN_ENUM type, uint8 r, uint8 g, uint8 b): Polygon{type}, red{r}, green{g}, blue{b}{

}

void ColPolygon::setColour(uint8 r, uint8 g, uint8 b){
    this->red = r;
    this->green = g;
    this->blue = b;
}

void ColPolygon::drawPolygon(){
    if (isComplete()){
        glMatrixMode(GL_MODELVIEW);
        glBegin(this->type);

        glColor3b(this->red, this->green, this->blue);
        for(auto v : this->vertices){
            glVertex3v16(v.x, v.y, v.z);
        }

        glEnd();
        // printf("hello from col: %d\n", this->vertices.size());
    }
    //otherwise, do nothing
}

Polygon *ColPolygon::createCopy(){
    return new ColPolygon(*this);
}