/**
 * @file main.cpp
 * @author Ian Prentice
 * @brief Sample of using engine
 * 
 */

#include <nds.h>
// #include <postest.h>
#include <nds/arm9/postest.h>
#include "PolyMesh.hpp"
#include "ColPolygon.hpp"
#include "TexPolygon.hpp"
#include "SceneGraph.hpp"

#include "whistle.h"
#include <stdio.h>
#include "BSP.hpp"

int doublePyramidScene(){
    glInit(); //initialize OpenGL state machine
    SceneGraph::debugGLConfig(); //debug gl setup configuration

    //============== texture ==============
    int whistleTextureID;
    glGenTextures(1, &whistleTextureID); //allocates texture space

    //binding this texture id as the current one in the state machine
    glBindTexture(0, whistleTextureID);
    //loads texture image into memory allocated for whistleTextureID
    glTexImage2D(0, 0, GL_RGBA, TEXTURE_SIZE_128, TEXTURE_SIZE_128, 0, TEXGEN_TEXCOORD, (u8 *) whistleBitmap);

    //=============== polygons =================
    u32 polyFormat = POLY_ALPHA(31) | POLY_CULL_NONE;

    //set of vertices for a pyramid
    Vertex vSet[5];
    vSet[0] = {1, 0, 1};
    vSet[1] = {-1, 0, 1};
    vSet[2] = {-1, 0, -1};
    vSet[3] = {1, 0, -1};
    vSet[4] = {0, 2, 0};

    //define textured pyramid and add polygons to it
    PolyMesh texPyramidMesh(polyFormat);
    //add square as base of pyramid
    TexPolygon *tempTex = new TexPolygon(GL_QUADS, whistleTextureID);

    //define coloured pyramid and add polygons to it
    PolyMesh colPyramidMesh(polyFormat);
    ColPolygon *tempCol = new ColPolygon(GL_QUADS, 255, 255, 0);

    tempTex->addCoordinate(0, 0);
    tempTex->addCoordinate(128, 0);
    tempTex->addCoordinate(128, 128);
    tempTex->addCoordinate(0, 128);

    tempTex->addVertex(vSet[0]);
    tempTex->addVertex(vSet[1]);
    tempTex->addVertex(vSet[2]);
    tempTex->addVertex(vSet[3]);
    texPyramidMesh.addPolygon(tempTex);

    tempCol->copyVertices(*tempTex);
    colPyramidMesh.addPolygon(tempCol);

    //add first triangle face
    tempTex = new TexPolygon(GL_TRIANGLES, whistleTextureID);
    tempCol = new ColPolygon(GL_TRIANGLES, 255, 0, 0);

    tempTex->addCoordinate(0, 128);
    tempTex->addCoordinate(128/2, 0);
    tempTex->addCoordinate(128, 128);

    tempTex->addVertex(vSet[0]);
    tempTex->addVertex(vSet[4]);
    tempTex->addVertex(vSet[1]);
    texPyramidMesh.addPolygon(tempTex);
    
    tempCol->copyVertices(*tempTex);
    colPyramidMesh.addPolygon(tempCol);

    //add second triangle face
    tempTex = new TexPolygon(GL_TRIANGLES, whistleTextureID);
    tempCol = new ColPolygon(GL_TRIANGLES, 0, 255, 0);
    
    tempTex->addCoordinate(0, 128);
    tempTex->addCoordinate(128/2, 0);
    tempTex->addCoordinate(128, 128);

    tempTex->addVertex(vSet[1]);
    tempTex->addVertex(vSet[4]);
    tempTex->addVertex(vSet[2]);
    texPyramidMesh.addPolygon(tempTex);

    tempCol->copyVertices(*tempTex);
    colPyramidMesh.addPolygon(tempCol);

    //add third triangle face
    tempTex = new TexPolygon(GL_TRIANGLES, whistleTextureID);
    tempCol = new ColPolygon(GL_TRIANGLES, 0, 0, 255);
    
    tempTex->addCoordinate(0, 128);
    tempTex->addCoordinate(128/2, 0);
    tempTex->addCoordinate(128, 128);

    tempTex->addVertex(vSet[2]);
    tempTex->addVertex(vSet[4]);
    tempTex->addVertex(vSet[3]);
    texPyramidMesh.addPolygon(tempTex);

    tempCol->copyVertices(*tempTex);
    colPyramidMesh.addPolygon(tempCol);

    //add fourth triangle face
    tempTex = new TexPolygon(GL_TRIANGLES, whistleTextureID);
    tempCol = new ColPolygon(GL_TRIANGLES, 255, 0, 255);
    
    tempTex->addCoordinate(0, 128);
    tempTex->addCoordinate(128/2, 0);
    tempTex->addCoordinate(128, 128);

    tempTex->addVertex(vSet[3]);
    tempTex->addVertex(vSet[4]);
    tempTex->addVertex(vSet[0]);
    texPyramidMesh.addPolygon(tempTex);

    tempCol->copyVertices(*tempTex);
    colPyramidMesh.addPolygon(tempCol);

    //=============== game objects =================
    BoundBox pyrBox(-1.0f, 0.0f, -1.0f, 2.0f, 2.0f, 2.0f);
    GameObject tPyramid, cPyramid;
    tPyramid.setMesh(&texPyramidMesh);
    // tPyramid.setBox(&pyrBox);

    cPyramid.setMesh(&colPyramidMesh);
    // cPyramid.setBox(&pyrBox); //reuse bound box as they are the same sized pyramids

    tPyramid.transform.translate(-1.5f, 0, 0);
    cPyramid.transform.translate(1.5f, 0, 0);

    GameObject parentPyramid;
    parentPyramid.transform.translate(0, 0, -5);
    parentPyramid.addChild(&tPyramid);
    parentPyramid.addChild(&cPyramid);

    SceneGraph scene;
    GameObject root;
    root.addChild(&parentPyramid);
    scene.root = &root;
    // root.disable();

    while(true){
        float deltaX = 0.0f, deltaY = 0.0f, deltaZ = 0.0f, degX = 0.0f, degY = 0.0f, degZ = 0.0f;
        //get input
        scanKeys();
		
		u16 keys = keysHeld();
		
		// if((keys & KEY_UP)) xr = 3.0f;
		// if((keys & KEY_DOWN)) xr = -3.0f;
		// if((keys & KEY_LEFT)) yr = 3.0f;
		// if((keys & KEY_RIGHT)) yr = -3.0f;
        // if((keys & KEY_R)) parentPyramid.transform.translate(0.1f, 0, 0);
        // if((keys & KEY_L)) parentPyramid.transform.translate(-0.1f, 0, 0);

        /**
         * moving the camera
         * note: to move the camera in the positive x direction, translate the root object in the 
         * negative x direction. do the same thing for other axes
         * 
         * this is because the translations are moving all the objects in the scene, so we must flip all transformations
         * to treat it like we are moving the view point
         */
        //translations
        if ((keys & KEY_UP) == KEY_UP) deltaZ = 0.1f;
        if ((keys & KEY_DOWN) == KEY_DOWN) deltaZ = -0.1f;
        if ((keys & KEY_LEFT) == KEY_LEFT) deltaX = 0.1f;
        if ((keys & KEY_RIGHT) == KEY_RIGHT) deltaX = -0.1f;
        //rotations
        if ((keys & KEY_Y) == KEY_Y) degY = -1.0f;
        if ((keys & KEY_A) == KEY_A) degY = 1.0f;
        if ((keys & KEY_B) == KEY_B) degX = 1.0f;
        if ((keys & KEY_X) == KEY_X) degX = -1.0f;

        root.transform.translate(deltaX, deltaY, deltaZ);
        root.transform.rotate(degX, degY, degZ);

        // parentPyramid.transform.rotate(xr, yr, 0);
        // Vertex location = root.transform.getLocation();
        // glGetFixed(GL_GET_MATRIX_POSITION, &temp);
        // PosTest(location.x, location.y, location.z);
        // printf("%ld, %ld, %ld\n", PosTestXresult(), PosTestYresult(), PosTestZresult());
        scene.dfsRender();
        scene.renderFlush(0); //note: this calls glFlush, which acts like swiWaitForVBlank but with 3D rendering options
        // swiWaitForVBlank();
    }
}
int bspScene(){
    glInit(); //initialize OpenGL state machine
    SceneGraph::debugGLConfig(); //debug gl setup configuration

    //============== texture ==============
    int whistleTextureID;
    glGenTextures(1, &whistleTextureID); //allocates texture space

    //binding this texture id as the current one in the state machine
    glBindTexture(0, whistleTextureID);
    //loads texture image into memory allocated for whistleTextureID
    glTexImage2D(0, 0, GL_RGBA, TEXTURE_SIZE_128, TEXTURE_SIZE_128, 0, TEXGEN_TEXCOORD, (u8 *) whistleBitmap);

    //=============== polygons =================
    u32 polyFormat = POLY_ALPHA(31) | POLY_CULL_NONE;

    //set of vertices for a pyramid
    Vertex vSet[5];
    vSet[0] = {1, 0, 1};
    vSet[1] = {-1, 0, 1};
    vSet[2] = {-1, 0, -1};
    vSet[3] = {1, 0, -1};
    vSet[4] = {0, 2, 0};

    std::vector<Polygon *> pList;

    // PolyMesh texPyramidMesh(polyFormat);
    //add square as base of pyramid
    TexPolygon *tempTex = new TexPolygon(GL_QUADS, whistleTextureID);

    //define coloured pyramid and add polygons to it
    // PolyMesh colPyramidMesh(polyFormat);
    // ColPolygon *tempCol = new ColPolygon(GL_QUADS, 255, 255, 0);

    // Vertex offset(1.5f, 0, 0);

    tempTex->addCoordinate(0, 0);
    tempTex->addCoordinate(128, 0);
    tempTex->addCoordinate(128, 128);
    tempTex->addCoordinate(0, 128);

    tempTex->addVertex(vSet[0]);
    tempTex->addVertex(vSet[1]);
    tempTex->addVertex(vSet[2]);
    tempTex->addVertex(vSet[3]);
    pList.push_back(tempTex);

    // tempTex->addVertex(vSet[0] - offset);
    // tempTex->addVertex(vSet[1]- offset);
    // tempTex->addVertex(vSet[2]- offset);
    // tempTex->addVertex(vSet[3]- offset);
    // pList.push_back(tempCol);

    //add first triangle face
    tempTex = new TexPolygon(GL_TRIANGLES, whistleTextureID);
    // tempCol = new ColPolygon(GL_TRIANGLES, 255, 0, 0);

    tempTex->addCoordinate(0, 128);
    tempTex->addCoordinate(128/2, 0);
    tempTex->addCoordinate(128, 128);

    tempTex->addVertex(vSet[0]);
    tempTex->addVertex(vSet[4]);
    tempTex->addVertex(vSet[1]);
    pList.push_back(tempTex);

    // tempTex->addVertex(vSet[0] - offset);
    // tempTex->addVertex(vSet[4]- offset);
    // tempTex->addVertex(vSet[1]- offset);
    // pList.push_back(tempCol);

    //add second triangle face
    tempTex = new TexPolygon(GL_TRIANGLES, whistleTextureID);
    // tempCol = new ColPolygon(GL_TRIANGLES, 0, 255, 0);
    
    tempTex->addCoordinate(0, 128);
    tempTex->addCoordinate(128/2, 0);
    tempTex->addCoordinate(128, 128);

    tempTex->addVertex(vSet[1]);
    tempTex->addVertex(vSet[4]);
    tempTex->addVertex(vSet[2]);
    pList.push_back(tempTex);

    // tempTex->addVertex(vSet[1] - offset);
    // tempTex->addVertex(vSet[4]- offset);
    // tempTex->addVertex(vSet[2]- offset);
    // pList.push_back(tempCol);

    //add third triangle face
    tempTex = new TexPolygon(GL_TRIANGLES, whistleTextureID);
    // tempCol = new ColPolygon(GL_TRIANGLES, 0, 0, 255);
    
    tempTex->addCoordinate(0, 128);
    tempTex->addCoordinate(128/2, 0);
    tempTex->addCoordinate(128, 128);

    tempTex->addVertex(vSet[2]);
    tempTex->addVertex(vSet[4]);
    tempTex->addVertex(vSet[3]);
    pList.push_back(tempTex);

    // tempTex->addVertex(vSet[2] - offset);
    // tempTex->addVertex(vSet[4]- offset);
    // tempTex->addVertex(vSet[3]- offset);
    // pList.push_back(tempCol);

    //add fourth triangle face
    tempTex = new TexPolygon(GL_TRIANGLES, whistleTextureID);
    // tempCol = new ColPolygon(GL_TRIANGLES, 255, 0, 255);
    
    tempTex->addCoordinate(0, 128);
    tempTex->addCoordinate(128/2, 0);
    tempTex->addCoordinate(128, 128);

    tempTex->addVertex(vSet[3]);
    tempTex->addVertex(vSet[4]);
    tempTex->addVertex(vSet[0]);
    pList.push_back(tempTex);

    // tempTex->addVertex(vSet[3] - offset);
    // tempTex->addVertex(vSet[4]- offset);
    // tempTex->addVertex(vSet[0]- offset);
    // pList.push_back(tempCol);

    //bsp
    BSPNode root(polyFormat);
    root.buildBSPTree(pList);
    printf("done building");
    while(true){
        float deltaX = 0.0f, deltaY = 0.0f, deltaZ = 0.0f, degX = 0.0f, degY = 0.0f, degZ = 0.0f;
        //get input
        scanKeys();
		
		u16 keys = keysHeld();
		
		// if((keys & KEY_UP)) xr = 3.0f;
		// if((keys & KEY_DOWN)) xr = -3.0f;
		// if((keys & KEY_LEFT)) yr = 3.0f;
		// if((keys & KEY_RIGHT)) yr = -3.0f;
        // if((keys & KEY_R)) parentPyramid.transform.translate(0.1f, 0, 0);
        // if((keys & KEY_L)) parentPyramid.transform.translate(-0.1f, 0, 0);

        /**
         * moving the camera
         * note: to move the camera in the positive x direction, translate the root object in the 
         * negative x direction. do the same thing for other axes
         * 
         * this is because the translations are moving all the objects in the scene, so we must flip all transformations
         * to treat it like we are moving the view point
         */
        //translations
        if ((keys & KEY_UP) == KEY_UP) deltaZ = 0.1f;
        if ((keys & KEY_DOWN) == KEY_DOWN) deltaZ = -0.1f;
        if ((keys & KEY_LEFT) == KEY_LEFT) deltaX = 0.1f;
        if ((keys & KEY_RIGHT) == KEY_RIGHT) deltaX = -0.1f;
        //rotations
        if ((keys & KEY_Y) == KEY_Y) degY = -1.0f;
        if ((keys & KEY_A) == KEY_A) degY = 1.0f;
        if ((keys & KEY_B) == KEY_B) degX = 1.0f;
        if ((keys & KEY_X) == KEY_X) degX = -1.0f;

        root.transform.translate(deltaX, deltaY, deltaZ);
        root.transform.rotate(degX, degY, degZ);
        // parentPyramid.transform.rotate(xr, yr, 0);
        // Vertex location = root.transform.getLocation();
        // glGetFixed(GL_GET_MATRIX_POSITION, &temp);
        // PosTest(location.x, location.y, location.z);
        // printf("%ld, %ld, %ld\n", PosTestXresult(), PosTestYresult(), PosTestZresult());
        glMatrixMode(GL_MODELVIEW);
        printf("%d\n", root.render());
        // root.render();
        // for (auto i : pList){
        //     (*i).drawPolygon();
        // }
        glFlush(0); //note: this calls glFlush, which acts like swiWaitForVBlank but with 3D rendering options
        // swiWaitForVBlank();
    }
    return 0;
}
int main(){
    // return bspScene();
    return doublePyramidScene();
}