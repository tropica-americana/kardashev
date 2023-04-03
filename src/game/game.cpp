#include <iostream>
#include "game.h"
#include "../glmHandler/glmHandler.h"
#include <string>
void Game ::initialize()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0 )
    {
        std::cerr << "problem initializing everything " << std::endl;
        isRunning = false ; 
        return;
    }
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0 , &displayMode);
    window = SDL_CreateWindow(NULL /*NULL AS THE TITLE */,SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
    
    (displayMode).w
    ,
    (displayMode).h
    , SDL_WINDOW_BORDERLESS); // MIGHT GIVE AN ERROR
    if (window == 0 ){isRunning = false ;std::cout<<"probleme windowe "<<std::endl; ;return ; }
    renderer = SDL_CreateRenderer(window, NULL, 0);
    if (renderer == 0 ){isRunning = false ; 
    std::cout<<"probleme renderere"<<std::endl;
    SDL_SetWindowFullscreen(window  , SDL_WINDOW_FULLSCREEN) ; 

    // --------------to render text -----------------------------------------------------   
}}

void Game ::processInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) // fills the event with all kinds of important information about the current state of keyboard and mouse
    {
        switch (event.type)
        {
            case SDL_QUIT :  
                isRunning = false ; 
                break ; 
            
            case SDL_KEYDOWN  :
                if ((event.key.keysym.sym ) == SDLK_ESCAPE) {

                    isRunning = false ; 
                }
                break; 
            
            case SDL_MOUSEMOTION :
                mouseeventMutex.lock() ; 
                mouseevent = event.motion  ;  
                mouseeventMutex.unlock() ;
                break ; 
                
            case SDL_MOUSEWHEEL :
                mouseeventMutex.lock() ; 
                wheelEvent = event.wheel ; 
                mouseeventMutex.unlock() ;
                break ; 
            
            default :
                break;  
        }
   } 

}

void Game :: update () {
} 
// ---------------------------- render and destroying ----------------------------

void Game :: render () //where function is of the type function object 
{
    SDL_RenderPresent(renderer ) ; 
} 

void Game :: destroy () {
    SDL_DestroyWindow (window ) ; 
    SDL_DestroyRenderer (renderer ) ; 
   
}
 Game :: Game () {
    isRunning = true ; 
    initialize() ; 
 } 

 Game :: ~ Game () {
    destroy () ; 
 }  
 void Game :: renderText (TTF_Font * ourFont ) {
    
    if (TTF_Init() == -1 ) {std::cout << "problem rendering text "<<std::endl ; }
    SDL_Surface * surfaceText = TTF_RenderText_Solid (ourFont , "mike shah randwa" , {255 ,255,255})  ; 
    SDL_Texture * textTexture = SDL_CreateTextureFromSurface(renderer , surfaceText) ; 
    SDL_FreeSurface (surfaceText) ; 
    SDL_Rect rectangle ; 
    rectangle.x = 10 ; 
    rectangle.y = 10 ; 
    rectangle.w = 100 ; 
    rectangle.h = 100 ; 
    SDL_RenderCopy(renderer , textTexture ,NULL ,  &rectangle ) ; 
    SDL_DestroyTexture (textTexture ) ; 
    TTF_CloseFont ( ourFont ) ; 

 }
void Game::getTerminalText()
{
    std::chrono::milliseconds hunderedMilliSeconds(100);
    while (isRunning == true) {
        std::string input;
        std::getline(std::cin, input);
        {
            std::unique_lock<std::mutex> lock(terminalTextMutex);
            terminalText = input;
        }
        std::this_thread::sleep_for(hunderedMilliSeconds);
        std::cout<<terminalText<< std::endl ; 
    }
}

void processTerminalText(std::vector<nothingClass *> &hector, Game &game) {
    std::string input;
    input = game.terminalText ; 
    SDL_MouseMotionEvent &mouseEvent = game.mouseevent ; 
    std::regex rotate_pattern(R"(rotate\s+(\d+))");
    std::regex translate_pattern(R"(translate\s+(\d+))");
    std::regex process_input_pattern("processInput");
    std::regex end_pattern("end");

    std::smatch match;
    glm::vec3 orientationVector = glm::vec3(0.0f, 0.0f, 0.0f);

    {
        if (!input.empty()) {
            if (mouseEvent.state & SDL_BUTTON_LMASK) {
                orientationVector.x += mouseEvent.xrel;
                orientationVector.y += mouseEvent.yrel;
                orientationVector.z = 0.1;
                orientationVector.x = glm::radians(orientationVector.x) / 4000;
                orientationVector.y = glm::radians(orientationVector.y) / 4000;

                if (std::regex_search(input, match, rotate_pattern)) {
                    int index = std::stoi(match[1].str());
                    if (index >= 0 && index < hector.size()) {
                        hector[index]->rotate(orientationVector);
                    } 
                    else 
                    {
                        std::cout << "No such command found." << std::endl;
                    }
                } else if (std::regex_search(input, match, translate_pattern)) {
                    int index = std::stoi(match[1].str());
                    if (index >= 0 && index < hector.size()) {
                        orientationVector.x += mouseEvent.xrel;
                        orientationVector.y += mouseEvent.yrel;
                        hector[index]->translate(orientationVector);
                    } else {
                        std::cout << "No such command found." << std::endl;
                    }
                } else if (std::regex_search(input, match, process_input_pattern)) {
                    for (nothingClass *obj : hector) {
                        obj->processInput(mouseEvent);
                    }
                } else if (std::regex_search(input, match, end_pattern)) {
                    game.isRunning = false;
                } else {
                    std::cout << "No such command found." << std::endl;
                }
            }
        }
    }
}
