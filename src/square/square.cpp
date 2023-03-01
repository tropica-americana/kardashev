#include "square.h" // might give an linker error 
#include <algorithm>
///

void Square :: renderMyself (SDL_Renderer * renderer )
{
    // clearing all the vertices and adding them according to the new square attributes -- 
    fillVertices () ; 
    // -----------rotating each vertices according to square orientation -----------------------
    std::for_each (squareverticesarray.begin () , squareverticesarray.end () , 
    [this] (glm::mat4 & vertex){
        rotateVertex(vertex , squareOrientation);
    }) ;
    //----------- scaling each vertice according to  square position -------------------
    for_each (squareverticesarray.begin () , squareverticesarray.end () , 
    [this] (glm::mat4 & vertex){
        scaleMat4(vertex , squarePosition) ;   
    }) ;
    // ----------draw and join the vertices ------------------------------------------------------------------------
    staticConnectDotsAndRender(renderer , squareverticesarray) ;

}
void Square:: fillVertices (){
    squareverticesarray.clear() ; 
    float squareWidthStack ; 
// -- dealing with negative zAxis and scaling the relativeSquareWidth -------------
    if (squarePosition[2] < 0 ) { 
        squareWidthStack = squareWidth * (squareWidth / (squareWidth -  (squarePosition[2]) ))  ; 
        } 
// -- dealing with positive zAxis and scaling the relativeSqaureWidth  ------------        
    else if ((squarePosition[2]) >= 0  )
    {
        squareWidthStack = squareWidth * (squareWidth / (squareWidth +  (squarePosition[2]) )) ;
    }
// --  creating and popping the sqaurevertices onto the squareverticesarray --------
    glm::mat4 vertex = vec4ToMat4(createVec4(squareWidthStack) ) ; 
    for (int i = 0 ; i < 4 ; i++  ) {
       vertex =  glm::rotate(vertex  , 1.57f , glm::vec3 (0.0f , 0.0f , 1.0f )) ;     
       squareverticesarray.push_back(vertex ) ; 
     

}
}
Square::Square(float  squareWidth ): squareWidth{squareWidth} { 
    squarePosition.x = 100.0f ; 
    squarePosition.y = 30.0f ;
    squarePosition.z = 10.0f ;     
}
void Square::handleMouseEvents (SDL_MouseMotionEvent &mouseEvent , SDL_MouseWheelEvent &wheelEvent ) {
    if (mouseEvent.state &  SDL_BUTTON_LMASK )
    {
        squarePosition.x +=  mouseEvent.xrel ; 
        squarePosition.y +=  mouseEvent.yrel ; 
    }
    // if(wheelEvent.y > 0) // scroll up
    //      squarePosition.z += 10 ; 
    // else if(wheelEvent.y < 0) // scroll down
    //      squarePosition.z -= 10 ;    
} 
