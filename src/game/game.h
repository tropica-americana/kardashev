#ifndef _GAME_H_
#define _GAME_H_


#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector> 
#include <map>
#include <string> 
#include <mutex>
class Game {
    public: 
    bool isRunning ; 
    SDL_MouseMotionEvent mouseevent ; 
    SDL_MouseWheelEvent wheelEvent ;    
    SDL_Window * window ; 
    SDL_Renderer * renderer ; 
    std::mutex inputUploadMutex ; 
    Game () ;  // calls the initialize method 
    ~Game () ; // calls the void destory () method 
    void initialize() ;  // creates a window and renderer 
    void processInput () ;  // records the input and stores them into a ceratin data type 
    void update () ;  // updates the postion and presence of objects based on the input    
    void render () ;  // just paste everything on thhe renderrer 
    void destroy () ; // destroys the window and the renderer 
    void renderText (TTF_Font * ourFont ) ; 
} ; 
///
#endif // !_GAME_H_
