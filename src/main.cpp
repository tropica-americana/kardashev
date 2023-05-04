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
    myModel model1;
    myModel model2;
    myModel model3;
    std::vector<myNothingClass * > hector ; 
    // std::thread getTerminalTextThread(&Game::getTerminalText, &game);
    float radian = 0.01 ; 
    float scalingNumber = 100.0f ; 
    model1.loadModel("data.txt" , "myCuboidModel") ; 
    model1.currentMode = "modify"  ; 
    model1.scale(scalingNumber) ;
    // model2.loadModel("data.txt" , "tetraPointedCuboid") ;
    model2.loadModel("data.txt" , "myCuboidModel") ;
    model2.currentMode = "modify"  ;
    model2.scale(scalingNumber) ;
    model2.translate(0.0 , 1000.0f , 0.0) ;
    // model3.loadModel("data.txt" , "biPointedCuboid") ;
    // model3.currentMode = "modify"  ;
    // model3.scale(scalingNumber) ;
    // model3.translate(1000.0 , 0.0f , 0.0) ;
    model1.joinWithMyModel(model2) ;
    // model1.joinWithMyModel(model3) ;
    while (game.isRunning) {
        game.processInput();
        game.update();
        SDL_SetRenderDrawColor(game.renderer, 50, 50, 50, 255);
        SDL_RenderClear(game.renderer);
        //------------------------------------------------ write the code here for modifying ----------------------------
        // model.rotate(0.0 , radian, 0.0 )  ; 
        model1.processInput(game.mouseevent , game.keyboardEvent );
        model1.renderMyself(game.renderer);
        game.render();
        SDL_Delay(10);
    }
    return 0;
}




