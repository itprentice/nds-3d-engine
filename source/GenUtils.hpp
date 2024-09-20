/**
 * @file GenUtils.hpp
 * @author Ian Prentice (iprentic@uwo.ca)
 * @brief Header defining general purpose utils for the game engine
 * 
 */

#ifndef GENUTILS_H
#define GENUTILS_H

#include <nds.h> //for types
/**
 * @brief simple non-POD structure to hold x, y, z values for a vertex
 * use constructor to accept floats when defining vertex without having to use floating point opengl calls
 * 
 */
struct Vertex{
    v16 x;
    v16 y;
    v16 z;
    // Vertex(v16 x=0, v16 y=0, v16 z=0): x{x}, y{y}, z{z} {}
    Vertex(float x, float y, float z);
    Vertex();
    Vertex operator+(Vertex const& rhs);
    Vertex operator-(Vertex const& rhs);
    Vertex cross(Vertex const& rhs);
    int32 magnitude();
};

#endif