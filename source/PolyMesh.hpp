/**
 * @file PolyMesh.hpp
 * @author Ian Prentice (iprentic@uwo.ca)
 * @brief A 3D mesh made up of Polygons
 * 
 */

#ifndef POLYMESH_H
#define POLYMESH_H

#include "Polygon.hpp"
#include <vector>

/**
 * @brief simple class that holds polygons and renders them
 * 
 */
class PolyMesh{
    protected:
        u32 polyFormat;
        std::vector<Polygon *> polyList;
    public:
        void renderMesh();
        void addPolygon(Polygon *p);
        /**
         * @brief returns the number of polygons in this mesh
         * 
         * @return int 
         */
        int numPolygons();
        u32 getFormat();
        PolyMesh(u32 pFmt);
        ~PolyMesh();
};


#endif