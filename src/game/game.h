#ifndef _GAME_H_
#define _GAME_H_


#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector> 
#include <map>
#include <string> 
#include <mutex>
#include <chrono>
#include <thread>
#include "../nothingClass /nothingClass.h"
#include "../myModel/myModel.h"
#include <regex>
#include <unordered_map>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
class Game {
    public: 
    bool isRunning ; 
    std::mutex mouseeventMutex ; 
    SDL_MouseMotionEvent mouseevent ; 
    SDL_MouseWheelEvent wheelEvent ;   
    SDL_KeyboardEvent keyboardEvent ; 
    SDL_Window * window ; 
    SDL_Renderer * renderer ; 
    std::mutex terminalTextMutex ; 
    std::string terminalText ; 
    std::vector <myModel * > models ; 
    Game () ;  // calls the initialize method 
    ~Game () ; // calls the void destory () method 
    void initialize() ;  // creates a window and renderer 
    void processInput () ;  // records the input and stores them into a ceratin data type 
    void update (size_t time_in_milliseconds ) ;  // updates the postion and presence of objects based on the input    
    void render () ;  // just paste everything on thhe renderrer 
    void destroy () ; // destroys the window and the renderer and removes all the models from the heap 
    void renderText (TTF_Font * ourFont ) ; 
    void getTerminalText() ;
} 
; 
///
#endif // !_GAME_H_
