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
#include <thread>
#include <chrono>
#include <mutex>
#include <regex>
#include <fstream>
using namespace std;
using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::string;
using std::regex;
using std::smatch;
using std::regex_search;
using std::ifstream;
using std::ofstream;

int main() {
    string filepath ; 
    regex rodRegex ( "\\-\\-\\-\\-\\-\\-\\-\\-\\-\\-\\-\\-*") ; 
    smatch match ; 
    cin >> filepath ;
    ifstream file(filepath);
    string line;
    vector <string> lines ; 
    while (!file.eof()) {
        getline(file, line);
        if ( line != ""  ){
            if (regex_search( line.cbegin() , line.cend() , match , rodRegex )){

            } 
            else  {
                lines.push_back (line) ; 
            }
        } ; 
        
    }
    for ( auto & item : lines ) {
        cout << item << endl ; 
    }
    file.close() ; 
    return 0;
}




