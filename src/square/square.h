#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <iostream>
#include <vector> 
#include <map>
#include "glm/glm.hpp"
#include <SDL2/SDL.h>
#include <array>
#include <vector>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/string_cast.hpp>
#include <string>
#include "../glmHandler/glmHandler.h"
class Square {
    public:
    float  squareWidth ; 
    glm::vec3 squarePosition ; // contains the position of the sqaure i the 3Dimesional space 
    glm::vec3 squareOrientation ; // contains the value of square rotation in radians  
    std::vector <glm::mat4> squareverticesarray ;   
    Square (float squareWidth ) ; 
    ~Square () = default ; 
    void renderMyself ( SDL_Renderer * renderer ) ;
    void handleMouseEvents(SDL_MouseMotionEvent &mouseEvent , SDL_MouseWheelEvent &wheelEvent) ;  
    void fillVertices () ;
}; 

#endif // !_SQUARE_H_