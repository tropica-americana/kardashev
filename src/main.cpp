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
    Line line(200.0f);
    std::vector<nothingClass *> hector;
    hector.push_back(new Pyramid(100.0f));
    hector.push_back(new Pyramid(1000.0f));
    std::mutex mtx;
    std::thread getTerminalTextThread(&Game::getTerminalText, &game);

    while (game.isRunning) {
        game.processInput();
        game.update();
        SDL_SetRenderDrawColor(game.renderer, 50, 50, 50, 255);
        SDL_RenderClear(game.renderer);
        for (auto & item : hector )
        {
            // item->processInput(game.mouseevent) ;
            // item->translate(glm::vec3 (1.0f));
            item-> rotate(glm::vec3 (0.1f , 0.0f , 0.0f )) ;
        }
        processTerminalText(hector , game  );
        for (auto &item : hector) 
        { 
            item->renderMyself(game.renderer); 
        }
        game.render();
        SDL_Delay(10);
    }
    return 0;
}


