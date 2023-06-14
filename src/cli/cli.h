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
    std::smatch match ; 
    std::string extractedModelName ; 
    std::string lhsString  ;
    std::string rhsString ;   
    std::regex ifNameStatementRegex {"if\\s*\\s*name\\s*==\\s*(\\w+)\\s*"} ;
    std::regex notIfNameStatementRegex { "if\\s*\\s*name\\s*!=\\s*(\\w+)\\s*"} ; 
    std::regex modifyByKeyRegex {"if\\s*\\s*(\\w+)\\s*==\\s*(\\w+)\\s*"} ;
    std::regex notModifyBykeyRegex {"if\\s*\\s*(\\w+)\\s*!=\\s*(\\w+)\\s*"} ;  
    std::regex changeKeyRegex {"\\s+([A-Za-z0-9\\.]+)\\s+\\->\\s+([A-Za-z0-9\\.]+)\\s+"} ; 
    std::regex rmCommandRegex {"\\s*rm\\s*"} ; 
    std::regex changeCommandRegex { "\\s*change\\s*"} ; 
    std::regex addCommandRegex {"\\s*add\\s*"} ;
    std::regex joinCommandRegex {"\\s*join\\s*"} ;
    std::regex showAllTheCommandsRegex  {"\\s*show\\s*"} ;
 
    CLI ()  = default; 
    ~CLI () = default ;
    void getTerminalText ( ) ; 
    void processCommand(std::vector <myModel * > & models) ; 
    void processRmCommand(std::vector <myModel * > & models) ;
    void processChangeCommand(std::vector <myModel * > & models) ;
    void processShowCommand() ; 
} ; 


#endif  