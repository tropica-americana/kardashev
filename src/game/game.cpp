#include <iostream>
#include "game.h"

#include <string>
void Game ::initialize()
{
    models.clear () ; 
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0 )
    {
        std::cerr << "problem initializing everything " << std::endl;
        isRunning = false ; 
        return;
    }
    if ( TTF_Init() != 0 ) {
        std::cerr << "problem initializing sdl_ttf" << std::endl ;  
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

void Game ::processInput( )
{
/*
1. a-z and 1-9 key inputs show continous recording and there fore there key pressed should be recorder uusign 
    the principle of if ( stringmap["1"]== "was pressed") 
2. command keys show discontinous recordings i.e. if (stringmap["1"]== "being pressed") is acceptable 
    because of the fact that after commadn keys is pressed the keydown event is stopeed to record 
    maybe that si the characterstic of modifier keys ; 
*/
    // as the stringmap and the floatMap are used uin the class attributes ; 
    // std::unordered_map<std::string , std::string  > stringMap ;
    // std::unordered_map<std::string , float  > floatMap ;
    /*
     * clearing the unordered maps from the previous imputs which is important ; 
     */ 
    stringMap.clear() ;floatMap.clear () ; 
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
        switch (event.type)
        {
            case SDL_QUIT :  
                isRunning = false ; 
                break ; 
            case SDL_KEYDOWN  :
            // recording the keyup events ; 
                if ((event.key.keysym.sym ) == SDLK_ESCAPE) {
                    isRunning = false ; 
                }
                if ((event.key.keysym.sym) == SDLK_a) {
                    stringMap["a"] = "being pressed" ;
                }
                if ((event.key.keysym.sym) == SDLK_b) {
                    stringMap["b"] = "being pressed" ; 
                    }
                if ((event.key.keysym.sym) == SDLK_c) {
                    stringMap["c"] = "being pressed"  ; 
                } 
                if ((event.key.keysym.sym) == SDLK_d) {
                    stringMap["d"] = "being pressed" ; 
                    }
                if ((event.key.keysym.sym) == SDLK_e){
                    stringMap["f"] = "being pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_f) {
                    stringMap["g"] = "being pressed"  ; 
                }
                if ((event.key.keysym.sym) == SDLK_g){
                    stringMap["h"] = "being pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_h) {
                    stringMap["i"] = "being pressed" ; 
                }

                if ((event.key.keysym.sym) == SDLK_i) {
                    stringMap["j"] = "being pressed"  ; 
                }
                if ((event.key.keysym.sym) == SDLK_j) {
                    stringMap["j"] = "being pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_k) {
                    stringMap["l"] = "being pressed" ;
                }
                if ((event.key.keysym.sym) == SDLK_m) {
                    stringMap["m"] = "being pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_n) {
                    stringMap["n"] = "being pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_o){
                    stringMap["o"] = "being pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_p) {
                    stringMap["p"] = "being pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_q) {
                    stringMap["q"] = "being pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_r) {
                    stringMap["r"] = "being pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_s){
                    stringMap["s"] = "being pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_t) {
                    stringMap["t"] = "being pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_u){
                    stringMap["u"] = "being pressed"  ; 
                }
                if ((event.key.keysym.sym) == SDLK_v) {
                    stringMap["v"] = "being pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_w) {
                    stringMap["w"] = "being pressed"  ; 
                } 
                if ((event.key.keysym.sym) == SDLK_x) {
                    stringMap["x"] = "being pressed" ;
                }
                if ((event.key.keysym.sym ) == SDLK_y){
                    stringMap["y"] = "being pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_z){
                    stringMap["z"] = "being pressed" ; 
                }
                if ((event.key.keysym.sym ) == SDLK_2) {
                    stringMap["2"] == "being pressed" ; 
                }
               
                if ((event.key.keysym.sym ) == SDLK_1) {
                    stringMap["1"] == "being pressed" ; 
                }
                if ((event.key.keysym.sym ) == SDLK_4) 
                    stringMap["4"] = "being pressed" ; 
                    
                if ((event.key.keysym.sym ) == SDLK_3) {
                    stringMap["3"] == "being pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_5) {
                    stringMap["5"] = "being pressed"  ; 
                }
                if ((event.key.keysym.sym) == SDLK_6) {
                    stringMap["6"] = "being pressed" ; 
                } 
                if ((event.key.keysym.sym) == SDLK_7) {
                    stringMap["7"] = "being pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_8) {
                    stringMap["8"] = "being pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_9) {
                    stringMap["9"] = "being pressed" ; 
                }          
                if ((event.key.keysym.sym ) == SDLK_UP) {
                    stringMap["up"] = "being pressed" ; 
                }
                
                if ((event.key.keysym.sym ) == SDLK_DOWN) {
                    stringMap["down"] = "being pressed" ; 
                }
                               
                // command key or control in windows 
                if ((event.key.keysym.sym ) == SDLK_LGUI || (event.key.keysym.sym ) == SDLK_LCTRL) {
                    stringMap["command"] = "being pressed" ; 
                    // std::cout << "Command being pressed: " << std::endl ; 
                }
                
                break;
            // recording the key down events 
            case SDL_KEYUP :
                if ((event.key.keysym.sym ) == SDLK_ESCAPE) {
                    isRunning = false ; 
                }
                if ((event.key.keysym.sym) == SDLK_a) {
                    stringMap["a"] = "was pressed" ;
                }
                if ((event.key.keysym.sym) == SDLK_b) {
                    stringMap["b"] = "was pressed" ; 
                    }
                if ((event.key.keysym.sym) == SDLK_c) {
                    stringMap["c"] = "was pressed"  ; 
                } 
                if ((event.key.keysym.sym) == SDLK_d) {
                    stringMap["d"] = "was pressed" ; 
                    }
                if ((event.key.keysym.sym) == SDLK_e){
                    stringMap["f"] = "was pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_f) {
                    stringMap["g"] = "was pressed"  ; 
                }
                if ((event.key.keysym.sym) == SDLK_g){
                    stringMap["h"] = "was pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_h) {
                    stringMap["i"] = "was pressed" ; 
                }

                if ((event.key.keysym.sym) == SDLK_i) {
                    stringMap["j"] = "was pressed"  ; 
                }
                if ((event.key.keysym.sym) == SDLK_j) {
                    stringMap["j"] = "was pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_k) {
                    stringMap["l"] = "was pressed" ;
                }
                if ((event.key.keysym.sym) == SDLK_m) {
                    stringMap["m"] = "was pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_n) {
                    stringMap["n"] = "was pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_o){
                    stringMap["o"] = "was pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_p) {
                    stringMap["p"] = "was pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_q) {
                    stringMap["q"] = "was pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_r) {
                    stringMap["r"] = "was pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_s){
                    stringMap["s"] = "was pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_t) {
                    stringMap["t"] = "was pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_u){
                    stringMap["u"] = "was pressed"  ; 
                }
                if ((event.key.keysym.sym) == SDLK_v) {
                    stringMap["v"] = "was pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_w) {
                    stringMap["w"] = "was pressed"  ; 
                } 
                if ((event.key.keysym.sym) == SDLK_x) {
                    stringMap["x"] = "was pressed" ;
                }
                if ((event.key.keysym.sym ) == SDLK_y){
                    stringMap["y"] = "was pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_z){
                    stringMap["z"] = "was pressed" ; 
                }
                
                if ((event.key.keysym.sym ) == SDLK_1) {
                    stringMap["1"] == "was pressed" ; 
                }
                if ((event.key.keysym.sym ) == SDLK_4) 
                    stringMap["4"] = "was pressed" ; 
                    
                if ((event.key.keysym.sym ) == SDLK_3) {
                    stringMap["3"] == "was pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_5) {
                    stringMap["5"] = "was pressed"  ; 
                }
                if ((event.key.keysym.sym) == SDLK_6) {
                    stringMap["6"] = "was pressed" ; 
                } 
                if ((event.key.keysym.sym) == SDLK_7) {
                    stringMap["7"] = "was pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_8) {
                    stringMap["8"] = "was pressed" ; 
                }
                if ((event.key.keysym.sym) == SDLK_9) {
                    stringMap["9"] = "was pressed" ; 
                }  
                if ((event.key.keysym.sym ) == SDLK_UP) {
                    stringMap["up"] = "was pressed" ; 
                }
                
                if ((event.key.keysym.sym ) == SDLK_DOWN) {
                    stringMap["down"] = "was pressed" ; 
                }     
                // command key or control in windows 
                if ((event.key.keysym.sym ) == SDLK_LGUI || (event.key.keysym.sym ) == SDLK_LCTRL) {
                    stringMap["command"] = "was pressed" ; 
                    // std::cout << "Command was pressed" << std::endl; ; 
                }
                
                break ;
            case SDL_MOUSEMOTION :
                // recording and storing mouse events in to the string maps and the float maps 
                {
                // recording the mouse floating point values 
                SDL_MouseMotionEvent mouseEvent = event.motion ; 
                floatMap["xrel"] += mouseEvent.xrel ;
                floatMap["yrel"] += mouseEvent.yrel ;
                floatMap["x"] = mouseEvent.x ;
                floatMap["y"] = mouseEvent.y ; 
                // recording the mouse button state ; 
                if (mouseEvent.state & SDL_BUTTON_LMASK) {
                    stringMap["left mouse button"] = "being pressed" ; 
                }
                // leaving somethings for the later improvement  ;

                }
                
                break ; 
            case SDL_MOUSEWHEEL :
                continue;
                break ; 
            
            default :
                break;
            
        }
        
   } 
    float simultaneousMotionFactor = 100.0f ;
    float simultaneousRotationFactor = 0.1f ; 
    for (auto & item : models ) {
         
        if ( item->stringMap["input"] != "false" ){
            if ( stringMap["t"] == "being pressed" && stringMap["left mouse button"] == "being pressed" ) {
                item->translate (floatMap["xrel"]*simultaneousMotionFactor , 
                floatMap["yrel"] * simultaneousMotionFactor , floatMap["zrel"] * simultaneousMotionFactor) ; 
            }
            if (stringMap["r"] == "being pressed" && stringMap["left mouse button"] == "being pressed"){
                item->rotate (floatMap["xrel"]*simultaneousRotationFactor , floatMap["yrel"] * simultaneousRotationFactor , 0.0f ) ;
            }
            if (stringMap["a"] == "being pressed" && stringMap["left mouse button"] == "being pressed"){
                if (stringMap["f"] == "was pressed" || stringMap["f"] == "being pressed") {
                    item->vertexFinalized = true ;
                }
                if (item->vertexFinalized == true) {
                    myVertex newVertex ; 
                    newVertex.xTranslate = item->vertices[0]->xTranslate ; 
                    newVertex.yTranslate = item->vertices[0]->yTranslate ;
                    newVertex.zTranslate = item->vertices[0]->zTranslate ;
                    newVertex.x = floatMap["x"] - newVertex.xTranslate ;
                    newVertex.y = floatMap["y"] - newVertex.yTranslate ;
                    newVertex.z = 0.01f ;
                    item->vertices.push_back( new myVertex{newVertex} ) ;
                    item->vertexFinalized = false ;
                    item->createMesh() ; 
                }
                if ( item->vertexFinalized == false ) {
                    item->vertices[item->vertices.size() - 1]->x += floatMap["x"] * simultaneousMotionFactor ;
                    item->vertices[item->vertices.size() - 1]->y += floatMap["y"] * simultaneousMotionFactor ;    
                }
            }
            if (stringMap["up"] == "being pressed" ){
                item->scale (1.2f) ;
            }
            if (stringMap["down"] == "being pressed" ){
                item->scale (0.8f) ;
            }
            if (stringMap["up"] == "was pressed") {
                item->scale (1.1f) ;
            }
            if (stringMap["down"] == "was pressed") {
                item->scale (0.9f) ;
            }
            if (stringMap["s"] == "was pressed"){
                std::string modelName ; 
                std::cout << "Enter the name of the model you want to save" << std::endl ;
                std::cin >> modelName ;
                if (modelName == "" || modelName == " " || modelName == "\n"){
                    return ; 
                }
                item->saveModel( "data.txt", modelName) ;
                }
            
            if (stringMap["command"] == "being pressed"){
                if (stringMap["z"] == "was pressed"){
                    int verticesSize = item->vertices.size( ) ;
                    delete item->vertices[verticesSize - 1] ;
                    item->vertices.pop_back() ;
                } 
                // std::cout << "undo recorded" << std::endl ; 
                // this is the most poorly written algo 
             } 

        }
    }

}

void Game :: update (size_t time_in_milliseconds ) {

    for (auto & item : models ) {
        item->move(time_in_milliseconds) ; 
        // turning the net accelaration of model to zero so it should be calcualted in the next cycle 
        item -> acceleration = { 0 , 0 , 0 } ; 
    }
} 
// ---------------------------- render and destroying ----------------------------

void Game :: render () //where function is of the type function object 
{
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);
    
    for (auto & item : models ) {
        auto position = item->getPosition() ;
        if (std::get<0>(position) > -10000 && std::get<0>(position) < 10000 && std::get<1>(position) > -10000 && std::get<1>(position) < 10000 && std::get<2>(position) > -10000 && std::get<2>(position) < 10000) 
        item->renderMyself (renderer ) ;
    }    
    SDL_RenderPresent(renderer ) ; 
} 

void Game :: destroy () {
    SDL_DestroyWindow (window ) ; 
    SDL_DestroyRenderer (renderer ) ; 
    for (auto & item : models ) {
        delete item ; 
    }
   
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
