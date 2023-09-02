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

Img:: Img ( SDL_Renderer * rendererer ) : renderer (rendererer) {
    createImageModel() ;
    this -> texture = nullptr ; 
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
Img :: Img ( SDL_Texture * textureInput , SDL_Renderer * rendererInput ) {
    this-> texture = textureInput ; 
    this -> renderer = rendererInput ; 

}
Img :: Img ( ) {
    this -> renderer = nullptr ; 
    this -> texture = nullptr ; 

} 

void Img :: convertTotext( std::string text , std::string pathToTtf = "/Users/sachinjain/Desktop/gamemachine/assets/fonts/arial.ttf" ) {
    Text textObj ; 
    if ( texture != nullptr )
    SDL_DestroyTexture( texture ) ; 
    this-> texture = textObj.createTextureOfText( text , this-> renderer , pathToTtf ) ; 
}

// this is among the most useful functions for text generation ; 
SDL_Texture * Text::createTextureOfText ( std::string texttobedisplayed , SDL_Renderer * renderer  , std::string pathToTtf) 
{  
    TTF_Font * font = TTF_OpenFont( pathToTtf.c_str() , 100) ; 
    if (TTF_Init() != 0)
    {
        std::cout << "SDL_ttf could not initialize: " << TTF_GetError() << std::endl;
        return nullptr;
    }
    std::cout << SDL_GetError( ) << std::endl ; 
    if ( font == NULL) 
    std::cout << "the font waas not found " << std::endl ; 
    SDL_Color color;
    color = {255, 255, 255};
    SDL_Surface * surface =  TTF_RenderText_Blended(font, texttobedisplayed.c_str(), color );
    TTF_CloseFont(font) ;
    SDL_Texture * texture = SDL_CreateTextureFromSurface( renderer , surface ) ;
    SDL_FreeSurface( surface ) ;  
    return texture  ;  
}
// here is shown how to render text 
void imageSystem (std::string path , std::string pathToTtf ){
    Game game ; 
    Time timeObject ; 
    Img img (game.renderer ) ;
    img.convertTotext("this is the text" , pathToTtf ) ; 
    game.models.push_back(&img.imageModel) ;
    while (game.isRunning) {
        game.processInput();
        game.update(timeObject.calculateTimeElapsedAndUpdateTime());
        img.renderImg() ;
        SDL_RenderPresent(game.renderer);
        SDL_Delay(10);
    }
}

// here is shwon how to render text 
void textsystem ( std::string text ) {
    Game game ; 
    Time timeObject ; 
    Img img (game.renderer ) ;
    img.convertTotext("this is the text" ) ; 
    game.models.push_back(&img.imageModel) ;
    while (game.isRunning) {
        game.processInput();
        game.update(timeObject.calculateTimeElapsedAndUpdateTime());
        img.renderImg() ;
        SDL_RenderPresent(game.renderer);
        SDL_Delay(1);
    }

} 