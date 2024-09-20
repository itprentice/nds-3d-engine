/**
 * @file GameObject.hpp
 * @author Ian Prentice
 * @brief header describing interface of GameObject class
 * 
 */

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Transform.hpp"
#include "PolyMesh.hpp"
#include "BoundBox.hpp"
// #include "SceneGraph.hpp"
#include <vector>

class GameObject{
    friend class SceneGraph;
    protected:
        /**
         * @brief whether or not the game object is currently active
         * 
         */
        bool activeState;
        /**
         * @brief optional mesh for game object
         * 
         */
        PolyMesh *mesh;
        /**
         * @brief optional bounding box for game object
         * 
         */
        BoundBox *box;

        /**
         * @brief single parent of this game object
         * 
         */
        GameObject *parent;
        /**
         * @brief the children of this game object
         * 
         */
        std::vector<GameObject *> children;
    public:
        /**
         * @brief mandatory transform for every game object (describes position and rotation)
         * note: yes i know this is bad object oriented design, I just saw no point to setter/getter in this case, since I want the transform to be read/write exposed like in Unity
         */
        Transform transform;
        /**
         * @brief Construct a new Game Object object
         * 
         */
        GameObject();
        // ~GameObject();
        /**
         * @brief adds child to this game object and sets this as the child's parent
         * will only add child if it doesn't already have a parent
         * 
         * @param c 
         */
        void addChild(GameObject *c);
        /**
         * @brief renders game object by performing transforms and drawing mesh (if available)
         * checks if mesh is in view (if box is available) before drawing
         * only renders if the object is active
         * 
         * @return the number of polygons rendered
         */
        virtual int render();
        
        /**
         * @brief returns number of polygons in mesh (if there is a mesh)
         * 
         * @return int 
         */
        int numPolygons();

        //setters and getters (just to match unity behaviour, not the greatest object oriented design)
        /**
         * @brief Set the Mesh object
         * @param newMesh 
         */
        void setMesh(PolyMesh *newMesh);
        void setBox(BoundBox *box);    
        /**
         * @brief return whether or not this game object is enabled
         * note: GameObjects are enabled by default
         * @return true 
         * @return false 
         */
        bool isActive();
        /**
         * @brief enable game object (enabled by default)
         * 
         */
        void enable();
        /**
         * @brief disable game object (enabled by default)
         * 
         */
        void disable();
};

#endif