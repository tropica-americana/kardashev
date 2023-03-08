#ifndef _LINE_H_
#define _LINE_H_
#include <iostream>
#include <vector>
#include <array> 
#include "../Vertex/Vertex.h"
#include "../Quadrant/Quadrant.h"
#include <SDL2/SDL.h>
class Line : std::array<Vertex , 2 > {
public : 
    glm::mat4 centerOfRotation ; 
    Line () ; 
    Line (float scalingNumber ) ; 
    ~Line () = default  ;
    Vertex *  getCenterOfRotation () ;   
    void rotateLine(const  glm::vec3 & orientationVec3 ); 
    void rotateLineAlongAxis (const glm::vec3 & axis  , float amount ) ; 
    void rotateLineAlongCOT(const glm::vec3 & orientationVec3 , Vertex & centerOfTranslation  ) ; 
    void renderMyself (SDL_Renderer * renderer );
    Vertex operator [] (int index ) {return this->at(index) ; }  ; 
    void processInput  ( const SDL_MouseMotionEvent  & mouseEvent )  ; 
    
} ;

#endif 