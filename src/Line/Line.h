#ifndef _LINE_H_
#define _LINE_H_
#include <iostream>
#include <vector>
#include <array> 
#include "../Vertex/Vertex.h"

class Line : std::array<Vertex ,2 > {
    public : 
    glm::mat4 centerOfRotation ; 
    Line () ; 
    ~Line () = default  ;
    Vertex &  getCenterOfRotation () ;   
    rotateLine(const  glm::vec3 & orientationVec3 ); 
    rotateLineAlongCOT(const glm::vec3 & orientationVec3 , Vertex & centerOfTranslation  ) ; 
}   

#endif 