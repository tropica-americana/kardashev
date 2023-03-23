#ifndef _NOTHING_CLASS_
#define _NOTHING_CLASS_
#include <iostream>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
class nothingClass {
    public:
    virtual void renderMyself (SDL_Renderer * renderer ) {}; 
    virtual void translate (const glm::vec3 & vec3 ){} ; 
    virtual void rotate(const glm::vec3 & orientationVec3   ){} ; 
    virtual void processInput (const SDL_MouseMotionEvent & mouseEvent ){} ;    
};
#endif // !_NOTHINGCLASS_
// processInput method can be overridden in the derived classed 