/**
 * @file Polygon.hpp
 * @author Ian Prentice (iprentic@uwo.ca)
 * @brief header interface to polygons composed of vertices
 * 
 */

#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
//include this header to use nds opengl types 
//note: nds does not have floating point hardware, so try to use ints as much as possible
#include <nds.h>
#include "GenUtils.hpp"

/**
 * @brief Polygon abstract class defiining a simple polygon type consisting of individual vertices
 * 
 */
class Polygon{
    protected:
        std::vector<Vertex> vertices;
        /**
         * @brief the openGL mode to use for glBegin()
         * this determines how the vertices will be treated for rendering
         */
        GL_GLBEGIN_ENUM type;
        /**
         * @brief checks if polygon is complete by seeing if number of vertices matches
         * the amount that should be in this type of polygon
         * 
         * @return true 
         * @return false 
         */
        bool isComplete();
    public:
        /**
         * @brief renders each of the vertices according this this polygons type (glBegin mode)
         * only draws polygons if it has a complete set of vertices
         * pure virtual method to force implementation of this for each different type of polygon
         */
        virtual void drawPolygon() = 0;
        /**
         * @brief add a vertex to this polygon
         * 
         * @param v 
         * @return true when the vertex is added
         * @return false when the vertex isn't added
         */
        virtual bool addVertex(Vertex v);
        /**
         * @brief copy the vertices from another polygon
         * 
         * @param p is the polygon from which to copy the vertices
         * if p has more vertices than the capacity of this polygon, then only copy the first n vertices
         * if p has less vertices than the capacity of this polygon, then there will still be remaining vertex slots to fill
         */
        void copyVertices(const Polygon &p);
        /**
         * @brief return a dynamically allocated copy of this Polygon object
         * 
         * @return Polygon* 
         */
        virtual Polygon *createCopy() = 0;
        /**
         * @brief Construct a new Polygon object
         * 
         * @param type 
         */
        Polygon(GL_GLBEGIN_ENUM type);
        virtual ~Polygon();
        
        friend class BSPNode; //quick and dirty way to reveal vertices to BSPNode
};


#endif