#include "./myModel/myModel.h"
#include "./myVertex/myVertex.h"
#include "./game/game.h"
#include <iostream>
#include <cmath>
#include <numbers>
#include "./physics/physics.cpp"
#include "./Time/Time.cpp"
#include <random>
float MASS_OF_SUN = 1;
float MASS_OF_EARTH = 10;
size_t TIME_SPENT_IN_EACH_FRAME = 10; // this is in milliseconds 
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
float TIMEEXPANSIONCOEFFICIENT = 0.4 ; 

class Random {
public : 
    float getRandomFloatInRange(float minFloat, float maxFloat) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(minFloat, maxFloat);
        float randomValue = dis(gen);
        std::cout << randomValue << std::endl;
        return randomValue;
    }
};

class Planets {
    public : 
    myModel createSphere() {
        myModel sphere;
        sphere.currentMode = "modify";
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
        earth.velocity = {randomObject.getRandomFloatInRange( 0.5 , 2 ), randomObject.getRandomFloatInRange(0.5 , 2  ) , randomObject.getRandomFloatInRange(0.5 , 2  )} ;
        earth.moveTo ( randomObject.getRandomFloatInRange(3000 , 7000 ), randomObject.getRandomFloatInRange(3000 , 7000 ),randomObject.getRandomFloatInRange(3000 , 7000 )) ; 
        earth.angularVelocity = {randomObject.getRandomFloatInRange(-0.02 , 0.02 ) , randomObject.getRandomFloatInRange(-0.02 , 0.02 ) , randomObject.getRandomFloatInRange(-0.02 , 0.02 ) } ; 
        std::cout << "x position of random earth is " << std::get<0> (earth.getPosition() )  <<  std::endl ;
        std::cout << "y position of random earth is " << std::get<1> (earth.getPosition() )  <<  std::endl ;
        std::cout << "z position of random earth is " << std::get<2> (earth.getPosition() )  <<  std::endl ;
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
    for (int i = 0 ; i < 1 ; i++ ){
        earth = new myModel(planet.createRandomEarth()) ;
        models.push_back(earth) ;
        earth = nullptr ;
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
        for ( int i = 0 ; i < game.models.size() ; i++ ) {
            for (int j = 0 ; j < game.models.size() ; j++ ) {
                if ( j != i ) {
                    std::tuple <float , float , float > force = physicsFunctions.calculateGravitationalForce ( *(game.models[i]) , *(game.models[j]) ) ;
                    modelsMutex.lock() ;
                    physicsFunctions.addAccelarationToTheModelAccordingToCurrentForce ( *(game.models[i]) , force  ) ; 
                    modelsMutex.unlock() ;
                }
            
            }
             
        }}

        }
    
} ;


float Universe :: zoomAmount = 0.01 ;
void renderSolarSystem () {
    std::mutex modelsMutex;
    Universe universe;
    solarSystem solarsystem;
    Time timeObject ;
    size_t time = SDL_GetTicks64() ;  
    size_t relativeTime ; 
    createSolarSystem(solarsystem.game.models);

    std::thread calcThread(&solarSystem::calculateAccelerationDueToGravitaionalPullAndAlsoMoveTheModelsInAllTheModelsInVectorOfPointerToModels, &solarsystem, std::ref(modelsMutex));
    // Detach the thread if it should run independently, otherwise we'll need to join it later
    calcThread.detach(); 

    while (solarsystem.game.isRunning) {  // Make sure this access is thread-safe!
        time = timeObject.calculateTimeElapsedAndUpdateTime() ; 
        relativeTime = static_cast <size_t> ( time * TIMEEXPANSIONCOEFFICIENT ) ;   
        modelsMutex.lock () ; 
        solarsystem.game.processInput();
        solarsystem.game.update(relativeTime);
        universe.translateAllModelsAccordingToMouseInput(solarsystem.game.models, solarsystem.game.mouseevent, solarsystem.game.keyboardEvent);
        universe.zoomOutAndRenderTheObjectInTheUniverse(solarsystem.game.models, solarsystem.game.renderer);
        modelsMutex.unlock();
        std::cout << "time elapsed " << time  << std::endl ;
        SDL_Delay(TIME_SPENT_IN_EACH_FRAME );
    }
}
