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

void processTerminalText(std::vector<nothingClass *> &hector, Game &game) {
    std::string input;
    input = game.terminalText ; 
    SDL_MouseMotionEvent &mouseEvent = game.mouseevent ; 
    std::regex rotate_pattern(R"(rotate\s+(\d+))");
    std::regex translate_pattern(R"(translate\s+(\d+))");
    std::regex process_input_pattern("processInput");
    std::regex end_pattern("end");

    std::smatch match;
    glm::vec3 orientationVector = glm::vec3(0.0f, 0.0f, 0.0f);

    {
        if (!input.empty()) {
            if (mouseEvent.state & SDL_BUTTON_LMASK) {
                orientationVector.x += mouseEvent.xrel;
                orientationVector.y += mouseEvent.yrel;
                orientationVector.z = 0.1;
                orientationVector.x = glm::radians(orientationVector.x) / 4000;
                orientationVector.y = glm::radians(orientationVector.y) / 4000;

                if (std::regex_search(input, match, rotate_pattern)) {
                    int index = std::stoi(match[1].str());
                    if (index >= 0 && index < hector.size()) {
                        hector[index]->rotate(orientationVector);
                    } 
                    else 
                    {
                        std::cout << "No such command found." << std::endl;
                    }
                } else if (std::regex_search(input, match, translate_pattern)) {
                    int index = std::stoi(match[1].str());
                    if (index >= 0 && index < hector.size()) {
                        orientationVector.x += mouseEvent.xrel;
                        orientationVector.y += mouseEvent.yrel;
                        hector[index]->translate(orientationVector);
                    } else {
                        std::cout << "No such command found." << std::endl;
                    }
                } else if (std::regex_search(input, match, process_input_pattern)) {
                    for (nothingClass *obj : hector) {
                        obj->processInput(mouseEvent);
                    }
                } else if (std::regex_search(input, match, end_pattern)) {
                    game.isRunning = false;
                } else {
                    std::cout << "No such command found." << std::endl;
                }
            }
        }
    }
}

