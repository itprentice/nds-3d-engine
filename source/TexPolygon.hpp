/**
 * @file TexPolygon.hpp
 * @author Ian Prentice (iprentic@uwo.ca)
 * @brief header interface of TexPolygon class
 *
 */
#ifndef TEXPOLYGON_H
#define TEXPOLYGON_H

#include "Polygon.hpp"

/**
 * @brief Textured Polygon class: polygon with a texture mapping
 * 
 */
class TexPolygon : public Polygon{
    private:
        int textureId;
        std::vector<u32> coordinates;
    public:
        /**
         * @brief adds coordinate mapping for texture in (u, v) coordinates
         * 
         * @param u
         * @param v
         */
        void addCoordinate(int u, int v);

        /**
         * @brief updates texture to be represented with new id
         * 
         * @param textureId 
         */
        void changeTexture(int textureId);

        void drawPolygon() override;
        /**
         * @brief Construct a new Tex Polygon object
         * 
         * @param t 
         * @param textureId 
         */
        TexPolygon(GL_GLBEGIN_ENUM t, int textureId);
        Polygon *createCopy() override;
};

#endif