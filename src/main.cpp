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
#include "./myModel/myModel.h"
#include "./mathematicalLayer/mathematicalLayer.h"
#include <thread>
#include <chrono>
#include <mutex>
#include <regex>
using namespace std;
myModel createSphere() ; 
void renderSolarSystem () ; 
void imageSystem ( std::string path , std::string pathToTtf ) ;
void textsystem ( std::string text ) ; 
int main() { 
    // textsystem("this is a text system "  ) ; 
    imageSystem ( "this is a text system " , "/Users/sachinjain/Desktop/gamemachine/assets/fonts/arial.ttf") ; 
    return 0;
}




