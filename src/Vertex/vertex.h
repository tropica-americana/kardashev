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
    float distanceFromObserver {500.0f };  
    glm::mat4 verticeMatrix ;  
    Quadrant quadrant ; 
    Vertex() ; 
    Vertex (float symetricDistanceFromOrigin , Quadrant quadrant ) ; 
    Vertex (glm::vec3 & positionVec3 )  ;
    Vertex (glm::vec3 positionVec3 )  ;
    Vertex (glm::mat4 & matrix ) ;  
    ~Vertex()  = default ;
    float getAtIndex (int index) {float returnFloat{0} ; for (int i = 0 ; i < 4 ; i++){returnFloat += verticeMatrix[i][index] ; } return returnFloat ; }
    float getAtIndexExcludingTranslate (int index) {float returnFloat{0} ; for (int i = 0 ; i < 3 ; i++){returnFloat += verticeMatrix[i][index] ; } return returnFloat ; }
    void scaleSymetrically (float length ) ;  
    void scaleAsymetrically (glm::vec3 scalingVec3 ) ; 
    void scaleSymetrically (float length , Quadrant quadrant ) ;
    void translate (const glm::vec3 & movementVec3 ) ; 
    void translate (glm::mat4 & modelToBeAdded ) ; // can take model as an input 
    void rotateVertex (const glm::vec3 & orientationVec3) ; 
    void rotateVertexGpt( float angleX, float angleY, float angleZ) ; 
    void rotateVertexAlongAxis (const glm::vec3 & axis , float amount  ) ; 
    float operator [] (int index ) ;
    Vertex operator - (const Vertex & vertex1 ) ; 
    Vertex & operator = ( const Vertex & vertex )  ; 
    bool isTouchingVertex (float range , const SDL_MouseMotionEvent & mouseEvent )  ; 
    void setQuadrant () ; 

}  ; 
#endif // !_VERTEX_H_
