/**
 * @file Transform.cpp
 * @author Ian Prentice (iprentic@uwo.ca)
 * @brief implementation of Transform class
 * 
 */

#include "Transform.hpp"

Transform::Transform(){
    x = inttof32(0);
    y = inttof32(0);
    z = inttof32(0);

    xRotation = 0;
    yRotation = 0;
    zRotation = 0;
}
void Transform::translate(float x, float y, float z){
    //assume vertex vals have already been converted to v16 fixed point
    this->x += floattof32(x);
    this->y += floattof32(y);
    this->z += floattof32(z);
}

void Transform::rotate(float xDeg, float yDeg, float zDeg){
    xRotation += degreesToAngle(xDeg);
    yRotation += degreesToAngle(yDeg);
    zRotation += degreesToAngle(zDeg);
}

void Transform::doTransform(){
    //switch to modelview stack to properly apply matrix transformations
    glMatrixMode(GL_MODELVIEW);

    glTranslatef32(x, y, z);
    glRotateXi(xRotation);
    glRotateYi(yRotation);
    glRotateZi(zRotation);

}
Vertex Transform::getLocation(){
    return Vertex{this->x, this->y, this->z};
}