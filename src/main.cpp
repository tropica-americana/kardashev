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
#include "./Database/Database.h"
#include "./Model/Model.h"
#include <thread>
#include <chrono>
#include <mutex>
#include <regex>
using namespace std;
void processTerminalText(std::vector<nothingClass *> &hector, Game &game) ; 
int main() {
    Game game;
    Model model;
    std::vector<nothingClass * > hector ; 
    std::thread getTerminalTextThread(&Game::getTerminalText, &game);
    while (game.isRunning) {
        game.processInput();
        game.update();
        SDL_SetRenderDrawColor(game.renderer, 50, 50, 50, 255);
        SDL_RenderClear(game.renderer);
        //------------------------------------------------ write the code here for modifying ----------------------------
        model.rotate(glm::vec3 (0.0f, 1.0f,0.0f)) ; 
        model.processInput(game.mouseevent);
        model.renderMyself(game.renderer);
        // processTerminalText(hector , game  );
        game.render();
        SDL_Delay(10);
    }
    return 0;
}


