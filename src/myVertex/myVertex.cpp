#include "./myVertex.h"
myVertex::myVertex(float xDistance , float yDistance , float zDistance){
    x = xDistance; y = yDistance; z = zDistance;
    xRotate = 0.0f; yRotate = 0.0f; zRotate = 0.0f;
}  
void myVertex::scale(float length ) {
    x = length   * x ; y = length * y ; z = length * z ;
}
void myVertex::translate ( float xT , float yT , float zT) {
     xTranslate += xT ; yTranslate += yT ; zTranslate += zT ;
}
void myVertex::rotateMyVertex (float xR , float yR , float zR )  {
    rotateMyVertexAlongAxis (xR , Axis :: x ) ; 
    rotateMyVertexAlongAxis (yR , Axis :: y ) ;
    rotateMyVertexAlongAxis (zR , Axis :: z ) ;
}
void myVertex::rotateMyVertexAlongAxis (float amount , Axis axis ) {
    if (axis ==  Axis :: z ) {
        x = x *  cos (amount ) - y * sin (amount );
        y = y *  cos (amount)  +  x * sin (amount )  ; 
    } 
    if (axis == Axis :: y ) {
        
        x = x * cos (amount ) + z * sin (amount ) ;
        z = z * cos (amount) - x * sin (amount )  ; 
    }
    if (axis == Axis :: x ) {
        y = y * cos (amount) - z * sin (amount) ; 
        z = z * cos (amount) + y * sin (amount) ;
    }
}
float myVertex::getOnScreenX() {
    float relativeX ; 
    float percentageOfFarness = z  / distanceFromObserver ; 
    relativeX = (x  + x * percentageOfFarness );
    relativeX += xTranslate ; 
    return relativeX ; 
    }
        
float myVertex::getOnScreenY() {
    float relativeY ; 
    float percentageOfFarness = z  / distanceFromObserver ; 
    relativeY = (y  + y * percentageOfFarness );
    relativeY += yTranslate ; 
    return relativeY ; 
}
myVertex& myVertex::operator=(const myVertex& vertex) {
    // copy all member variables from the 'vertex' parameter
    distanceFromObserver = vertex.distanceFromObserver;
    x = vertex.x;
    y = vertex.y;
    z = vertex.z;
    xRotate = vertex.xRotate;
    yRotate = vertex.yRotate;
    zRotate = vertex.zRotate;
    xTranslate = vertex.xTranslate;
    yTranslate = vertex.yTranslate;
    zTranslate = vertex.zTranslate;
    return *this;
}

// z axis directed away from the observor 
// Positive rotation is usually considered to be counterclockwise