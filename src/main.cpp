#include <iostream>
#include <SDL2/SDL.h>
#include <vector> 
#include <map>
#include "./game/game.h"
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/string_cast.hpp>
#include <SDL2/SDL.h>
#include "./nothingClass /nothingClass.h" // do not change this 
#include "./myModel/MyModel.h"
#include <thread>
#include <chrono>
#include <mutex>
#include <regex>
using namespace std;
void processTerminalText(std::vector<myNothingClass *> &hector, Game &game) ; 
myModel createSphere() ; 
int main() {
    Game game;
    std::vector<myNothingClass * > hector ; 
    // myModel model1 = createSphere () ; 
    myModel model1 ; 
    model1.loadModel( "data.txt" , "sphere") ; 
    model1.currentMode =  "modify" ; 

    while (game.isRunning) {
        game.processInput();
        game.update();
        SDL_SetRenderDrawColor(game.renderer, 50, 50, 50, 255);
        SDL_RenderClear(game.renderer);
        //------------------------------------------------ write the code here for modifying ----------------------------
        model1.processInput(game.mouseevent , game.keyboardEvent );
        model1.renderMyself(game.renderer);
        game.render();
        SDL_Delay(10);
    }
    return 0;
}




