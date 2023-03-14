#include "./Pyramid.h"

Pyramid::Pyramid (float length ) {
    
    verticesArray.at (0) = Vertex{0.0f , Quadrant::positiveUpperRight } ;
    verticesArray.at (1) = Vertex{length , Quadrant::positiveUpperRight } ; 
    verticesArray.at (2) = Vertex{length , Quadrant::positiveUpperLeft } ; 
    verticesArray.at (3) = Vertex{length , Quadrant::positiveLowerLeft } ;   
    verticesArray.at (4) = Vertex{length , Quadrant::positiveLowerRight  } ; 

} 
void Pyramid::rotate ( const glm::vec3 & orientationVec3  ) {

    // ------------------rotating along the xAxis ----------------------
    glm::vec3 axis {glm::vec3 (1.0f , 0.0f , 0.0f )} ; 
    float amount = orientationVec3.x ; 
    if (orientationVec3.x != 0.0f ) {
    verticesArray.at(1).rotateVertexAlongAxis(axis , amount );
    verticesArray.at(2).rotateVertexAlongAxis(axis , amount );
    verticesArray.at(3).rotateVertexAlongAxis(axis , -amount );
    verticesArray.at(4).rotateVertexAlongAxis(axis , -amount );}
    // ------------------rotating along the yAxis -----------------------
    if (orientationVec3.y != 0.0f ){
    axis = glm::vec3 (0.0f ,1.0f  , 0.0f ) ; 
    amount = orientationVec3.y ; 
    verticesArray.at(1).rotateVertexAlongAxis(axis , amount );
    verticesArray.at(2).rotateVertexAlongAxis(axis , -amount );
    verticesArray.at(3).rotateVertexAlongAxis(axis , -amount );
    verticesArray.at(4).rotateVertexAlongAxis(axis , amount );}
    // ----------------rotating along the zAxis --------------------------
    if (orientationVec3.z != 0.0f ) {
    axis = glm::vec3 (0.0f ,0.0f  , 1.0f ) ; 
    amount = orientationVec3.z ; 
    verticesArray.at(1).rotateVertexAlongAxis(axis , amount );
    verticesArray.at(2).rotateVertexAlongAxis(axis , -amount );
    verticesArray.at(3).rotateVertexAlongAxis(axis , amount );
    verticesArray.at(4).rotateVertexAlongAxis(axis , -amount ); }

} 
void Pyramid::renderMyself (SDL_Renderer * renderer ) {
    SDL_SetRenderDrawColor (renderer , 255 ,255 ,255 ,255 ) ;
    for (int i = 1 ; i < 4 ; i++) {
    SDL_RenderDrawLine (renderer , verticesArray.at(i)[0] , verticesArray.at(i)[1], 
    verticesArray.at(i+1)[0] , verticesArray.at(i+1)[1]) ; 
    // print ("looping draw line ") ; 
    }   
    SDL_RenderDrawLine(renderer , verticesArray.at(1)[0] , verticesArray.at(1)[1], 
    verticesArray.at(4)[0] , verticesArray.at(4)[1]);    
    for (int i = 1 ; i < 5 ; i++)
    {
    SDL_RenderDrawLine (renderer , verticesArray.at(0)[0] , verticesArray.at(0)[1], 
    verticesArray.at(i)[0] , verticesArray.at(i)[1]); 
    }
} 
void Pyramid::processInput (const SDL_MouseMotionEvent & mouseEvent  ){
    float simultaneousMotionFactor {1.0f } ; 
    if (mouseEvent.state &  SDL_BUTTON_LMASK ){for (int i = 0 ; i < 5 ; i++)
    {verticesArray.at(i).translate (glm::vec3 (mouseEvent.xrel*simultaneousMotionFactor , mouseEvent.yrel*simultaneousMotionFactor  ,0.0f  )) ;  }}    
}
void Pyramid::translate (const glm::vec3 & vec3 ) {
    for (int i = 0 ; i < 5 ; i++ ) 
    {
    verticesArray.at(i).translate (vec3 ) ; 
    }
}
void Pyramid :: displaySelf () {
    display_model (verticesArray.at(0).verticeMatrix ) ; 
    display_model (verticesArray.at(1).verticeMatrix ) ; 
    display_model (verticesArray.at(2).verticeMatrix ) ; 
    display_model (verticesArray.at(3).verticeMatrix ) ;  
    display_model (verticesArray.at(3).verticeMatrix ) ; 
} 





