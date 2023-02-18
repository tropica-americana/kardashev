
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include <SDL2/SDL.h>
inline glm::vec4 createVec4 (float sizeOfElement ) {
   return  glm::vec4(glm::vec3 (sizeOfElement) , 1.0f ) ; 
}
inline glm::mat4 vec4ToMat4 (const glm::vec4 & vec4 )
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

inline void rotateVertex (glm::mat4 & vertex , const glm::vec3 & orientationVec3) {
    vertex = glm::rotate (vertex,
    orientationVec3.x ,glm::vec3(1.0f , 0.0f , 0.0f ) );
    vertex = glm::rotate (vertex,
    orientationVec3.y ,glm::vec3 (0.0f , 1.0f , 0.0f ) );
    vertex = glm::rotate (vertex,
    orientationVec3.z ,glm::vec3 ( 0.0f , 0.0f , 1.0f));  
    return ;
} 
template <typename T >
inline float compSum(T & vector ) {
    return glm::compSum (vector) ; 
}
inline void inlineConnectDotsAndRender (SDL_Renderer * renderer , std::vector<glm::mat4> & verticesArray )
{   
    int numvertices  = verticesArray.size () ; 
    auto  end = verticesArray.end() - 1 ;
    auto start = verticesArray.begin () ; 
    for (int i = 0 ; i <= numvertices  ; i++ ){
        if (i != 0 && i < numvertices  ){  
            // glm::vec4 vertex = mat4ToVec4 (verticesArray[i]) ;
            // glm::vec4 previousVertex = mat4ToVec4 (verticesArray[i-1]) ;
            float xPos = glm::compSum (verticesArray[i][0]) ; 
            float yPos = glm::compSum (verticesArray[i][1] ) ; 
            float previousXPos = glm::compSum (verticesArray[i-1][0] ) ; 
            float previousYPos = glm::compSum (verticesArray[i-1][1]) ; 
            SDL_RenderDrawLine(renderer , xPos , yPos , 
            previousXPos , previousYPos );

            } ; 
        if (i == numvertices )
        {
            SDL_RenderDrawLine(renderer , compSum(end[0]) , compSum(end[1]) , compSum(start[0]) , compSum(start[1]) );
        };
     }  
}
inline void scaleMat4 (glm::mat4 & model , glm::vec3 & vecPosition  ){
    for (int i = 0 ; i < 3 ; i++  ) {
        model[i][3] +=  vecPosition[i] ; 
    }
}
