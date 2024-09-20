/**
 * @file GenUtils.cpp
 * @author Ian Prentice (iprentic@uwo.ca)
 * @brief implementation of classes under GenUtils header
 * 
 */

#include "GenUtils.hpp"

Vertex::Vertex(): x{0}, y{0}, z{0}{

}
Vertex::Vertex(float x, float y, float z){
    this->x = floattov16(x);
    this->y = floattov16(y);
    this->z = floattov16(z);
}

Vertex Vertex::operator+(Vertex const& rhs){
    Vertex ret(*this);
    ret.x += rhs.x;
    ret.y += rhs.y;
    ret.z += rhs.z;

    return ret;
}

Vertex Vertex::operator-(Vertex const& rhs){
    Vertex ret(*this);
    ret.x -= rhs.x;
    ret.y -= rhs.y;
    ret.z -= rhs.z;

    return ret;
}

Vertex Vertex::cross(Vertex const& rhs){
    Vertex ret;
    //calculate cross product (asssume all elements are already in fixed point v16 format)
    //leverage f32 fixed point math bc were already in v16 (4.12) fixed point, and f32 is 20.12, 
    //so f32 is a strict superset and its operations can take v16 params
    //tbh though normal integer multiplication would work fine in most cases, this just handles overflows more cleanly
    ret.x = f32tov16(mulf32(this->y, rhs.z) - mulf32(this->z, rhs.y));
    ret.y = f32tov16(mulf32(this->z, rhs.x) - mulf32(this->x, rhs.z));
    ret.z = f32tov16(mulf32(this->x, rhs.y) - mulf32(this->y, rhs.x));

    return ret;
}
int32 Vertex::magnitude(){
    return sqrtf32(mulf32(x, x) + mulf32(y, y) + mulf32(z, z));
}