#ifndef _GLMHANDLER_H_
#define _GLMHANDLER_H_
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include <SDL2/SDL.h>
// ----------einstein never needed a compiler and always trusted his brain ---------------------------------------------------
inline glm::vec4 createVec4 (float sizeOfElement ) {
   return  glm::vec4(glm::vec3 (sizeOfElement) , 1.0f ) ; 
}
inline glm::mat4  vec4ToMat4 (const glm::vec4 & vec4 )
{
    return glm::mat4( 
    vec4.x, 0, 0, 0, 
    0, vec4.y, 0, 0, 
    0, 0, vec4.z, 0, 
    0, 0, 0, vec4.w 
);
}
inline glm::mat4 vec4ToMat4 (const glm::vec4 &&vec4 )
{
    return glm::mat4( 
    vec4.x, 0, 0, 0, 
    0, vec4.y, 0, 0, 
    0, 0, vec4.z, 0, 
    0, 0, 0, vec4.w 
);
}

inline glm::vec4  mat4ToVec4 (glm::mat4 &model){
    glm::vec4 vertex =  ( model * glm::vec4 (1.0f , 1.0f  , 1.0f , 1.0f ) ) ;  
    return vertex ; 
}
inline glm::vec4  mat4ToVec4 (glm::mat4 &&model){
    glm::vec4 vertex =  ( model * glm::vec4 (1.0f , 1.0f  , 1.0f , 1.0f ) ) ;  
    return vertex ; 
}


static void rotateVertex (glm::mat4 & vertex , const glm::vec3 & orientationVec3) {
    vertex = glm::rotate (vertex,
    orientationVec3.x ,glm::vec3(1.0f , 0.0f , 0.0f ) );
    vertex = glm::rotate (vertex,
    orientationVec3.y ,glm::vec3 (0.0f , 1.0f , 0.0f ) );
    vertex = glm::rotate (vertex,
    orientationVec3.z ,glm::vec3 ( 0.0f , 0.0f , 1.0f));  
    return ;
} 
// -----------only designed for mat4 --------------------------------------------------------
inline float compSum( const glm::vec4 & vector ) {
    float sum = 0.0f ; 
    for (int i = 0 ; i < 4 ; i++ )  sum += vector[i]  ; 
    return sum ;
}
inline float compSum( const glm::vec3 & vector )
{
    float sum = 0.0f ; 
    for (int i = 0 ; i < 3 ; i++ )  sum += vector[i]  ; 
    return sum ; 
}
static  void staticConnectDotsAndRender (SDL_Renderer * renderer ,const  std::vector<glm::mat4> & verticesArray )
{   
    int numvertices  = verticesArray.size () ; 
    auto  end = verticesArray.end() - 1 ;
    auto start = verticesArray.begin () ; 
    for (int i = 0 ; i <= numvertices  ; i++ ){
        if (i != 0 && i < numvertices  ){  
            float xPos = compSum(verticesArray[i][0]) ;     
            float yPos = compSum (verticesArray[i][1] ) ; 
            float previousXPos = compSum (verticesArray[i-1][0] ) ; 
            float previousYPos = compSum (verticesArray[i-1][1]) ; 
            SDL_RenderDrawLine(renderer , xPos , yPos , 
            previousXPos , previousYPos );

            } ; 
        if (i == numvertices )
        {
            SDL_RenderDrawLine(renderer , compSum((*end)[0]) , compSum((*end)[1]) , compSum((*start)[0]) , compSum((*start)[1]) );
        };
     }  
}

inline void scaleMat4 (glm::mat4 & model , glm::vec3 & vecPosition  ){
    for (int i = 0 ; i < 3 ; i++  ) {
        model[i][3] +=  vecPosition[i] ; 
    }
}

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
// the question is wheather you can change the center of rotation of a vertex and rotate the 
// object around the center vertex 
#endif // !_GLMHANDLER_H_