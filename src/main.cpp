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

using namespace std;
static void inputThread(std::vector<nothingClass *> &hector, Game &game, std::mutex &mtx);
static void getTerminalText(std::string &textTerminal, Game &game, std::mutex &mtx);

int main() {
    Game game;
    Line line(200.0f);
    std::vector<nothingClass *> hector;
    hector.push_back(new Pyramid(500.0f));
    std::mutex mtx;
    std::thread getTerminalTextThread(&Game::getTerminalText, &game);

    while (game.isRunning) {
        game.processInput();
        game.update();
        SDL_SetRenderDrawColor(game.renderer, 50, 50, 50, 255);
        SDL_RenderClear(game.renderer);
        for (auto &item : hector) 
        { 
            item->renderMyself(game.renderer); 
        }
        game.render();
        SDL_Delay(10);
    }
    return 0;
}











// static void inputThread(std::vector<nothingClass *> &hector, Game &game, std::mutex &mtx) {
//     std::string terminalText{""};
//     std::chrono::milliseconds tenMilliSeconds(10);
//     SDL_MouseMotionEvent &mouseEvent = game.mouseevent;
//     glm::vec3 orientationVector = glm::vec3(0.0f, 0.0f, 0.0f);
//     std::string stateText;
//     std::thread getTerminalTextThread(getTerminalText, std::ref(terminalText), std::ref(game), std::ref(mtx));
//     while (game.isRunning == true || game.isRunning == 1 ) {
//         {
//             std::unique_lock<std::mutex> lock(mtx);
//             if (!terminalText.empty()) {
//                 if (mouseEvent.state & SDL_BUTTON_LMASK) {
//                     orientationVector.x += mouseEvent.xrel;
//                     orientationVector.y += mouseEvent.yrel;
//                     orientationVector.z = 0;
//                     orientationVector.x = glm::radians(orientationVector.x)/4000;
//                     orientationVector.y = glm::radians(orientationVector.y)/4000;
//                     if (terminalText == "rotate 0" && !hector.empty()) {
//                         hector[0]->rotate(orientationVector);
//                     }
//                     if (terminalText == "end") {
//                         game.isRunning = false;
//                     }
//                     if (terminalText == "translate 0" && !hector.empty()) {
//                         orientationVector.x += mouseEvent.xrel;
//                         orientationVector.y += mouseEvent.yrel;
//                         hector[0]->translate(glm::vec3 (orientationVector));
//                     }
//                 }
//             }
//         }
//     }
//     // getTerminalTextThread.join();
// }
