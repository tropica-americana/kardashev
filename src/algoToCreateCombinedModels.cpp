
#include "./myModel/myModel.h"
#include "./myVertex/myVertex.h"
#include <iostream>
#include <cmath>
#include <numbers>
myModel createSphere() {
    myModel sphere ; 
    sphere.currentMode = "modify" ; 
    myVertex mainVertex { 0.0f , 100.0f  , 0.0f } ; 
    sphere.addVertex(mainVertex) ; 
    float pi = std::numbers::pi_v< float>  ; 
    float currentAngle = 0.0f ; 
    int numberOfVerticesPerPlane = 10 ; 
    float incrementAngle =  2 * pi / static_cast<int> (numberOfVerticesPerPlane ) ; 
    for (int i = 0 ; i < 10 ; i++ ) {
        mainVertex.rotateMyVertexAlongAxis( incrementAngle , Axis::x) ; 
        for ( int i = 0 ; i < 10 ; i++ ) {
            mainVertex.rotateMyVertexAlongAxis(incrementAngle , Axis::z ) ; 
            sphere.addVertex(mainVertex) ; 
        }
    }
    sphere.createMesh() ; 
    return sphere ; 
}

