/**
 * @file BoundBox.hpp
 * @author your name (you@domain.com)
 * @brief header of interface for BoundBox class
 * 
 */

#ifndef BOUNDBOX_H
#define BOUNDBOX_H

#include <nds.h>
/**
 * @brief BoundBox class for calls to BoxTest
 * (x, y, z) should be the top-left-front vertex of a box surrounding the object
 * measure from the center of the object
 * (i.e. box coords are relative to the current matrix translation and rotation transforms)
 * height, width, depth is measured from this top-left-front vertex
 */
class BoundBox{

    private:
        v16 x, y, z, height, width, depth;
    // float x, y, z, height, width, depth;
    public:
        /**
         * @brief Construct a new Bound Box object
         * 
         * @param x 
         * @param y 
         * @param z 
         * @param height 
         * @param width 
         * @param depth 
         */
        BoundBox(v16 x, v16 y, v16 z, v16 height, v16 width, v16 depth);

        /**
         * @brief Construct a new Bound Box object
         * converts float parameters to v16 (4 digits).(12 digits) fixed point decimal format
         * @param x 
         * @param y 
         * @param z 
         * @param height 
         * @param width 
         * @param depth 
         */
        BoundBox(float x, float y, float z, float height, float width, float depth);

        /**
         * @brief perform a box test on this bounding box
         * (xyz) should be the most negative vertex in the box. width, height, and depth are the dimensions
         * @return true if in view fustrum
         * @return false otherwise
         */
        bool checkBoxTest();

};

#endif