/**
 * @file GameObject.cpp
 * @author Ian Prentice (iprentic@uwo.ca)
 * @brief implementation of GameObject class
 * 
 */

#include "GameObject.hpp"
#include <nds/arm9/postest.h>
#include <stdio.h>

GameObject::GameObject():
activeState{true},
mesh{nullptr},
box{nullptr},
parent{nullptr}{
}

void GameObject::addChild(GameObject *c){
    if (c->parent == nullptr){
        c->parent = this;
        this->children.push_back(c);
    }
}

int GameObject::render(){
    int retVal = 0;
    if (this->isActive()){
        this->transform.doTransform();
        bool isVisible = true;
        if (this->box != nullptr){
            isVisible = this->box->checkBoxTest();
        }
        if (this->mesh != nullptr && isVisible){
            this->mesh->renderMesh();
            retVal = this->mesh->numPolygons();
        }

    }
    // else{
    //     this->transform.doTransform();
    //     PosTest(0, 0, 0);
    //     printf("%f, %f, %f\n", f32tofloat(PosTestXresult()), f32tofloat(PosTestYresult()), f32tofloat(PosTestZresult()));
    // }
    return retVal;
}

void GameObject::setMesh(PolyMesh *newMesh){
    this->mesh = newMesh;
}

void GameObject::setBox(BoundBox *box){
    this->box = box;
}

bool GameObject::isActive(){
    return this->activeState;
}

void GameObject::enable(){
    this->activeState = true;
}

void GameObject::disable(){
    this->activeState = false;
}

int GameObject::numPolygons(){
    if (this->mesh != nullptr && this->isActive()){
        return this->mesh->numPolygons();
    }
    else{
        return 0;
    }
}