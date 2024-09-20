/**
 * @file TexPolygon.cpp
 * @author your name (you@domain.com)
 * @brief implementation of TexPolygon class
 * 
 */

#include "TexPolygon.hpp"
#include <stdio.h>

TexPolygon::TexPolygon(GL_GLBEGIN_ENUM t, int textureId): Polygon{t}, textureId{textureId} {

}
void TexPolygon::addCoordinate(int u, int v){
    this->coordinates.push_back(TEXTURE_PACK(inttot16(u), inttot16(v)));
}

void TexPolygon::drawPolygon(){
    //only draw if there are enough texture coordinates for the amount of vertices
    if (isComplete()){
        glMatrixMode(GL_MODELVIEW);
        glBegin(this->type);
        glBindTexture(0, this->textureId);
        int tIdx = 0, tSize = this->coordinates.size();
        glColor3b(255, 255, 255); //for some reason, textures don't work if the polyon colour isn't white

        for (auto v : vertices){
            GFX_TEX_COORD = this->coordinates[tIdx];
            glVertex3v16(v.x, v.y, v.z);
            tIdx = (tIdx + 1) % tSize;
        }

        glEnd();
        // printf("hello from tex: %d\n", this->vertices.size());
    }
}

void TexPolygon::changeTexture(int tId){
    this->textureId = tId;
}

Polygon *TexPolygon::createCopy(){
    return new TexPolygon(*this);
}