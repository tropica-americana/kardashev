#include "system.h"

void System::addEntity()
{
    
}

void enterCreatorMode () {
    myModel model ; 
    Game game ; 
    bool creatorModeOn = false  ; 
    std::cout << "Enter Creator Mode [Y/N]" << std::endl;
    std::string input;
    std::string filePath ; 
    std::cin >> input;
    if (input == "Y" || input == "y") {
        creatorModeOn = true ;
        std::cout << "Enter the name of the model" << std::endl;
        std::cin >> input;
        std::cout << "Enter the name of the file where the model will be saved" << std::endl;
        std::cin >> filePath;
        if (model.loadModel(filePath , input ) == true) {
            std::cout << "Model loaded" << std::endl;

        } 
        while ( creatorModeOn){
            game.processInput();
            if (game.keyboardEvent.keysym.sym == SDLK_ESCAPE) {
                creatorModeOn = false ; 
                std::cout << "Creator Mode Off do you want to save model " << std::endl;
                std::cin >> input;
                if (input == "Y" || input == "y") {
                    model.saveModel();
                    std::cout << "Model saved" << std::endl;
                }
                

            }

            game.update();
            game.render();
        }
         }   
}