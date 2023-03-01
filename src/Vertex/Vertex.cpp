#include "./Vertex.h"

Vertex:: Vertex() {
    verticeMatrix  = glm::mat4 (1.0f ) ;  
}
Vertex:: Vertex (float symetricDistanceFromOrigin , Quadrant quadrant ) {
    verticeMatrix  = glm::mat4 (1.0f ) ; 
    scaleSymetrically( symetricDistanceFromOrigin , quadrant ) ; 
} ;

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
    verticeMatrix= glm::rotate (verticeMatrix,
    orientationVec3.x ,glm::vec3(1.0f , 0.0f , 0.0f ) );
    verticeMatrix = glm::rotate (verticeMatrix ,
    orientationVec3.y ,glm::vec3 (0.0f , 1.0f , 0.0f ) );
    verticeMatrix = glm::rotate (verticeMatrix ,
    orientationVec3.z ,glm::vec3 ( 0.0f , 0.0f , 1.0f));  
    return ;
}  
Vertex:: Vertex(glm::vec3 & positionVec3 ){
    verticeMatrix =   vec4toMat4( glm::vec4 (positionVec3 , 1.0f  )) ;  
} 

void Vertex::translate (glm::mat4 & modelToBeAdded ){
    glm::translate (vertexMatrix , mat4toVec4(modelToBeAdded)); 
}
Vertex::Vertex (glm::mat4 & matrix ){
    verticeMatrix = matrix ; 
} ;  
//------------------- operator overloading ---------------
Vertex  operator - (const Vertex & vertex1  ){
    Vertex  localVertex  = new Vertex ; 
    localVertex -> verticeMatrix = (this->verticeMatrix )- (vertex1.verticeMatrix ) ;
    return q localVertex ;  
 } ; 
float operator [] (int index )
 {float returnFloat{0.0f}  ; for (int i = 0 ; i <4  ; i++) {returnFloat += vertexMatrix[index][i] ; } return returnFloat ;   } ;     