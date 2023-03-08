#ifndef _VERTEX_H_
#define _VERTEX_H_
#include <iostream>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "../glmHandler/glmHandler.h"
#include <vector>
#include "../Quadrant/Quadrant.h"

class Vertex {

    public: 
    glm::mat4 verticeMatrix ;  
    Vertex() ; 
    Vertex (float symetricDistanceFromOrigin , Quadrant quadrant ) ; 
    Vertex (glm::vec3 & positionVec3 )  ;
    Vertex (glm::mat4 & matrix ) ;  
    ~Vertex()  = default ;
    void scaleSymetrically (float length ) ;  
    void scaleAsymetrically (glm::vec3 scalingVec3 ) ; 
    void scaleSymetrically (float length , Quadrant quadrant ) ;
    void translate (const glm::vec3 & movementVec3 ) ; 
    void translate (glm::mat4 & modelToBeAdded ) ; // can take model as an input 
    // void rotateVertex (const glm::vec3 & orientationVec3) ; 
    void rotateVertexAlongAxis (const glm::vec3 & axis , float amount  ) ; 
    float operator [] (int index ) ;
    Vertex operator - (const Vertex & vertex1  ) ; 
    Vertex & operator = (float decimal_number )  ; 
    bool isTouchingVertex (float range , const SDL_MouseMotionEvent & mouseEvent )  ; 

}  ; 
#endif // !_VERTEX_H_
