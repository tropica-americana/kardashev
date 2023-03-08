#include "./triangle.h"
Pyramid::Pyramid () {
    float length {30.0f } ; 
    verticesArray.at (0) = Vertex{glm::vec3 (0.0f , 0.0f ,0.0f)} ;
    verticesArray.at (1) = Vertex{length , Quadrant::positiveLowerRight } ; 
    verticesArray.at (2) = Vertex{length , Quadrant::positiveLowerLeft } ; 
    verticesArray.at (3) = Vertex{length , Quadrant::negativeLowerRight } ;   
    verticesArray.at (4) = Vertex{length , Quadrant::negativeLowerLeft  } ; 
} 
void Pyramid::rotate (const glm::vec3 & axis ) {
    
} 