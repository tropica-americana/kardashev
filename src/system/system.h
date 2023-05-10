#include <iostream>
#include <array>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "../Quadrant/Quadrant.h"
#include "../nothingClass /nothingClass.h"
#include "../myVertex/myVertex.h"
#include "../game/game.h"
#include <mutex>
#include <tuple>
#include <cmath>
#include <fstream>
#include <regex>
#include <cstdio>
#include <sstream>
#include <unordered_map>
#include <../myModel/myModel.h>
#include "../game/game.h"
class System : Game
{
      std::vector <myModel> models;
      void renderWorld ( SDL_Renderer * renderer ) ; 
};