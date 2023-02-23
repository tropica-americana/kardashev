#include "./Vertex.h"

Vertex:: Vertex() {
    verticeMatrix  = glm::mat4 (1.0f ) ;  
}

void Vertex::scaleSymetrically (float length ) {
    glm::scale (verticeMatrix , glm::vec3 (length , length , length ) )   ; 
};  
void Vertex::scaleAsymetrically (glm::vec3 scalingVec3 ) {
    glm::scale (verticeMatrix , scalingVec3 ) ; 
}; 
void Vertex::scaleSymetrically (float length , Quadrant quadrant ) {
    switch (quadrant) {

        case positiveUpperRight : {
           glm::scale (verticeMatrix , glm::vec3 (length , length , length ) )   ; 
           break  ;  
        } 
        case positiveLowerRight : {
            glm::scale (verticeMatrix , glm::vec3 (length , -length , length ) )   ; 
            break ; 
        }
        case positiveLowerLeft : {
            glm::scale (verticeMatrix , glm::vec3 (-length , -length , length ) )   ; 
            break ;   
        } 
        case positiveUpperLeft : {
            glm::scale (verticeMatrix , glm::vec3 (-length , length , length ) )   ; 
            break ; 
        }
        case negativeUpperRight : {
           glm::scale (verticeMatrix , glm::vec3 (length , length , -length ) )   ; 
           break  ;  
        } 
        case negativeLowerRight : {
            glm::scale (verticeMatrix , glm::vec3 (length , -length , -length ) )   ; 
            break ; 
        }
        case negativeLowerLeft : {
            glm::scale (verticeMatrix , glm::vec3 (-length , -length , -length ) )   ; 
            break ;   
        } 
        case negativeUpperLeft : {
            glm::scale (verticeMatrix , glm::vec3 (-length , length , -length ) )   ; 
            break ; 
        } 
        default : {
            std::cout << "no matching Quadrant " << std::endl ; 
        } 
    } 
}; 

void Vertex::translate (glm::vec3 movementVec3 ){
    glm::translate ( verticeMatrix  , movementVec3 )  ; 
} ;  
void Vertex::rotateVertex ( const glm::vec3 & orientationVec3) {
    vertex = glm::rotate (verticeMatrix,
    orientationVec3.x ,glm::vec3(1.0f , 0.0f , 0.0f ) );
    vertex = glm::rotate (verticeMatrix ,
    orientationVec3.y ,glm::vec3 (0.0f , 1.0f , 0.0f ) );
    vertex = glm::rotate (verticeMatrix ,
    orientationVec3.z ,glm::vec3 ( 0.0f , 0.0f , 1.0f));  
    return ;
}  