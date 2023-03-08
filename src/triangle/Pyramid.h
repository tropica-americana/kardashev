#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <iostream>
#include <array>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "../glmHandler/glmHandler.h"
#include "../Vertex/vertex.h"
#include "../Line/Line.h"
#include "../Quadrant/Quadrant.h"
class Pyramid {
public :    
    std::array <Vertex,5> verticesArray ; 
    std::array<Line,5> linesArray ; 
    Pyramid  () ; 
    ~Pyramid = default ; 
    void renderMyself () ; 
    void rotate(const glm::vec3 & axis ) ; 
    void processInput () ;        
}
#endif
