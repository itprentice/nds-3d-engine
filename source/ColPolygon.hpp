/**
 * @file ColPolygon.hpp
 * @author Ian Prentice (iprentic@uwo.ca)
 * @brief header interface for ColPolygon (Coloured Polygon) class.
 * 
 */

#ifndef COLPOLYGON_H
#define COLPOLYGON_H

#include "Polygon.hpp"
/**
 * @brief Coloured Polygon class. This is a polygon that has a single colour.
 * 
 */
class ColPolygon : public Polygon{
    protected:
        uint8 red;
        uint8 green;
        uint8 blue;
    public:
        /**
         * @brief Construct a new Col Polygon object
         * 
         * @param type 
         * @param red 
         * @param green 
         * @param blue 
         */
        ColPolygon(GL_GLBEGIN_ENUM type, uint8 red, uint8 green, uint8 blue);

        /**
         * @brief Set the colour of this polygon
         * 
         * @param red 
         * @param green 
         * @param blue 
         */
        void setColour (uint8 red, uint8 green, uint8 blue);

        /**
         * @brief inherited member function
         * 
         */
        void drawPolygon() override;

        Polygon *createCopy() override;

};

#endif