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
    model.addVertex(Vertex(glm::vec3 (0.01f )));
    model.addVertex(Vertex(glm::vec3 (150.0f , 250.0f ,350.0f )));
    model.addVertex(Vertex(glm::vec3 (12.0f , 180.0f ,220.0f )));
    model.addVertex(Vertex(glm::vec3 (800.0f , 160.0f ,280.0f )));
    model.addVertex(Vertex(glm::vec3 (50.0f , 100.0 , 130.0f )));
    // hector.emplace_back(&model);
    std::thread getTerminalTextThread(&Game::getTerminalText, &game);

    while (game.isRunning) {
        game.processInput();
        game.update();
        SDL_SetRenderDrawColor(game.renderer, 50, 50, 50, 255);
        SDL_RenderClear(game.renderer);
        //------------------------------------------------ write the code here for modifying ----------------------------
        model.rotate(glm::vec3 (0.01f, 0.01f,0.01f)) ; 
        model.processInput(game.mouseevent);
        model.renderMyself(game.renderer);
        // processTerminalText(hector , game  );
        game.render();
        SDL_Delay(10);
    }
    return 0;
}


