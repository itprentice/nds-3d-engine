/**
 * @file BoundBox.cpp
 * @author Ian Prentice (iprentic@uwo.ca)
 * @brief implementation of BoundBox class
 * 
 */

#include "BoundBox.hpp"

BoundBox::BoundBox(v16 x, v16 y, v16 z, v16 height, v16 width, v16 depth): x{x}, y{y}, z{z}, height{height}, width{width}, depth{depth}{

}

BoundBox::BoundBox(float x, float y, float z, float height, float width, float depth){
    this->x = floattov16(x);
    this->y = floattov16(y);
    this->z = floattov16(z);
    this->height = floattov16(height);
    this->width = floattov16(width);
    this->depth = floattov16(depth);
}

bool BoundBox::checkBoxTest(){
    return (BoxTest(x, y, z, height, width, depth) != 0);
}