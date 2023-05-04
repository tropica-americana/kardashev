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

class System
{
      /*in  this class we will try to use std::unorderedmap to store the data 
      which is supposed to be the fastest way to access data */
      std::unordered_map<int , myModel> systemData;
      void addEntity ()  ; 
      void removeEntity () ; 
      void updateEntity () ; 
      myModel * getEntity () ; 
};