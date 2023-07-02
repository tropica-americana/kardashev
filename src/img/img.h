#ifndef _IMG_H_
#define _IMG_H_

#include "../myModel/myModel.h"
#include "../game/game.h"
#include "../Time/Time.h"
class Img {
    public :
    myModel imageModel ; 
    SDL_Renderer * renderer ;
    SDL_Texture * texture ;
    Img ( SDL_Renderer * renderer , std::string path) ; 
    ~Img () ;
    void loadImg (std::string path) ;
    void renderImg () ;
    void processInput ( Game & game ) ; 
    void createImageModel () ;
    SDL_Rect  createRectFromModel () ;
};

#endif 