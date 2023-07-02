#include "./img.h"

void Img::loadImg (std::string path) {
    SDL_Surface * image = IMG_Load(path.c_str());
    if (image == NULL) {
        std::cout << "Error loading image" <<IMG_GetError()<< std::endl;
    }
    else {
        texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_FreeSurface(image);
    }
}

void Img::renderImg () {

    SDL_RenderClear(renderer );
    SDL_RenderCopy(renderer, texture, NULL, NULL);

}
Img :: Img ( SDL_Renderer * renderer , std::string path) {
    this->renderer = renderer ;
    loadImg(path) ;
}
Img :: ~ Img () {
    if (texture != NULL)
    SDL_DestroyTexture(texture) ;
}
void imageSystem (std::string path){
    Game game ; 
    Time timeObject ; 
    Img img (game.renderer , path) ;
    while (game.isRunning) {
        game.processInput();
        game.update(timeObject.calculateTimeElapsedAndUpdateTime());
        img.renderImg() ;
        SDL_RenderPresent(game.renderer);
        SDL_Delay(10);
    }
}