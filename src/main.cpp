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
int main() {
    Game game;
    myModel model;
    std::vector<myNothingClass * > hector ; 
    // std::thread getTerminalTextThread(&Game::getTerminalText, &game);
    float radian = 0.01 ; 
    model.loadModel("data.txt" , "mySphereVertices") ; 
    model.scale(200.0) ; // --> do not remove 
    model.saveModel("data.txt" , "myScaledSecondModel") ; 
    
    while (game.isRunning) {
        game.processInput();
        game.update();
        SDL_SetRenderDrawColor(game.renderer, 50, 50, 50, 255);
        SDL_RenderClear(game.renderer);
        //------------------------------------------------ write the code here for modifying ----------------------------
        model.rotate(radian , 0.0,radian) ; 
        model.processInput(game.mouseevent);
        model.renderMyself(game.renderer);
        // processTerminalText(hector , game  );
        game.render();
        SDL_Delay(10);
    }
    return 0;
}


