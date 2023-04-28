#ifndef _MYVERTEX_H_
#define _MYVERTEX_H_
#include <iostream>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <vector>
#include <cmath>
#include "../Quadrant/Quadrant.h"
class myVertex {
    public:
    float distanceFromObserver {30000.0f };  
    float x ; 
    float y ; 
    float z ; 
    float xRotate = 0.0f ; 
    float yRotate  = 0.0f; 
    float zRotate = 0.01f ; 
    float xTranslate = 0.0f ; 
    float yTranslate = 0.0f; 
    float zTranslate = 0.01f; 
    myVertex(float xDistance , float yDistance , float zDistance) ; 
    myVertex() = default; 
    ~myVertex()  = default ;
    void scale(float length ) ;  
    void translate ( float xTranslate , float yTranslate , float zTranslate) ; 
    void rotateMyVertex (float xR , float yR , float zR ) ; 
    void rotateMyVertexAlongAxis (float amount , Axis axis ) ; 
    float getOnScreenX () ; 
    float getOnScreenY () ; 
    float convertOnScreenXtoAbsoluteX (float x ) ;
    float convertOnScreenYtoAbsoluteY (float y ) ;
    void displayVertexOnTerminal () ; 
    myVertex & operator = ( const myVertex & vertex )  ; 
    myVertex operator - (const myVertex & vertex ) ;
}  ; 
#endif 