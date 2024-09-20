/**
 * @file Transform.hpp
 * @author Ian Prentice
 * @brief header describing interface for Transform class
 * 
 */

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "GenUtils.hpp"

class Transform{
    private:
        //f32 variables
        int x;
        int y;
        int z;

        //libnds Angle variables
        int xRotation;
        int yRotation;
        int zRotation;
    public:
        // Vertex getPositionVec();
        /**
         * @brief translate from current position by incrementing
         * 
         * @param x
         * @param y
         * @param z
         */
        void translate(float x, float y, float z);
        /**
         * @brief rotate from current rotation by incrementing
         * 
         * @param xDeg 
         * @param yDeg 
         * @param zDeg 
         */
        void rotate(float xDeg, float yDeg, float zDeg);

        /**
         * @brief performs the matrix operations specified by position and rotation vectors
         * 
         */
        void doTransform();

        Vertex getLocation();
        /**
         * @brief Construct a new Transform object
         * 
         */
        Transform();
};

#endif