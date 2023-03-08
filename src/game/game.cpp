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
    std::cout<<"probleme renderere "<<std::endl;
    SDL_SetWindowFullscreen(window  , SDL_WINDOW_FULLSCREEN) ; 
    return ; }
}

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
                mouseevent = event.motion  ;  
                // print<std::string> ("mouse motion event ") ; 
                break ; 
                
            case SDL_MOUSEWHEEL :
                wheelEvent = event.wheel ; 
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