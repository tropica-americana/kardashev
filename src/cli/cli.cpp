#include "cli.h"

void CLI::getTerminalText ( ) {
    std::string inputText ;
    // system("clear") ;
    std::getline ( std::cin  , inputText) ; 
    // error prone area above 
    command = inputText ;  
}
void CLI::processCommand( std::vector <myModel * > & models ) {

    std::smatch match ; 
    // below we will create a bunch of regular expressions for each type of terminal command 
    // the first word is the command 
    // the second word is the if statements 
    // the third word should be empty for these types of command 
    std::regex ifNameStatementRegex ("if\\s*\\(\\s*name\\s*==\\s*(\\w+)\\s*\\)") ;
    std::regex notIfNameStatementRegex ( "if\\s*\\(\\s*name\\s*!=\\s*(\\w+)\\s*\\)") ; 
    std::regex modifyByKeyRegex ("if\\s*\\(\\s*(\\w+)\\s*==\\s*(\\w+)\\s*\\)" ) ;
    std::regex notModifyBykeyRegex ("if\\s*\\(\\s*(\\w+)\\s*!=\\s*(\\w+)\\s*\\)") ;  
    std::regex rmCommandRegex ("\\s*rm\\s*") ; 
    // name is in capturing group 1 
    //----------------------------------------------------------------------------------
    //getting the first word from the command string 
    // multiple if statements for the differnet commad types 
    if ( std::regex_search( command.cbegin() , command.cend() , match , rmCommandRegex  ) ){
        if (std::regex_search( command.cbegin() , command.cend() , match , ifNameStatementRegex  )) {
            for ( auto & model : models ) {
                std::cout << "break point  1 cli " << std::endl ;
                if(model->modelName == match[1] )
                model->stringMap["isRendering"] = "false" ;
                std::cout << "removed " << match[1] << std::endl ; 
            }
        }
        if (std::regex_search( command.cbegin() , command.cend() , match , notIfNameStatementRegex  )) {
            for ( auto & model : models ) {
                std::cout << "break point  2 cli " << std::endl ;
                if(model->modelName != match[1] )
                model->stringMap["isRendering"] = "false" ; 
                std::cout << "removed " << match[1] << std::endl ;
            }
        }
        if (std::regex_search( command.cbegin() , command.cend() , match , modifyByKeyRegex  )) {
            for ( auto & model : models ) {
                if(model->stringMap[match[1]] == match[2] )
                model->stringMap["isRendering"] = "false" ; 
            }
        }        

    }

    std::cout <<"command processed " << std::endl ;
    // std::cout << "command is " << command << std::endl ; 
}