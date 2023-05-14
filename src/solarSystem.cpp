#include "./myModel/myModel.h"
#include "./myVertex/myVertex.h"
#include "./game/game.h"
#include <iostream>
#include <cmath>
#include <numbers>
#include "./physics/physics.cpp"
#include <random>
float MASS_OF_SUN = 10000;
float MASS_OF_EARTH = 100;
float earthVelocityConstatnt = 0;
float EARTH_HORIZONTAL_VELOCITY = earthVelocityConstatnt;
float EARTH_VERTICAL_VELOCITY = -earthVelocityConstatnt;
float EARTH_VELOCITY_Z_AXIS = earthVelocityConstatnt; 
float SUN_HORIZONTAL_VELOCITY = 0;
float SUN_VERTICAL_VELOCITY = 0;
float SCREEN_RESOLUTION = 2000;
float HORIZONTAL_SCREEN_RESOLUTION = 2000;
float VERTICAL_SCREEN_RESOLUTION = 1300 ; 
float EXPANSIONCOEFFICIENT = 1.3 ; 
myModel createSphere()  ; 
class Random {
    public : 
        float getRandomFloatInRange(float minFloat , float maxFloat) {
        static std::default_random_engine e;
        static std::uniform_real_distribution<> dis(minFloat , maxFloat ); // range [0, 1)
        return dis(e);
    }
};
class Planets {
    public : 
    myModel createEarth () {
        myModel earth ;
        earth = createSphere ( ) ; 
        earth.modelName = "earth" ;
        earth.mass = MASS_OF_EARTH ;

        //scaling the earth in proportion to cube root of mass of earth 
        float scalingFactor = std::cbrt(earth.mass) ;
        earth.scale( scalingFactor) ;  
        earth.velocity = {EARTH_HORIZONTAL_VELOCITY, EARTH_VERTICAL_VELOCITY , EARTH_VELOCITY_Z_AXIS} ;
        earth.moveTo (1000, 1000, 0 ) ; 
        earth.angularVelocity = {0.0 , 0.01 , 0.0 } ; 
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
        sun.velocity = {SUN_HORIZONTAL_VELOCITY, SUN_VERTICAL_VELOCITY , 0} ;
        sun.moveTo ( 500, 500 , 0 ) ;  
        sun.angularVelocity = {0.0 , 0.01 , 0.0 } ;     
        return sun ;
    }
    myModel createRandomEarth () {
        myModel earth ;
        Random randomObject ;
        earth = createSphere ( ) ; 
        earth.modelName = "earth" ;
        earth.mass = MASS_OF_EARTH ;

        //scaling the earth in proportion to cube root of mass of earth 
        float scalingFactor = std::cbrt(earth.mass) ;
        earth.scale( scalingFactor) ;  
        earth.velocity = {randomObject.getRandomFloatInRange(-1 , 1 ), randomObject.getRandomFloatInRange(-0.5 , 0.5  ) , randomObject.getRandomFloatInRange(-0.5 , 0.5  )} ;
        earth.moveTo ( randomObject.getRandomFloatInRange(-1500 , 1500 ), randomObject.getRandomFloatInRange(-1500 , 1500 ),randomObject.getRandomFloatInRange(-1500 , 1500 )) ; 
        earth.angularVelocity = {randomObject.getRandomFloatInRange(-0.02 , 0.02 ) , randomObject.getRandomFloatInRange(-0.02 , 0.02 ) , randomObject.getRandomFloatInRange(-0.02 , 0.02 ) } ; 
        return earth ;
    }
} ; 

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
    void translateAllModelsAccordingToMouseInput ( std::vector <myModel *> & models , SDL_MouseMotionEvent & mouseevent , SDL_KeyboardEvent & keyboardevent ) {
        {
            
            for ( int i = 0 ; i < models.size() ; i++ ) {
                models[i]->processInput( mouseevent , keyboardevent) ; 
             }
        }
    }
};

void createSolarSystem (std::vector<myModel *> & models) {
    Planets planet ; 
    myModel * sun = new myModel(planet.createSun()) ;
    models.push_back(sun) ;
    // for (int i = 0 ; i < 2  ; i++ ){
    //     myModel * earth = new myModel(planet.createEarth()) ;
    //     models.push_back(earth) ; 
    //     earth = nullptr ;
    //     }
    myModel * /**/ earth ; 
    earth = new myModel(planet.createRandomEarth()) ;
    models.push_back(earth) ;
    earth = new myModel(planet.createRandomEarth()) ;
    models.push_back(earth) ;
    earth = new myModel(planet.createRandomEarth()) ;
    models.push_back(earth) ;
    earth = new myModel(planet.createRandomEarth()) ;
    models.push_back(earth) ;
    earth = new myModel(planet.createRandomEarth()) ;
    models.push_back(earth) ;
    earth = new myModel(planet.createRandomEarth()) ;
    models.push_back(earth) ;
    earth = new myModel(planet.createRandomEarth()) ;
    models.push_back(earth) ;
    earth = new myModel(planet.createRandomEarth()) ;
    models.push_back(earth) ;
    earth = new myModel(planet.createRandomEarth()) ;
    models.push_back(earth) ;
    earth = new myModel(planet.createRandomEarth()) ;
    models.push_back(earth) ;
    earth = new myModel(planet.createRandomEarth()) ;
    models.push_back(earth) ;
    earth = new myModel(planet.createRandomEarth()) ;
    models.push_back(earth) ;
    earth = new myModel(planet.createRandomEarth()) ;
    models.push_back(earth) ;
    earth = new myModel(planet.createRandomEarth()) ;
    models.push_back(earth) ;
    earth = new myModel(planet.createRandomEarth()) ;
    models.push_back(earth) ;
    earth = new myModel(planet.createRandomEarth()) ;
    models.push_back(earth) ;
    earth = new myModel(planet.createRandomEarth()) ;
    models.push_back(earth) ;
    earth = new myModel(planet.createRandomEarth()) ;
    models.push_back(earth) ;
    earth = new myModel(planet.createRandomEarth()) ;
    models.push_back(earth) ;
    earth = new myModel(planet.createRandomEarth()) ;
    models.push_back(earth) ;
}

class solarSystem {
    public:
    Game game ; 
    solarSystem () {
        Game game ;
    }
    
    void calculateAccelerationDueToGravitaionalPullAndAlsoMoveTheModelsInAllTheModelsInVectorOfPointerToModels (size_t  time_in_milliseconds ) {
        Physics physicsFunctions  ;
        for ( int i = 0 ; i < game.models.size() ; i++ ) {
            for (int j = 0 ; j < game.models.size() ; j++ ) {
                if ( j != i ) {
                    std::tuple <float , float , float > force = physicsFunctions .calculateGravitationalForce ( *(game.models[i]) , *(game.models[j]) ) ;
                    physicsFunctions.addAccelarationToTheModelAccordingToCurrentForce ( *(game.models[i]) , force ) ; 
                    // std::cout << "force applied on model  " << game.models[i]->modelName << "  is " << std::get<0>(force) << " " << std::get<1>(force) << " " << std::get<2>(force) << std::endl ;
                }
            }
        }

        }
    
 } ; 

float Universe :: zoomAmount = 0.01 ;

void renderSolarSystem () {
    
    Universe universe ;
    solarSystem solarSystem ;
    createSolarSystem(solarSystem.game.models) ;
    std::cout << "number of models in the solar system is " << solarSystem.game.models.size() << std::endl ;
    while (solarSystem.game.isRunning) {
        
        solarSystem.game.processInput() ;
        // solarSystem.calculateAccelerationDueToGravitaionalPullAndAlsoMoveTheModelsInAllTheModelsInVectorOfPointerToModels( 20 ) ;
        solarSystem.game.update( 20 ) ;
        universe.translateAllModelsAccordingToMouseInput ( solarSystem.game.models ,solarSystem.game.mouseevent , solarSystem.game.keyboardEvent) ;
        universe.zoomOutAndRenderTheObjectInTheUniverse ( solarSystem.game.models , solarSystem.game.renderer ) ;
        // SDL_Delay(20) ;
    }
}


