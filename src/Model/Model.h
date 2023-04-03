#ifndef _MODEL_H_
#define _MODEL_H_

#include <iostream>
#include <array>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "../glmHandler/glmHandler.h"
#include "../Vertex/vertex.h"
#include "../Quadrant/Quadrant.h"
#include "../nothingClass /nothingClass.h"
#include <mutex>
class Model : nothingClass {
  public:
    std::vector<std::string> modelName ; 
    std::vector<Vertex> vertices;
     Model () = default ; 
    ~Model () = default ;
    virtual void renderMyself (SDL_Renderer * renderer )override ; 
    virtual void translate (const glm::vec3 & vec3 )override  ; 
    virtual void rotate(const glm::vec3 & orientationVec3   )override  ; 
    virtual void processInput (const SDL_MouseMotionEvent & mouseEvent )override ; 
    void addVertex (const glm::vec3 & vertex ) ; 
};
#endif