/**
 * @file BSP.hpp
 * @author Ian Prentice
 * @brief header containing the declarations of the different classes involved for Binary Space Partitioning
 * 
 */

#ifndef BSP_H
#define BSP_H
#include "GenUtils.hpp"
#include "Polygon.hpp"
#include "GameObject.hpp"
#include <array>
#include <vector>

enum PlaneClasses{
    pCoincident,
    pFront,
    pBack
};
class Plane{
    friend class Line;
    protected:
        // std::array<Vertex, 3> planeVertices;
        v16 A, B, C, D; //plane coefficients for Ax + By + Cz + D = 0
    public:
        Plane(Vertex p1, Vertex p2, Vertex p3);
        Plane();
        PlaneClasses classifyPoint(Vertex p);
};
class Line{
    friend class Plane;
    protected:
        Vertex l0, l1, l;
    public:
        Line(Vertex p1, Vertex p2);
        Vertex intersectionPoint(const Plane &plane);
};

class BSPNode: public GameObject{
    protected:
        Plane partition;
        // Polygon *poly;
        // std::vector<Polygon *> coincidentList;
        BSPNode *front, *back;
        Vertex maxVertex();
        Vertex minVertex;
    public:
        void buildBSPTree(std::vector<Polygon *> plist);
        /**
         * @brief draw BSP tree using back to front tree traversal
         * 
         * @param eye 
         */
        int render() override;
        BSPNode(u32 pFmt);
};

#endif