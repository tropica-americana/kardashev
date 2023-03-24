#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <iostream>
#include <array>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "../glmHandler/glmHandler.h"
#include "../Vertex/vertex.h"
#include "../Quadrant/Quadrant.h"
#include "../nothingClass /nothingClass.h"
#include <mutex>
class Pyramid : public nothingClass {
public :    
    std::array <Vertex,5> verticesArray ; 
    std::mutex verticesArrayMutex ; 
    Pyramid (float length ) ; 
    ~Pyramid() = default ; 
    void renderMyself (SDL_Renderer * renderer ) override  ; 
    void translate (const glm::vec3 & vec3 ) override  ; 
    void rotate(const glm::vec3 & orientationVec3   ) override  ; 
    void processInput (const SDL_MouseMotionEvent & mouseEvent ) override ;    
    void displaySelf () ; 
};
#endif
