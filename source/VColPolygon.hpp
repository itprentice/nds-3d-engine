/**
 * @file VColPolygon.hpp
 * @author Ian Prentice (iprentic@uwo.ca)
 * @brief header of VColPolygon type 
 * 
 */

#ifndef VCOLPOLYGON_H
#define VCOLPOLYGON_H

#include "Polygon.hpp"
#include <array>
/**
 * @brief Vertex Coloured Polygon type: polygon with a colour for each vertex
 * 
 */
class VColPolygon : public Polygon{
    protected:
        std::vector<std::array<uint8, 3>> rgb;
    public:
        /**
         * @brief Construct a new VColPolygon object
         * 
         * @param t 
         */
        VColPolygon(GL_GLBEGIN_ENUM t);
        /**
         * @brief adds a vertex with specified colour
         * 
         * @param v 
         * @param red 
         * @param green 
         * @param blue 
         * @return true 
         * @return false 
         */
        bool addVertex(Vertex v, uint8 red, uint8 green, uint8 blue);
        
        /**
         * @brief overrides basic vertex insertion to ensure colour vectors matchup to vertices
         * 
         * @param v 
         * @return true 
         * @return false 
         */
        bool addVertex(Vertex v) override;

        /**
         * @brief override 
         * 
         */
        void drawPolygon() override;
        Polygon *createCopy() override;

};

#endif