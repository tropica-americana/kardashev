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
    std::unordered_map<std::string , std::string  > stringMap ;
    std::unordered_map<std::string , float  > floatMap ;
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
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
                if ((event.key.keysym.sym ) == SDLK_w) {
                    stringMap["w"] = "being pressed" ;  
                }
                if ((event.key.keysym.sym ) == SDLK_t) {
                    stringMap["t"] = "being pressed" ;  
                }
                if ((event.key.keysym.sym ) == SDLK_r) {
                    stringMap["r"] = "being pressed" ;  
                }
                if ((event.key.keysym.sym ) == SDLK_a) {
                    stringMap["a"] = "being pressed" ;  
                }
                
                if ((event.key.keysym.sym ) == SDLK_f) {
                    stringMap["f"] = "being pressed" ;
                }
              
                if ((event.key.keysym.sym ) == SDLK_3) {
                    stringMap["3"] == "being pressed" ; 
                }
               
                if ((event.key.keysym.sym ) == SDLK_1) {
                    stringMap["1"] == "being pressed" ; 
                }
              
                if ((event.key.keysym.sym ) == SDLK_2) {
                    stringMap["2"] == "being pressed" ; 
                }
                 
                if ((event.key.keysym.sym ) == SDLK_UP) {
                    stringMap["up"] = "being pressed" ; 
                }
                
                if ((event.key.keysym.sym ) == SDLK_DOWN) {
                    stringMap["down"] = "being pressed" ; 
                }
                // s key 
                if ((event.key.keysym.sym ) == SDLK_s) {
                    stringMap["s"] = "being pressed" ; 
                }
                // command key or control in windows 
                if ((event.key.keysym.sym ) == SDLK_LGUI || (event.key.keysym.sym ) == SDLK_LCTRL) {
                    stringMap["command"] = "being pressed" ; 
                }
                // z eky 
                if ((event.key.keysym.sym ) == SDLK_z) {
                    stringMap["z"] = "being pressed" ; 
                }
                break; 
            case SDL_KEYUP :
                if ((event.key.keysym.sym ) == SDLK_w) {
                   stringMap["w"] = "was pressed"  ; 

                }
                if ((event.key.keysym.sym ) == SDLK_t) {
                    stringMap["t"] = "was pressed" ; 
                }
                if ((event.key.keysym.sym ) == SDLK_r) {
                    stringMap["r"] = "was pressed" ;
                }
                if ((event.key.keysym.sym ) == SDLK_a) {
                    stringMap["a"] = "was pressed" ;  
                }
                if ((event.key.keysym.sym ) == SDLK_f) {
                    stringMap["f"] = "was pressed" ;
                }
                if ((event.key.keysym.sym ) == SDLK_3) {
                    stringMap["3"] == "was pressed" ; 
                }
                if ((event.key.keysym.sym ) == SDLK_1) {
                    stringMap["1"] == "was pressed" ; 
                }
                if ((event.key.keysym.sym ) == SDLK_2) {
                    stringMap["2"] == "was pressed" ; 
                }
                if ((event.key.keysym.sym ) == SDLK_UP) {
                    stringMap["up"] = "was pressed" ; 
                }
                if ((event.key.keysym.sym ) == SDLK_DOWN) {
                    stringMap["down"] = "was pressed" ; 
                }
                if ((event.key.keysym.sym ) == SDLK_s) {
                    stringMap["s"] = "was pressed" ; 
                }
                if ((event.key.keysym.sym ) == SDLK_LGUI || (event.key.keysym.sym ) == SDLK_LCTRL) {
                    stringMap["command"] = "was pressed" ; 
                }
                if ((event.key.keysym.sym ) == SDLK_z ) {
                    stringMap["z"] = "was pressed" ; 
                }
                break ;
            case SDL_MOUSEMOTION :
                {SDL_MouseMotionEvent mouseEvent = event.motion ; 
                floatMap["xrel"] += mouseEvent.xrel ;
                floatMap["yrel"] += mouseEvent.yrel ;
                floatMap["x"] = mouseEvent.x ;
                floatMap["y"] = mouseEvent.y ; 
                if (mouseEvent.state & SDL_BUTTON_LMASK) {
                    stringMap["left mouse button"] = "being pressed" ; 
                }}
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
        if ( item->currentMode == "translate") {
            item->translate( floatMap["xrel"]*simultaneousMotionFactor , 
            floatMap["yrel"] * simultaneousMotionFactor , floatMap["zrel"] * simultaneousMotionFactor) ; 
        } 
        if ( item->currentMode == "modify" ){
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
                std::cout << "undo recorded" << std::endl ; 
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

void processTerminalText(std::vector<myNothingClass *> &hector, Game &game) {
    std::string input;
    input = game.terminalText ; 
    SDL_MouseMotionEvent &mouseEvent = game.mouseevent ; 
    SDL_KeyboardEvent &keyboardEvent = game.keyboardEvent ;
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
                        hector[index]->rotate(orientationVector.x , orientationVector.y , orientationVector.z);
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
                        hector[index]->translate(orientationVector.x , orientationVector.y , orientationVector.z);
                    } else {
                        std::cout << "No such command found." << std::endl;
                    }
                } else if (std::regex_search(input, match, process_input_pattern)) {
                    for (myNothingClass * obj : hector) {
                        obj->processInput(mouseEvent , keyboardEvent);
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