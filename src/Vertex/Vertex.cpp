#include "./Vertex.h"
#include "../glmHandler/glmHandler.h"
Vertex:: Vertex() {
    verticeMatrix  = glm::mat4 (1.0f ) ;  
    setQuadrant() ;
}
Vertex:: Vertex (float symetricDistanceFromOrigin , Quadrant quadrant ) {
    verticeMatrix  = glm::mat4 (1.0f) ; 
    scaleSymetrically( symetricDistanceFromOrigin , quadrant ) ; 
    quadrant = quadrant ; 

} 
Vertex::Vertex (glm::vec3 &postionVec3 ) {
    verticeMatrix  = glm::mat4 (1.0f) ; 
    scaleAsymetrically( postionVec3 ) ;
    setQuadrant() ; 
} 
Vertex::Vertex (glm::vec3 postionVec3 ) {
    verticeMatrix  = glm::mat4 (1.0f) ; 
    scaleAsymetrically( postionVec3 ) ;
    setQuadrant() ; 
} 
void Vertex::scaleSymetrically (float length ) {
    myScale (verticeMatrix , glm::vec3 (length , length , length ) )   ; 
}
void Vertex::scaleAsymetrically (glm::vec3 scalingVec3 ) {
    myScale (verticeMatrix , scalingVec3 ) ; 
} 
void Vertex::scaleSymetrically (float length , Quadrant quadrant ) {
    switch (quadrant) {

        case Quadrant::positiveUpperRight : {
           myScale  (verticeMatrix , glm::vec3 (length , length , length ) )   ; 
           break  ;  
        } 
        case Quadrant::positiveLowerRight : {
            myScale  (verticeMatrix , glm::vec3 (length , -length , length ) )   ; 
            break ; 
        }
        case Quadrant::positiveLowerLeft : {
            myScale  (verticeMatrix , glm::vec3 (-length , -length , length ) )   ; 
            break ;   
        } 
        case Quadrant::positiveUpperLeft : {
            myScale  (verticeMatrix , glm::vec3 (-length , length , length ) )   ; 
            break ; 
        }
        case Quadrant::negativeUpperRight : {
           myScale  (verticeMatrix , glm::vec3 (length , length , -length ) )   ; 
           break  ;  
        } 
        case Quadrant::negativeLowerRight : {
            myScale  (verticeMatrix , glm::vec3 (length , -length , -length ) )   ; 
            break ; 
        }
        case Quadrant::negativeLowerLeft : {
            myScale  (verticeMatrix , glm::vec3 (-length , -length , -length ) )   ; 
            break ;   
        } 
        case Quadrant::negativeUpperLeft : {
            myScale  (verticeMatrix , glm::vec3 (-length , length , -length ) )   ; 
            break ; 
        } 
        default : {
            std::cout << "no matching Quadrant " << std::endl ; 
        } 
    } 
} 

void Vertex::translate (const glm::vec3 & movementVec3 ){
   verticeMatrix[3][0] = verticeMatrix[3][0] +  movementVec3.x  ;  
   verticeMatrix[3][1] = verticeMatrix[3][1] + movementVec3.y  ; 
   verticeMatrix[3][2] = verticeMatrix[3][2] + movementVec3.z  ;  
} 

void Vertex::rotateVertex ( const glm::vec3 & orientationVec3) {

    verticeMatrix= glm::rotate (verticeMatrix,
    orientationVec3.x ,glm::vec3(1.0f , 0.0f , 0.0f ) );
    verticeMatrix = glm::rotate (verticeMatrix ,
    orientationVec3.y ,glm::vec3 (0.0f , 1.0f , 0.0f ) );
    verticeMatrix = glm::rotate (verticeMatrix ,
    orientationVec3.z ,glm::vec3 ( 0.0f , 0.0f , 1.0f));  
    return ;
}

void Vertex::rotateVertexAlongAxis (const glm::vec3 & axis  , float amount) 
{
    verticeMatrix = glm::rotate (verticeMatrix , amount , axis ) ; 
}  
// Vertex:: Vertex(glm::vec3 & positionVec3 ){
//     verticeMatrix =   vec4ToMat4( glm::vec4 (positionVec3 , 1.0f  )) ;  
// } 
Vertex::Vertex (glm::mat4 & matrix ){
    verticeMatrix = matrix ; 
} 
//------------------- operator overloading ---------------
Vertex Vertex::operator - (const Vertex & vertex1  ){
    Vertex  localVertex ; 
    localVertex.verticeMatrix = (this->verticeMatrix )- (vertex1.verticeMatrix ) ;
    return  localVertex ;  
} 
float Vertex::operator [] (int index ) 
{   
    float returnFloat{0.0f}  ; 
    for (int i = 0 ; i <3  ; i++) // excluding the translate value 
    {
    returnFloat += verticeMatrix[i][index];
    }
    if (index  == 0 || index == 1 ){ 
        float zAxis {0};   
        float & indexAxis = returnFloat  ; // no need to copy it again and thats why my friends you learn c++
        for (int i = 0 ; i <4  ; i++)
        {
            zAxis  += verticeMatrix[i][2];
        }
        if(zAxis  > 0.0f  ) { 
            float percentageOfFarness = zAxis  / distanceFromObserver ; 
            float relativeX = (indexAxis  + indexAxis*percentageOfFarness );
            relativeX += verticeMatrix[3][index] ; // including the excluded translate value 
            return relativeX ; 
        }
        if(zAxis  < 0.0f  ) {
            float percentageOfCloseness =  zAxis/ distanceFromObserver ; 
            float relativeX = (indexAxis + indexAxis*percentageOfCloseness );
            relativeX += verticeMatrix[3][index] ; // including the excluded translate value 
            return relativeX ; 
        }

    }
    
    if (index == 2 )return returnFloat ;
     
 }      

bool Vertex::isTouchingVertex (float range  , const SDL_MouseMotionEvent  & mouseEvent ) { 
    if ( (mouseEvent.x >= ((*this)[0] - range) && mouseEvent.x <= ((*this)[0] + range ) )) {
        if ((mouseEvent.y >= ((*this)[1] - range) && mouseEvent.y <= ((*this)[1] + range ) ))
        {return true ; 
                        }
  }
    else return false ; 
}   
Vertex & Vertex::operator = ( const Vertex & vertex ) {
    this->verticeMatrix = vertex.verticeMatrix ; 
    this -> quadrant = vertex.quadrant ;
    return *this ;
 } ; 


 void Vertex::rotateVertexGpt( float angleX, float angleY, float angleZ) {
    std::cout << quadrant <<std::endl;
    if (quadrant == Quadrant::positiveUpperRight) {
    } 
    //above line of code is hyperactive 
    if (quadrant == Quadrant::positiveUpperLeft ) {
        angleY = -angleY ; 
        angleZ = -angleZ ;
    }
    if (quadrant == Quadrant::positiveLowerLeft ) {
        angleX = -angleX ;
        angleY = -angleY ;
    }
    if (quadrant == Quadrant::positiveLowerRight) {
        angleZ = -angleZ ;
        angleX = -angleX ; 
    } 
        
    float radX = glm::radians(angleX);
    float radY = glm::radians(angleY);
    float radZ = glm::radians(angleZ);

    glm::mat4 rotationX = {
        {1, 0, 0, 0},
        {0, cos(radX), -sin(radX), 0},
        {0, sin(radX), cos(radX), 0},
        {0, 0, 0, 1}
    };
    glm::mat4 rotationY = {
        {cos(radY), 0, sin(radY), 0},
        {0, 1, 0, 0},
        {-sin(radY), 0, cos(radY), 0},
        {0, 0, 0, 1}
    };
    glm::mat4 rotationZ = {
        {cos(radZ), -sin(radZ), 0, 0},
        {sin(radZ), cos(radZ), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    verticeMatrix  = verticeMatrix * rotationX * rotationY * rotationZ;
}
void Vertex:: setQuadrant () {
    if (getAtIndexExcludingTranslate(2) > 0 ) {
        if (getAtIndexExcludingTranslate(1) > 0) {
            if (getAtIndexExcludingTranslate(0) > 0 ) {
                quadrant = Quadrant::positiveUpperRight ;

            }
            if (getAtIndexExcludingTranslate(0) < 0) {
                quadrant = Quadrant::positiveUpperLeft ; 
            }
        }
        if (getAtIndexExcludingTranslate(1) < 0) {
            if (getAtIndexExcludingTranslate(0) > 0 ) {
                quadrant = Quadrant::positiveLowerRight ;
            }
            if (getAtIndexExcludingTranslate(0) < 0) {
                quadrant = Quadrant::positiveLowerLeft ; 
            }
        }
    }
    if (getAtIndexExcludingTranslate(2) < 0 ) {
        if (getAtIndexExcludingTranslate(1) > 0) {
            if (getAtIndexExcludingTranslate(0) > 0 ) {
                quadrant = Quadrant::negativeUpperRight ; 
            }
            if (getAtIndexExcludingTranslate(0) < 0) {
                quadrant = Quadrant::negativeUpperLeft ; 
            }
        }
        if (getAtIndexExcludingTranslate(1) < 0) {
            if (getAtIndexExcludingTranslate(0) > 0 ) {
                quadrant = Quadrant::negativeLowerRight ; 
            }
            if (getAtIndexExcludingTranslate(0) < 0) {
                quadrant = Quadrant::negativeLowerLeft ; 
            }
        }
    }
    // std::cout << quadrant << std::endl;  // the very essential operator overloading for ouputing enumerated class 
}