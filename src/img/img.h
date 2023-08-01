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
    Img ( ) = default ; 
    Img ( SDL_Renderer * renderer , std::string path) ; 
    Img ( SDL_Texture * textureInput , SDL_Renderer * renderer  ) ; 
    ~Img () ;
    void loadImg (std::string path) ;
    void renderImg () ;
    void processInput ( Game & game ) ; 
    void createImageModel () ;
    void convertTotext (std::string text , std::string pathToTtf ) ; 
    SDL_Rect  createRectFromModel () ;

};
class Text  {
    public: 
    SDL_Texture * createTextureOfText ( std::string texttobedisplayed , SDL_Renderer * renderer , std::string pathToTtf ) ; 
    
} ; 

#endif 