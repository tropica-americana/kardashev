#ifndef _NOTHING_CLASS_
#define _NOTHING_CLASS_
#include <iostream>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "../myVertex/myVertex.h"
class nothingClass {
    public:
    virtual void renderMyself (SDL_Renderer * renderer ) {}; 
    virtual void translate (const glm::vec3 & vec3 ){} ; 
    // virtual void translate (float xTranslateParameter , float yTranslateParameter , float zTranslateParameter  ){}  ;
    virtual void rotate(const glm::vec3 & orientationVec3   ){} ; 
    // virtual void rotate(float xRotateParameter , float yRotateParameter , float zRotateParameter ) {}; 
    virtual void processInput (const SDL_MouseMotionEvent & mouseEvent ){} ;    
};
class myNothingClass {
public:
    virtual void renderMyself(SDL_Renderer *renderer) = 0;
    virtual void translate(float xTranslateParameter, float yTranslateParameter, float zTranslateParameter) = 0;
    virtual void rotate(float xRotateParameter, float yRotateParameter, float zRotateParameter) = 0;
    virtual void processInput(const SDL_MouseMotionEvent &mouseEvent , const SDL_KeyboardEvent & keyboardEvent ) = 0;
    virtual void addVertex (float xAmount , float yAmount , float zAmount)  = 0;
    virtual void createMesh() = 0;
};
#endif // !_NOTHINGCLASS_
// processInput method can be overridden in the derived classed 