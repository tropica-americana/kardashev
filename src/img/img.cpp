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
    SDL_Rect rect = createRectFromModel() ;
    SDL_RenderCopy(renderer, texture, NULL, &rect );
}
Img :: Img ( SDL_Renderer * renderer , std::string path) {
    createImageModel() ;
    this->renderer = renderer ;
    loadImg(path) ;
}
Img :: ~ Img () {
    if (texture != NULL)
    SDL_DestroyTexture(texture) ;
}
void Img :: createImageModel (){
    imageModel.translate( 1000.0 , 1000.0 , 0.0f) ;  
    for (auto & item : imageModel.vertices){
        delete item ;
    }
    imageModel.vertices.clear() ;
    imageModel.addVertex(0.0f , 0.0f , 0.0f) ;
    imageModel.addVertex(100.0f , 0.0f , 0.0f) ;
    imageModel.addVertex(100.0f , 100.0f , 0.0f) ;
    imageModel.addVertex(0.0f , 100.0f , 0.0f) ;
        
}
SDL_Rect  Img :: createRectFromModel (){
    SDL_Rect rect ; 
    rect.x = imageModel.vertices[0]->getOnScreenX() ;
    rect.y = imageModel.vertices[0]->getOnScreenY() ;
    rect.w = imageModel.vertices[2]->x - imageModel.vertices[0]->x ;
    rect.h = imageModel.vertices[2]->y - imageModel.vertices[0]->y ;
    return rect ;
}
void imageSystem (std::string path){
    Game game ; 
    Time timeObject ; 
    Img img (game.renderer , path) ;
    game.models.push_back(&img.imageModel) ;
    while (game.isRunning) {
        game.processInput();
        game.update(timeObject.calculateTimeElapsedAndUpdateTime());
        img.renderImg() ;
        SDL_RenderPresent(game.renderer);
        SDL_Delay(10);
    }
}