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
    if (xR != 0 )rotateMyVertexAlongAxis (xR , Axis :: x ) ; 
    if (yR != 0 )rotateMyVertexAlongAxis (yR , Axis :: y ) ;
    if (zR != 0 )rotateMyVertexAlongAxis (zR , Axis :: z ) ;
}
void myVertex::rotateMyVertexAlongAxis (float amount , Axis axis ) {
    // float initialX = x ; 
    // float initialY = y ;
    // float initialZ = z ;
    if (axis == Axis::z) {
    float tempX = x;
    float tempY = y;
    x = tempX * cos(amount) - tempY * sin(amount);
    y = tempY * cos(amount) + tempX * sin(amount);
    }   
    if (axis == Axis::y) {
        float tempX = x;
        float tempZ = z;
        x = tempX * cos(amount) + tempZ * sin(amount);
        z = tempZ * cos(amount) - tempX * sin(amount);
    }
    if (axis == Axis::x) {
        float tempY = y;
        float tempZ = z;
        y = tempY * cos(amount) - tempZ * sin(amount);
        z = tempZ * cos(amount) + tempY * sin(amount);
    }

    // float lossOfX = initialX - x ; 
    // float lossOfY = initialY - y ;
    // float lossOfZ = initialZ - z ;
    // std::cout <<"loss of x " << " " << lossOfX << std::endl;
    // std::cout <<"loss of y " << " " << lossOfY<< std::endl;
    // std::cout <<"loss of z " << " " << lossOfZ << std::endl;
    
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