#include "./Line.h"
#include "../Quadrant/Quadrant.h"
#include "../game/game.h"
Line :: Line () {  
    this->at(0) = ( Vertex(1.0f , Quadrant::positiveUpperRight ) ) ; 
    this->at(1) = (Vertex(1.0f , Quadrant::negativeLowerLeft ) ) ;  
}
Line :: Line (float scalingNumber ) {
    this->at(0) = ( Vertex(scalingNumber , Quadrant::positiveUpperRight ) ) ; 
    // print<float> (this->at(0).verticeMatrix[0][0] )   ; 
    // print<std::string>(" line initialized ");
    this->at(1) = (Vertex(scalingNumber , Quadrant::negativeLowerLeft ) ) ; 
    // print<float> (this->at(0)[1] ) ; 
}
// returns a pointer to the vertex
Vertex * Line::getCenterOfRotation (){
    Vertex * pointerToVertex = new Vertex ;  
    for (int i = 0 ; i < 4 ; i++ ) {
        pointerToVertex->verticeMatrix[i][i] = (*this)[0].verticeMatrix[i][3] ;  
    }
    return pointerToVertex ; 
} 
// void Line :: rotateLine( const glm::vec3 & orientationVec3 ) {
//     this->at(0).rotateVertex(orientationVec3 ) ; 
//     this->at(1).rotateVertex(orientationVec3 ) ; 
// }  
void Line :: rotateLineAlongAxis (const glm::vec3 & axis , float amount  ) {
    this->at(0).rotateVertexAlongAxis(axis , amount ) ; 
    this->at(1).rotateVertexAlongAxis(axis , amount ) ; 
}  
// void Line :: rotateLineAlongCOT(const glm::vec3 & orientationVec3 , Vertex & centerOfTranslation  ) {
//     Vertex connectingVertex  ; 
//     Vertex * pointerToVertex = getCenterOfRotation() ; 
//     for (int i = 0 ; i < 4 ; i++ ) {              //centerOfRotation     // center of translation 
//         (connectingVertex.verticeMatrix)[i][i] = ((*pointerToVertex).verticeMatrix[i][i] - centerOfTranslation[i]) ; 
//     }
//     connectingVertex.rotateVertex(orientationVec3)  ; 
//      for (int i =  0 ; i < 4 ; i++ ){
//         (*pointerToVertex).verticeMatrix[i][3] = connectingVertex[i] ; 
//      } 
//      delete pointerToVertex ; // deleting the dynamically allocated memory used in the function getCenterOfRotation()
// } 
void Line::renderMyself (SDL_Renderer * renderer  )

{   
    SDL_SetRenderDrawColor(renderer , 255 , 255 , 255 , 255) ; 
    SDL_RenderDrawLine(renderer ,(*this)[0][0] , (*this)[0][1] , (*this)[1][0] , (*this)[1][1] ) ; 
}
void Line :: processInput (const SDL_MouseMotionEvent & mouseEvent ) {
    if (mouseEvent.state &  SDL_BUTTON_LMASK ){
    float simultaneousMotionFactor {1};  
    float range {30.0f } ; 
    if (this->at(0).isTouchingVertex(range , mouseEvent)  ) {
    this->at(0).translate (glm::vec3 (mouseEvent.xrel*simultaneousMotionFactor , mouseEvent.yrel*simultaneousMotionFactor  ,0.0f  )) ; 
    }
    if (this->at(1).isTouchingVertex(range , mouseEvent )){
    this->at(1).translate (glm::vec3 (mouseEvent.xrel*simultaneousMotionFactor , mouseEvent.yrel*simultaneousMotionFactor  ,0.0f  )) ;  
    }
    this->at(0).translate (glm::vec3 (mouseEvent.xrel*simultaneousMotionFactor , mouseEvent.yrel*simultaneousMotionFactor  ,0.0f  )) ;  
    this->at(1).translate (glm::vec3 (mouseEvent.xrel*simultaneousMotionFactor , mouseEvent.yrel*simultaneousMotionFactor  ,0.0f  )) ;  
} }