#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <iostream>
#include <array>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "../glmHandler/glmHandler.h"
#include "../Vertex/vertex.h"
#include "../Quadrant/Quadrant.h"
class Pyramid {
public :    
    std::array <Vertex,5> verticesArray ; 
    Pyramid (float length ) ; 
    ~Pyramid() = default ; 
    void renderMyself (SDL_Renderer * renderer ) ; 
    void translate (const glm::vec3 & vec3 ) ; 
    void rotate(const glm::vec3 & orientationVec3   ) ; 
    void processInput (const SDL_MouseMotionEvent & mouseEvent ) ;    
    void displaySelf () ; 
};
#endif
