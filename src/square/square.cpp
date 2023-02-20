#include "square.h" // might give an linker error 
#include <algorithm>
static void display_model (const glm::mat4 &model , std::string &&content)  {
    std::cout<<std::endl; 
    std::cout<<content <<std::endl;
    std::cout<<glm::to_string (model[0]) <<std::endl;     
    std::cout<<glm::to_string (model[1]) <<std::endl;       
    std::cout<<glm::to_string (model[2]) <<std::endl;    
    std::cout<<glm::to_string (model[3]) <<std::endl; 
    std::cout<<std::endl;
} 
static void display_model (const glm::mat4 &model)  {
    std::cout<<std::endl;
    std::cout<<glm::to_string (model[0]) <<std::endl;     
    std::cout<<glm::to_string (model[1]) <<std::endl;       
    std::cout<<glm::to_string (model[2]) <<std::endl;    
    std::cout<<glm::to_string (model[3]) <<std::endl; 
    std::cout<<std::endl;
} 

void Square :: renderMyself (SDL_Renderer * renderer )
{
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
    inlineConnectDotsAndRender (renderer , squareverticesarray) ;
}
void Square:: fillVertices (){
    glm::mat4 vertex = vec4ToMat4(createVec4(squareWidth) ) ; 
    for (int i = 0 ; i < 4 ; i++  ) {
       vertex =  glm::rotate(vertex  , 1.57f , glm::vec3 (0.0f , 0.0f , 1.0f )) ;     
       squareverticesarray.push_back(vertex ) ; 
    }
}

Square::Square(float  squareWidth ): squareWidth{squareWidth} { 
    squarePosition.x = 100.0f ; 
    squarePosition.y = 30.0f ;
    squarePosition.z = 10.0f ; 
    //----------- filling the squareVerticesArray with the mat4 vertcises --------    
    fillVertices() ;                                                
}
void Square::handleMouseEvents (SDL_MouseMotionEvent &mouseEvent) {
    if (mouseEvent.state &  SDL_BUTTON_LMASK )
    {
        squarePosition.x +=  mouseEvent.xrel ; 
        squarePosition.y +=  mouseEvent.yrel ; 
        squareOrientation.x += mouseEvent.yrel  ;
        squareOrientation.y += mouseEvent.xrel ;  
    }
    
} 
