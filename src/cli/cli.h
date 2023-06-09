#ifndef _CLI_H_
#define _CLI_H_
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <regex>
#include "../myModel/myModel.h"
#include <stdlib.h>
class CLI {
    public: 
    std::string command ; 
    CLI ()  = default; 
    ~CLI () = default ;
    void getTerminalText ( ) ; 
    void processCommand(std::vector <myModel * > & models) ; 
} ; 


#endif  