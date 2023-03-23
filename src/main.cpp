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
#include <chrono>
using namespace std ; 
static void inputThread(std::vector<nothingClass *>  & hector, Game &  game ) ;
static void getTerminalText(std::string & textTerminal , Game & game  ) ;
int main () {
    Game game ; 
    Line line(200.0f ) ;
    std::vector <nothingClass * > hector ; 
    hector.push_back(new Pyramid(100.0f )) ; 
    hector.push_back(new Pyramid(10.0f ) ) ; 
    std::thread processInput(inputThread ,std::ref(hector) , std::ref(game ) );
    while (game.isRunning){
        game.processInput() ; 
        game.update() ; 
        SDL_SetRenderDrawColor(game.renderer , 50, 50, 50, 255 ) ; 
        SDL_RenderClear(game.renderer) ; 
        for (auto  & item : hector ) {item->renderMyself(game.renderer ) ; }  
        game.render() ; 
        SDL_Delay (10) ;
    } 
    // processInput.join () ; 
    return 0 ; 
   } 

static void inputThread(std::vector<nothingClass *> & hector, Game & game ){
    std::string terminalText{"rotate 0"};
    std::chrono::milliseconds tenMilliSeconds(10) ; 
    SDL_MouseMotionEvent & mouseEvent = game.mouseevent ; //connecting the game.mouseevent 
    glm::vec3 orientationVector = glm::vec3 (0.0f , 0.0f ,0.0f );
    std::string stateText ; 
    std::thread getTerminalTextThread( getTerminalText, std::ref(terminalText) , std::ref(game));
    while (game.isRunning ){
        
        if (!terminalText.empty()){  
        if (mouseEvent.state &  SDL_BUTTON_LMASK ){
        orientationVector.x += mouseEvent.xrel;
        orientationVector.y += mouseEvent.yrel;
        orientationVector.z = 0 ;  
        // Convert degrees to radians
        orientationVector.x = glm::radians(orientationVector.x);
        orientationVector.y = glm::radians(orientationVector.y);
        if (terminalText == "rotate 0" && !hector.empty()) 
        {
            hector[0]->rotate(orientationVector);
        }
        if (terminalText == "end" ) 
        {
            game.isRunning = 0; 
        }        
        // Add more cases as needed
        }
    }
}
    //  getTerminalTextThread.join () ; 
}
static void getTerminalText(std::string  & terminalText , Game &game) {
    std::chrono::milliseconds hunderedMilliSeconds(100) ;
    while (game.isRunning){
        std::getline(std::cin, terminalText); 
        std::cout<< terminalText <<std::endl; 
        if (terminalText.empty() ) {std::cout<<"empty" <<std::endl ; }
        if (terminalText == "rotate 0"){std::cout<<terminalText<<endl ; }
        std::this_thread::sleep_for(hunderedMilliSeconds) ;     
     }    
}
 