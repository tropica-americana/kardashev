#ifndef _renderinglayer_
#define _renderinglayer_ 

#include <iostream>
#include <array>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "../Quadrant/Quadrant.h"
#include "../nothingClass /nothingClass.h"
#include "../myVertex/myVertex.h"
#include <mutex>
#include <tuple>
#include <cmath>
#include <fstream>
#include <regex>
#include <unordered_map>
using std::cout ; 
using std::cin ; 
using std::vector ; 

// this function will prove useful to render the vertices of a model as connected dots ;  
void renderVerticesAsConnectedDots (  SDL_Renderer * renderer , vector <myVertex * > vectorToPointersOfVertices ) {
	// iterating from the first item to the last item and than joining them 
	for ( int i = 0 ; i < vectorToPointersOfVertices.size () - 1 ; i++   ) {

		SDL_RenderDrawLine ( renderer , vectorToPointersOfVertices[i]-> x , vectorToPointersOfVertices[i]-> y , vectorToPointersOfVertices[i+1] -> x  , vectorToPointersOfVertices[i+1]-> y )  
	}  
}

#endif 
