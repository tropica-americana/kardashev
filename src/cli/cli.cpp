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
    std::string extractedModelName ; 
    std::string lhsString  ;
    std::string rhsString ;  
    // below we will create a bunch of regular expressions for each type of terminal command 
    // the first word is the command 
    // the second word is the if statements 
    // the third word should be empty for these types of command 
    std::regex ifNameStatementRegex ("if\\s*\\s*name\\s*==\\s*(\\w+)\\s*") ;
    std::regex notIfNameStatementRegex ( "if\\s*\\s*name\\s*!=\\s*(\\w+)\\s*") ; 
    std::regex modifyByKeyRegex ("if\\s*\\s*(\\w+)\\s*==\\s*(\\w+)\\s*" ) ;
    std::regex notModifyBykeyRegex ("if\\s*\\s*(\\w+)\\s*!=\\s*(\\w+)\\s*") ;  
    std::regex changeKeyRegex ("\\s+([A-Za-z0-9\\.]+)\\s+\\->\\s+([A-Za-z0-9\\.]+)\\s+") ; 
    std::regex rmCommandRegex ("\\s*rm\\s*") ; 
    std::regex changeCommandRegex ( "\\s*change\\s*") ; 
    std::regex addCommandRegex ("\\s*add\\s*") ;
    std::regex joinCommandRegex ("\\s*join\\s*") ;
    // name is in capturing group 1 
    //----------------------------------------------------------------------------------
    //getting the first word from the command string 
    // multiple if statements for the differnet commad types 
    if ( std::regex_search( command.cbegin() , command.cend() , match , rmCommandRegex  ) ){
        if (std::regex_search( command.cbegin() , command.cend() , match , ifNameStatementRegex  )) {
            for ( auto & model : models ) {
                if(model->modelName == match[1] )
                model->stringMap["isRendering"] = "false" ;
                
            }
        }
        if (std::regex_search( command.cbegin() , command.cend() , match , notIfNameStatementRegex  )) {
            for ( auto & model : models ) {
                
                if(model->modelName != match[1] )
                model->stringMap["isRendering"] = "false" ; 
                            }
        }
        if (std::regex_search( command.cbegin() , command.cend() , match , modifyByKeyRegex  )) {
            for ( auto & model : models ) {
                if(model->stringMap[match[1]] == match[2] )
                model->stringMap["isRendering"] = "false" ; 
            }
        }        

    }
    if ( std::regex_search( command.cbegin() , command.cend() , match , changeCommandRegex  ) ){
        if ( std::regex_search(command.cbegin() , command.cend() , match, ifNameStatementRegex)){
            std::cout << "if name statement" << std::endl ;
            std::smatch match2 ; 
            for ( auto & model : models ) {
                if ( model->modelName == match[1] ) {
                    if (std::regex_search( command.cbegin() , command.cend() , match2 , changeKeyRegex  )) {
                       { model->stringMap[match2[1]] = match2[2] ;
                        }
                    }
                }
            }   
        }
        else if ( std::regex_search(command.cbegin() , command.cend() , match, notIfNameStatementRegex)){
            std::cout << "not if name statement" << std::endl ;
            std::smatch match2 ; 
            for ( auto & model : models ) {
                if ( model->modelName != match[1] ) {
                    if (std::regex_search( command.cbegin() , command.cend() , match2 , changeKeyRegex  )) {
                        {model->stringMap[match2[1]] = match2[2] ;
                        }
                    }
                }
            }
        }
        else if ( std::regex_search(command.cbegin() , command.cend() , match, modifyByKeyRegex)){
            std::cout << "modify by key" << std::endl ;
            std::smatch match2 ; 
            for ( auto & model : models ) {
                if ( model->stringMap[match[1]] == match[2] ) {
                    if (std::regex_search( command.cbegin() , command.cend() , match2 , changeKeyRegex  )) {
                      { model->stringMap[match2[1]] = match2[2] ;
                        }
                    }
                }
            }
        }
        else if ( std::regex_search(command.cbegin() , command.cend() , match, notModifyBykeyRegex)){
            std::cout << "not modify by key" << std::endl ;
            std::smatch match2 ; 
            for ( auto & model : models ) {
                if ( model->stringMap[match[1]] != match[2] ) {
                    if (std::regex_search( command.cbegin() , command.cend() , match2 , changeKeyRegex  )) {
                        {model->stringMap[match2[1]] = match2[2] ;
                        }
                    }
                }
            }
        }
    }

    std::cout <<"command processed " << std::endl ;
}