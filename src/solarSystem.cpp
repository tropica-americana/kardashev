#include "./myModel/myModel.h"
#include "./myVertex/myVertex.h"
#include "./game/game.h"
#include <iostream>
#include <cmath>
#include <numbers>
float MASS_OF_SUN = 100;
float MASS_OF_EARTH = 1;
float GRAVITATIONAL_CONSTANT = 600;
float EARTH_HORIZONTAL_VELOCITY = 10;
float SUN_VERTICAL_VELOCITY = 10;
float SCREEN_RESOLUTION = 2000;
float HORIZONTAL_SCREEN_RESOLUTION = 2000;
float VERTICAL_SCREEN_RESOLUTION = 1300 ; 
float EXPANSIONCOEFFICIENT = 1.3 ; 
myModel createSphere()  ; 

class Universe 
{
    public: 
    static float zoomAmount ; 
    Universe () = default ; 
    ~Universe () = default ;    
    void zoomOutAndRenderTheObjectInTheUniverse  ( std::vector <myModel *> & models , SDL_Renderer * renderer ) {
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);
        for ( int i = 0 ; i < models.size() ; i++ ) {
            models[i]->renderMyselfAccordingToZoomLevelAndScreePixelResolution( renderer , zoomAmount , HORIZONTAL_SCREEN_RESOLUTION , VERTICAL_SCREEN_RESOLUTION ) ;
        }
        SDL_RenderPresent(renderer ) ; 
    };
};

class Physics {

};

myModel createEarth () {
    myModel earth ;
    earth = createSphere ( ) ; 
    earth.modelName = "earth" ;
    earth.mass = MASS_OF_EARTH ;

    //scaling the earth in proportion to cube root of mass of earth 
    float scalingFactor = std::cbrt(earth.mass) ;
    earth.scale( scalingFactor) ;  
    earth.velocity = {EARTH_HORIZONTAL_VELOCITY  , 0, 0} ;
    earth.moveTo (500, 500, 0 ) ; 
    return earth ;
}
myModel createSun () {
    myModel sun ;
    sun = createSphere ( ) ;
    sun.modelName = "sun" ;
    sun.mass = MASS_OF_SUN ;
    
    //scaling the sun in proportion to cube root of mass of sun 
    float scalingFactor = std::cbrt(sun.mass) ;
    sun.scale( scalingFactor) ; 
    sun.velocity = {0, SUN_VERTICAL_VELOCITY , 0} ;
    sun.moveTo ( 200, 200 , 0 ) ;      
    return sun ;
}

void createSolarSystem (std::vector<myModel *> & models) {
    myModel * earth = new myModel(createEarth()) ;
    models.push_back(earth) ;

    myModel * sun = new myModel(createSun()) ;
    models.push_back(sun) ;
}


float calculateDistanceBetweenTwoModels ( myModel & model1 , myModel & model2 ) {
    float x1 , y1 , z1 , x2 , y2 , z2 ;
    std::tie(x1 , y1 , z1) = model1.getPosition() ;
    std::tie(x2 , y2 , z2) = model2.getPosition() ;
    float distance = std::sqrt( std::pow(x1 - x2 , 2) + std::pow(y1 - y2 , 2) + std::pow(z1 - z2 , 2) ) ;
    return distance ; 
}

std::tuple<float , float , float  > calculateGravitationalForce ( myModel & model1 , myModel & model2) {
    float distance = calculateDistanceBetweenTwoModels ( model1 , model2 ) ;
    float xDistance = std::get<0>(model1.getPosition()) - std::get<0>(model2.getPosition()) ;
    float yDistance = std::get<1>(model1.getPosition()) - std::get<1>(model2.getPosition()) ;
    float zDistance = std::get<2>(model1.getPosition()) - std::get<2>(model2.getPosition()) ;
    float force = ( GRAVITATIONAL_CONSTANT * model1.mass * model2.mass ) / std::pow(distance , 2) ;
    float xForce = ( force * xDistance ) / distance ;
    float yForce = ( force * yDistance ) / distance ;
    float zForce = ( force * zDistance ) / distance ;
    return { xForce , yForce , zForce } ;
    
}

void  accelerateModelAccordingToForce  ( myModel & model , std::tuple<float , float , float > force ) {
    float xAcceleration = std::get<0>(force) / model.mass ;
    float yAcceleration = std::get<1>(force) / model.mass ;
    float zAcceleration = std::get<2>(force) / model.mass ;
    model.acceleration = { xAcceleration , yAcceleration , zAcceleration } ;
}
 
class solarSystem {
    public:
    Game game ; 
    solarSystem () {
        Game game ;
    }
    
    void calculateAccelerationDueToGravitaionalPullAndAlsoMoveTheModelsInAllTheModelsInVectorOfPointerToModels (size_t  time_in_milliseconds ) {
        for ( int i = 0 ; i < game.models.size() ; i++ ) {
            for (int j = 0 ; j < game.models.size() ; j++ ) {
                if ( j != i ) {
                    
                    std::tuple <float , float , float > force = calculateGravitationalForce ( *(game.models[i]) , *(game.models[j]) ) ;
                    accelerateModelAccordingToForce ( *(game.models[i]) , force ) ;
                    game.models[i] -> move (time_in_milliseconds  /* time in milliseconds */) ; /*this also updates the velocity according to acceleration */
                }
            }
        }

    }
    
 } ; 
 float Universe :: zoomAmount = 0.1 ;

void renderSolarSystem () {
    
    Universe universe ;
    solarSystem solarSystem ;
    createSolarSystem(solarSystem.game.models) ;
    while (solarSystem.game.isRunning) {
        
        solarSystem.game.processInput() ;
        solarSystem.game.update( 20 ) ;
        solarSystem.calculateAccelerationDueToGravitaionalPullAndAlsoMoveTheModelsInAllTheModelsInVectorOfPointerToModels( 20 ) ;
        universe.zoomOutAndRenderTheObjectInTheUniverse ( solarSystem.game.models , solarSystem.game.renderer ) ;
        SDL_Delay(20) ;
    }
}