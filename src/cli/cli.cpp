
#include "cli.h"

void CLI::getTerminalText ( ) {
    std::string inputText ;
    // system("clear") ;
    std::getline ( std::cin  , inputText) ; 
    // error prone area above 
    command = inputText ;  
}

// --------------this is the most important function in the whole class -----------------

void CLI::processCommand( std::vector <myModel * > & models ) {
    processRmCommand ( models ) ;
    processChangeCommand ( models ) ;
    processShowCommand ( ) ;
    std::cout <<"command processed " << std::endl ;
}

// ----------------------------------------------------------------------------------------

void CLI::processRmCommand (std::vector <myModel * > & models){
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
}
void CLI::processChangeCommand(std::vector <myModel * > & models ){
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
}
void CLI::processShowCommand(){
    // showing all the keys and their states in the sting map for any model 
    if ( std::regex_search( command.cbegin() , command.cend() , match ,showAllTheCommandsRegex  )){
        std::cout << "showing all the commands" << std::endl ;
        std::cout << "isRendering  --> true / false " <<std::endl ; 
        std::cout << "input --> true / false "  <<std::endl ;

    }
}
