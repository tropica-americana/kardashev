#ifndef _VERTEX_H_
#define _VERTEX_H_
#include <iostream>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "../glmHandler/glmHandler.h"
#include <vector>
enum class Quadrant {
    positiveUpperRight , 
    positiveLowerRight , 
    positiveLowerLeft ,
    positiveUpperLeft , 
    negativeUpperRight , 
    negativeLowerRight , 
    negativeLowerLeft ,
    negativeUpperLeft 
}
enum class Axis {
    positiveX , positiveY , positiveZ , negativeX , negativeY , negativeY 
} 
class Vertex {
 // a vertex cannot be rotated around another vertex with different center of mass , to rotate a vertex around another vertex a new vertex should be created with the the desired center of mass    
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
    void translate (glm::vec3 movementVec3 ) ; 
    void translate (glm::mat4 & modelToBeAdded ) ; // can take model as an input 
    void rotateVertex (const glm::vec3 & orientationVec3) ; 
    float operator [] (int index ) ;
    Vertex & operator - (const Vertex & vertex1  ) ; 
}   
#endif // !_VERTEX_H_
