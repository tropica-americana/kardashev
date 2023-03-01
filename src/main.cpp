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
    Line line ; 
    while (game.isRunning){
        if (SDL_GetTicks() >= 10000) game.isRunning = false ; 
       
        myRenderFunction( ()[&game]{
            line.renderMyself (game.renderer ) ; 
        }) 
        game.render() ; 
        SDL_Delay (10) ; 
    }
    return 0 ; 
     }