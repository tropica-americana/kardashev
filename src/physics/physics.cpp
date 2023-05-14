
#include "../myModel/myModel.h"
#include "../myVertex/myVertex.h"
#include "../game/game.h"
#include <iostream>
#include <cmath>
#include <numbers>
float GRAVITATIONAL_CONSTANT = 60;
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