#include "./myModel/myModel.h"
#include "./myVertex/myVertex.h"
#include "./game/game.h"
#include <iostream>
#include <cmath>
#include <numbers>
float MASS_OF_SUN = 10;
float MASS_OF_EARTH = 1;
float GRAVITATIONAL_CONSTANT = 600;
float earthVelocityConstatnt = 1;
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
        sun.moveTo ( 100, 100 , 0 ) ;      
        return sun ;
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

class Physics {
    public: 
    float calculateDistanceBetweenTwoModels ( myModel & model1 , myModel & model2 ) {
        float x1 , y1 , z1 , x2 , y2 , z2 ;
        std::tie(x1 , y1 , z1) = model1.getPosition() ;
        std::tie(x2 , y2 , z2) = model2.getPosition() ;
        float distance = std::sqrt( std::pow(x1 - x2 , 2) + std::pow(y1 - y2 , 2) + std::pow(z1 - z2 , 2) ) ;
        return distance ; 
    }

    std::tuple<float , float , float  > calculateGravitationalForce ( myModel & model1 , myModel & model2) {
        // we are trying to calculate the force exerted on the model1 by the model 2 
        float distance = calculateDistanceBetweenTwoModels ( model1 , model2 ) ;
        float xDistance = std::get<0>(model1.getPosition()) - std::get<0>(model2.getPosition()) ;
        float yDistance = std::get<1>(model1.getPosition()) - std::get<1>(model2.getPosition()) ;
        float zDistance = std::get<2>(model1.getPosition()) - std::get<2>(model2.getPosition()) ;
        float force = ( GRAVITATIONAL_CONSTANT * model1.mass * model2.mass ) / std::pow(distance , 2) ;
        float xForce = ( force * xDistance ) / distance ;
        float yForce = ( force * yDistance ) / distance ;
        float zForce = ( force * zDistance ) / distance ;
        return { -xForce , -yForce ,  -zForce } ;
    
        }

        
    void  addAccelarationToTheModelAccordingToCurrentForce  ( myModel & model , std::tuple<float , float , float > & force ) {

        float xAcceleration = std::get<0>(force) / model.mass ;
        float yAcceleration = std::get<1>(force) / model.mass ;
        float zAcceleration = std::get<2>(force) / model.mass ;
        std::get <0> (model.acceleration) += xAcceleration ;
        std::get <1> (model.acceleration) += yAcceleration ;
        std::get <2> (model.acceleration) += zAcceleration ;

        }
   


};
void createSolarSystem (std::vector<myModel *> & models) {
    Planets planet ; 
    myModel * earth = new myModel(planet.createEarth()) ;
    models.push_back(earth) ;

    myModel * sun = new myModel(planet.createSun()) ;
    models.push_back(sun) ;
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

float Universe :: zoomAmount = 0.1 ;

void renderSolarSystem () {
    
    Universe universe ;
    solarSystem solarSystem ;
    createSolarSystem(solarSystem.game.models) ;
    while (solarSystem.game.isRunning) {
        
        solarSystem.game.processInput() ;
        solarSystem.calculateAccelerationDueToGravitaionalPullAndAlsoMoveTheModelsInAllTheModelsInVectorOfPointerToModels( 20 ) ;
        solarSystem.game.update( 20 ) ;
        universe.translateAllModelsAccordingToMouseInput ( solarSystem.game.models ,solarSystem.game.mouseevent , solarSystem.game.keyboardEvent) ;
        universe.zoomOutAndRenderTheObjectInTheUniverse ( solarSystem.game.models , solarSystem.game.renderer ) ;
        SDL_Delay(20) ;
    }
}