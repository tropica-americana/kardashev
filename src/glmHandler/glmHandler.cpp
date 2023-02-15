#include <iostream>
#include <glm/glm.hpp>
#include "glmHandler.h" 

// --------a funciton that takes the square vertex as the 3d position and then ------
//----------------------rotates it along the sqaure orientation---------------------------
//------------------------and then return a final vertex model -----------------------------

inline  void rotateVertex ( glm::vec4 &vertex 
, const glm::vec3 & orientationVec3 )
{  
    glm::mat4 vertexToModel = glm::mat4 (vertex.x , vertex.y , vertex.z ,1.0f ) ; 
    vertexToModel = glm::rotate (vertexToModel,
    orientationVec3.x ,glm::vec3 (1.0f , 0.0f , 0.0f ) );
    vertexToModel = glm::rotate (vertexToModel,
    orientationVec3.y ,glm::vec3 (0.0f , 1.0f , 0.0f ) );
    vertexToModel = glm::rotate (vertexToModel,
    orientationVec3.z ,glm::vec3 ( 0.0f , 0.0f , 1.0f));
    vertex =  ( vertexToModel * glm::vec4 (1.0f , 1.0f  , 1.0f , 1.0f ) ) ;  
    return ; 
}