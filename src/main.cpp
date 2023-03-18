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
#include "./nothingClass /nothingClass.h" // do not change this 
#include <thread>
using namespace std ; 
static void inputThread(std::vector<nothingClass *> &hector, const Game &game ) ; 
int main () {
    Game game ; 
    Line line(200.0f ) ;
    std::vector <nothingClass * > hector ; 
    hector.push_back(new Pyramid(100.0f )) ; 
    hector.push_back(new Pyramid(10.0f ) ) ; 
    std::thread processInput(inputThread ,hector , game  ) ; 
    while (game.isRunning){
        game.processInput() ; 
        game.update() ; 
        SDL_SetRenderDrawColor(game.renderer , 50, 50, 50, 255 ) ; 
        SDL_RenderClear(game.renderer) ; 
        for (auto  & item : hector ) {item->renderMyself(game.renderer ) ; }  
        game.render() ; 
        SDL_Delay (10) ;
    } 
    processInput.join () ; 
    return 0 ; 
   
    } 


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

    static void inputThread(std::vector<nothingClass *> &hector, const Game &game ){
    std::string terminalText;
    SDL_MouseMotionEvent mouseEvent = game.mouseevent ; 
    while (game.isRunning) {
        std::getline(std::cin, terminalText); // Read input from the terminal

        if (terminalText.empty()) break; // Stop reading input on second return/enter press

        glm::vec3 orientationVector;

        orientationVector.x += mouseEvent.xrel;
        orientationVector.y += mouseEvent.yrel;

        // Convert degrees to radians
        orientationVector.x = glm::radians(orientationVector.x);
        orientationVector.y = glm::radians(orientationVector.y);

        if (terminalText == "rotate 0" && !hector.empty()) {
            hector[0]->rotate(orientationVector);
        }
        // Add more cases as needed
    }
}