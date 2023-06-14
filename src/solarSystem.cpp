#include "./myModel/myModel.h"
#include "./myVertex/myVertex.h"
#include "./game/game.h"
#include <iostream>
#include <cmath>
#include <numbers>
#include "./physics/physics.h"
#include "./Time/Time.h"
#include "./Random/random.h"
#include "./cli/cli.h"
#include <random>
using std::cout ;
using std::endl ;
float MASS_OF_SUN = 100;
float MASS_OF_EARTH = 1;
size_t TIME_SPENT_IN_EACH_FRAME = 2; // this is in milliseconds 
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
float TIMEEXPANSIONCOEFFICIENT = 1.0 ; 
float ALLOWANCEEXPANSIONCOEFFICIENT = 1.0 ;

class Planets {
    public : 
    myModel createSphere() {
        myModel sphere;
        myVertex mainVertex{ 0.0f , 100.0f  , 0.0f };
        sphere.addVertex(mainVertex);
        float pi = std::numbers::pi_v< float>;
        float currentAngle = 0.0f;
        int numberOfVerticesPerPlane = 10;
        float incrementAngle = 2 * pi / static_cast<int> (numberOfVerticesPerPlane);
        for (int i = 0; i < 10; i++) {
            mainVertex.rotateMyVertexAlongAxis(incrementAngle, Axis::x);
            for (int i = 0; i < 10; i++) {
                mainVertex.rotateMyVertexAlongAxis(incrementAngle, Axis::z);
                sphere.addVertex(mainVertex);
            }
        }
        sphere.createMesh();
        return sphere;
    }
    myModel createEarth () {
        myModel earth ;
        earth = createSphere ( ) ; 
        earth.modelName = "earth" ;
        earth.mass = MASS_OF_EARTH ;
        earth.stringMap["input"] = "true" ;
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
        sun.stringMap["input"] = "true" ;
        //scaling the sun in proportion to cube root of mass of sun 
        float scalingFactor = std::cbrt(sun.mass) ;
        sun.scale( scalingFactor) ; 
        sun.velocity = {SUN_HORIZONTAL_VELOCITY, SUN_VERTICAL_VELOCITY , 0} ;
        sun.moveTo ( 0, 0 , 0 ) ;  
        sun.angularVelocity = {0.0 , 0.01 , 0.0 } ;     
        return sun ;
            }
    myModel createRandomEarth () {
        // the random error is not solved and is the cause of many problems . 
        
        myModel earth ;
        Random randomObject ;
        earth = createSphere ( ) ; 
        earth.modelName = "earth" ;
        
        earth.mass = MASS_OF_EARTH ;

        //scaling the earth in proportion to cube root of mass of earth 
        float scalingFactor = std::cbrt(earth.mass) ;
        earth.scale( scalingFactor) ;  
        earth.velocity = {randomObject.getRandomFloatInRangeIncludingNegativeValues( 0.5 , 2 ), randomObject.getRandomFloatInRangeIncludingNegativeValues(0.5 , 2  ) , randomObject.getRandomFloatInRangeIncludingNegativeValues(0.5 , 2  )} ;
        earth.moveTo ( randomObject.getRandomFloatInRangeIncludingNegativeValues(3000 , 7000 ), randomObject.getRandomFloatInRangeIncludingNegativeValues(3000 , 7000 ),randomObject.getRandomFloatInRangeIncludingNegativeValues(3000 , 7000 )) ; 
        earth.angularVelocity = {randomObject.getRandomFloatInRangeIncludingNegativeValues(-0.02 , 0.02 ) , randomObject.getRandomFloatInRangeIncludingNegativeValues(-0.02 , 0.02 ) , randomObject.getRandomFloatInRangeIncludingNegativeValues(-0.02 , 0.02 ) } ; 

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
    }
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
    sun = nullptr ;
    myModel * /**/ earth ; 
    for (int i = 0 ; i < 10; i++ ){
        earth = new myModel(planet.createRandomEarth()) ;
        models.push_back(earth) ;
        earth = nullptr ;
        }
}
void CliThreadFunction (std::vector <myModel *> & models  , bool & isRunning , std::mutex & modelsMutex) {
    while ( isRunning)
    {   
        
        CLI cliObject  ;
        cliObject.getTerminalText ( ) ;
        modelsMutex.lock() ;
        cliObject.processCommand( models ) ; 
        modelsMutex.unlock() ;
        SDL_Delay(100) ; 
    }
} 

class solarSystem {
    public:
    Game game ; 
    solarSystem () {
        Game game ;
    }
    
    inline void calculateAccelerationDueToGravitaionalPullAndAlsoMoveTheModelsInAllTheModelsInVectorOfPointerToModels ( std::mutex & modelsMutex ) {
        Physics physicsFunctions  ;
        while (game.isRunning){       
        Time timeObject ; 
        modelsMutex.lock() ;
        for ( int i = 0 ; i < game.models.size() ; i++ ) {
            
            game.models[i]->zeroTheAcceleration() ; 
            for (int j = 0 ; j < game.models.size() ; j++ ) {
                if ( j != i ) {
                    if ( std::find(game.models[i]->vectorOfModelsCollidedWithThisModel.begin(),game.models[i]->vectorOfModelsCollidedWithThisModel.end() , (game.models[j])) == game.models[i]->vectorOfModelsCollidedWithThisModel.end() )
                    {}
                    else {
                        std::tuple <float , float , float > force = physicsFunctions.calculateGravitationalForce ( *(game.models[i]) , *(game.models[j]) , std::ref (ALLOWANCEEXPANSIONCOEFFICIENT) ) ;
                        
                        physicsFunctions.addAccelarationToTheModelAccordingToCurrentForce ( *(game.models[i]) , force  ) ; 
                        // displaying the accleeration of the model 
                        float x = std::get<0>(game.models[i]->acceleration) ;
                        float y = std::get<1>(game.models[i]->acceleration) ;
                        float z = std::get<2>(game.models[i]->acceleration) ;
                        // std::cout << "acceleration of " << game.models[i]->modelName << " is " << x << " " << y << " " << z << std::endl ;
                        
                    }
                }
            }
        }
        modelsMutex.unlock() ;
        SDL_Delay(1) ;
        }
        }
    
} ;
void collisionThread ( std::vector <myModel *> & models , bool & isRunning  ) {
        Physics physicsFunctions ;
        while  ( isRunning )
        {
            physicsFunctions.checkForCollisionsInVectorOfPointersToModels ( models , 1.0f   )   ;
            SDL_Delay(3) ;
        }
}
float Universe :: zoomAmount = 0.01;
void renderSolarSystem () {
    std::mutex modelsMutex;
    Universe universe;
    solarSystem solarsystem;
    Time timeObject ;
    Physics physicsFunctions ; 
    size_t time = SDL_GetTicks64() ;  
    size_t relativeTime ; 
    createSolarSystem(solarsystem.game.models);
    std::thread calcThread(&solarSystem::calculateAccelerationDueToGravitaionalPullAndAlsoMoveTheModelsInAllTheModelsInVectorOfPointerToModels, &solarsystem, std::ref(modelsMutex) );
    calcThread.detach();
    std::thread cliThread(CliThreadFunction, std::ref(solarsystem.game.models),  std::ref(solarsystem.game.isRunning) , std::ref(modelsMutex)); 
    cliThread.detach();
    std::thread collisionthread ( collisionThread , std::ref(solarsystem.game.models) , std::ref(solarsystem.game.isRunning) ) ;
    collisionthread.detach() ;
    while (solarsystem.game.isRunning) {  
        
        time = timeObject.calculateTimeElapsedAndUpdateTime() ;
        relativeTime = static_cast <size_t> ( time * TIMEEXPANSIONCOEFFICIENT ) ;   
        modelsMutex.lock () ; 
        solarsystem.game.processInput();
        solarsystem.game.update(relativeTime);   

        universe.zoomOutAndRenderTheObjectInTheUniverse(solarsystem.game.models, solarsystem.game.renderer);
        modelsMutex.unlock() ;
        SDL_Delay(TIME_SPENT_IN_EACH_FRAME );
    }
}
 