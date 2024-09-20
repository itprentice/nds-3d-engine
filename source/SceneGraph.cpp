/**
 * @file SceneGraph.cpp
 * @author Ian Prentice (iprentic@uwo.ca)
 * @brief implementation of the SceneGraph class
 * 
 */

#include "SceneGraph.hpp"
#include <deque>
#include <unordered_set>
#include <stdio.h>

int SceneGraph::globalPolyCount = 0;

void SceneGraph::debugGLConfig(){
    //================ setup ===============
    consoleDemoInit(); //debug console output on lower screen
    videoSetMode(MODE_5_3D);
    vramSetBankA(VRAM_A_TEXTURE);

    // glInit(); //must call before performing any gl operations
    //note: libnds opengl mostly acts like a state machine

    glEnable(GL_ANTIALIAS);
    glEnable(GL_TEXTURE_2D);
    //setup rear plane
    glClearColor(0, 0, 0, 31); //bg must be opaque for aa to work
    glClearPolyID(63); //bg needs unique polygon id for aa to work
    glClearDepth(GL_MAX_DEPTH);

    //setup camera
    glViewport(0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1);  //set camera viewport to nds screen dimensions
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //note: glu functions are for controlling/setting up the camera 
    //note: will start off using floating point functions, and then pivot to fixed point (integer) functions if performance becomes an issue
    //floating point functions all get their parameters converted to fixed point ints before calling the int version of the function, so this causes some performance overhead
    gluPerspective(70, SCREEN_WIDTH/SCREEN_HEIGHT, 0.1, 40);

    gluLookAt(0.0, 0.0, 1.0, //camera "eye" position
              0.0, 0.0, 0.0, //looking at this position
              0.0, 1.0, 0.0); //unit vector describing which direction is up for the camera
    //+ve y is up, +ve x is right, -ve z is into the plane
}

void SceneGraph::dfsRender(){
    std::deque<GameObject *> toBeRendered;
    std::unordered_set<GameObject *> completed;
    GameObject *current = nullptr;
    // int polygonCount = 0;
    glMatrixMode(GL_MODELVIEW);

    toBeRendered.push_back(root);

    while (!toBeRendered.empty()){
        current = toBeRendered.back();

        //if current has already been handled (i.e. current in completed set)
        if (completed.find(current) != completed.end()){
            glPopMatrix(1);
            toBeRendered.pop_back();
        }
        //handle current
        else{
            if (globalPolyCount + current->numPolygons() <= MAX_POLYGON_COUNT){
                glPushMatrix();
                int count = current->render();

                globalPolyCount += count;
                this->polygonCount += count;

                completed.insert(current);
                for (auto c : current->children){
                    toBeRendered.push_back(c);
                }
            }
            else{
                //never handle current and its children as it will exceed max polygons
                toBeRendered.pop_back();
            }
        }
    }
}

void SceneGraph::renderFlush(u32 glFlushMode){
    //tell opengl state machine to render current scene
    glFlush(glFlushMode);
    //reset instance and global polygon counters
    globalPolyCount -= this->polygonCount;
    this->polygonCount = 0;
}