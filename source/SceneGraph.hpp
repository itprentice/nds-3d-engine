/**
 * @file SceneGraph.hpp
 * @author Ian Prentice (iprentic@uwo.ca)
 * @brief header interface for the SceneGraph class
 * This class holds GameObjects and renders them by traversing the tree (defined by parent/children) 
 */

#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#define MAX_POLYGON_COUNT 4000

#include "GameObject.hpp"

class SceneGraph{
    protected:
        static int globalPolyCount;
        int polygonCount;
    public:
        GameObject *root;

        /**
         * @brief walks through all objects in the tree (depth-first) and renders them
         */
        void dfsRender();
        /**
         * @brief helper function that does a standard OpenGL state machine initialization
         * must call glInit() before anything
         * 
         */
        static void debugGLConfig();
        /**
         * @brief small wrapper around glFlush to also update global polygon count
         * 
         * @param glFlushMode 
         */
        void renderFlush(u32 glFlushMode);
        // SceneGraph();
        // ~SceneGraph();
};

#endif