#include <iostream>
#include <SDL2/SDL.h>
#include <vector> 
#include <map>
#include "./square/square.h"
#include "./game/game.h"
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/string_cast.hpp>
#include <SDL2/SDL.h>
#include "./Line/Line.h"
#include "./Pyramid/Pyramid.h"
using namespace std ; 

template <typename T>
void myRenderFunction (T function ){
    function () ;
};
int main () {
    // Game game ; 
    // Square square(100.0) ; 
    // while (game.isRunning){
    //     if (SDL_GetTicks() >= 10000) game.isRunning = false ; 
    //     game.processInput() ; 
    //     game.update()  ; 
    //     // MyRenderFunction(
    //     //     [&game , &square ] (){
    //     //         SDL_SetRenderDrawColor(game.renderer , 21,
    //     //         21,21,255 ) ; 
    //     //         SDL_RenderClear(game.renderer ) ; 
    //     //         SDL_SetRenderDrawColor(game.renderer  , 255,255,255,255);
    //     //         square.renderMyself(game.renderer ) ; 
    //     //         square.handleMouseEvents(game.mouseevent , game.wheelEvent);
    //     //         SDL_RenderPresent(game.renderer ) ; 
    //     //     }
    //     // );
    //     myRenderFunction( ()[&game]{}) 
    //     game.render() ; 
    //     SDL_Delay (10) ; 
    Game game ; 
    Line line(200.0f ) ;
    // line[0].translate (glm::vec3(10.0f , 10.0f , 10.0f )) ; 
    // line[1].translate (glm::vec3(10.0f , 10.0f , 10.0f )) ;  
    Pyramid pyramid (100.0f ) ; 
    pyramid.translate (glm::vec3(100.0f , 100.0f , 100.0f  )) ; 
    pyramid.displaySelf () ; 
    while (game.isRunning){
        game.processInput() ; 
        game.update() ; 
        myRenderFunction([&game , &line , &pyramid ]{
        SDL_SetRenderDrawColor(game.renderer , 50, 50, 50, 255 ) ; 
        SDL_RenderClear(game.renderer) ; 
        // line.processInput(game.mouseevent) ; 
        // line.rotateLineAlongAxis(glm::vec3 (0.0f , 1.0f , 0.0f ) , 0.14f ) ; 
        // line.renderMyself (game.renderer ) ; 

        pyramid.processInput (game.mouseevent) ; 
        pyramid.rotate(glm::vec3 (0.01f , 0.01f , 0.01f )) ; 
        pyramid.renderMyself (game.renderer) ; 

        // pyramid.translate(glm::vec3 (1.0f , 0.0f , 0.0f )) ;
        // pyramid.displaySelf() ; 
        
        game.render() ; 
        SDL_Delay (10) ;
        }) ;  
    } 
    return 0 ; } 