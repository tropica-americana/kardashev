
#ifndef PHYSICS_CPP
#define PHYSICS_CPP
#include "../myModel/myModel.h"
#include "../myVertex/myVertex.h"
#include "../game/game.h"
#include "../Time/Time.h"
#include <iostream>
#include <cmath>
#include <numbers>
#include <mutex>
float GRAVITATIONAL_CONSTANT = 6000;
class Physics {

    public: 
    inline float calculateDistanceBetweenTwoModels ( myModel & model1 , myModel & model2 ) {
        float x1 , y1 , z1 , x2 , y2 , z2 ;
        std::tie(x1 , y1 , z1) = model1.getPosition() ;
        std::tie(x2 , y2 , z2) = model2.getPosition() ;
        float distance = std::sqrt( std::pow(x1 - x2 , 2) + std::pow(y1 - y2 , 2) + std::pow(z1 - z2 , 2) ) ;
        return distance ; 
    }

    inline std::tuple<float , float , float  > calculateGravitationalForce ( myModel & model1 , myModel & model2 , float allowanceExpansionCoefficient  ) {
        if (calculateDistanceBetweenTwoModels ( model1 , model2 ) <  1.0f  ) {
            return {0.0f , 0.0f , 0.0f} ;
        }
        // CHECKING IF THE DISTANCE BETWEEN MODEL1 AND MODEL2 IS  GREATER  THAN THE SUM OF THE RADIUS OF THE TWO MODELS
        std::tuple <float , float , float > model1Position = model1.getPosition() ;
        std::tuple <float , float , float > model2Position = model2.getPosition() ;
        float radiusOfModel1 = getRadius ( model1 ) ;
        float radiusOfModel2 = getRadius ( model2 ) ;
        float distance = calculateDistanceBetweenTwoModels ( model1 , model2 ) ;
        // if  ( distance > ( radiusOfModel1 + radiusOfModel2 ) * allowanceExpansionCoefficient ) {
        float xDistance = std::get<0>(model1Position) - std::get<0>(model2Position) ;
        float yDistance = std::get<1>(model1Position) - std::get<1>(model2Position) ;
        float zDistance = std::get<2>(model1Position) - std::get<2>(model2Position) ;
        float force = ( GRAVITATIONAL_CONSTANT * model1.mass * model2.mass ) / std::pow(distance , 2) ;
        float xForce = ( force * xDistance ) / distance ;
        float yForce = ( force * yDistance ) / distance ;
        float zForce = ( force * zDistance ) / distance ;
        return { -xForce , -yForce ,  -zForce } ;
        
        }
    inline float getRadius ( myModel & model ) {
        float radius = 0.0f ; 
        radius = model.vertices[0]->x ;
        // coverting to positive vlaue 
        if ( radius < 0 ) {
            radius = -radius ; 
        }
        return radius ; 
    }
        
    inline void addAccelarationToTheModelAccordingToCurrentForce  ( myModel & model , std::tuple<float , float , float > & force  ) {

        float xAcceleration = std::get<0>(force) / model.mass ;
        float yAcceleration = std::get<1>(force) / model.mass ;
        float zAcceleration = std::get<2>(force) / model.mass ;
        std::get <0> (model.acceleration) += xAcceleration ;
        std::get <1> (model.acceleration) += yAcceleration ;
        std::get <2> (model.acceleration) += zAcceleration ;
        
        }
    
    inline std::vector<std::tuple<float, float, float>> extractPositionVectorFromModelsVector(const std::vector<myModel*>& models) {
        std::vector<std::tuple<float, float, float>> positionVector;
        positionVector.reserve(models.size());
        positionVector.clear();
        for (const auto& model : models) {
            if ( model != nullptr)
          {  std::tuple<float, float, float> tuple = model->getPosition();
            positionVector.push_back(tuple);}
        }
        return positionVector;
        }
    inline std::vector <float> extractSizeFromModelsOfSpheres (std::vector <myModel * > & models ) {
        std::vector<float> vectorContainingRadiusOfModels ; 
        vectorContainingRadiusOfModels.clear() ; 
        for ( auto & item : models ) {
            float radius = (item->vertices[0])->x  ; 
            vectorContainingRadiusOfModels.push_back( radius ) ; 
        } 
        return vectorContainingRadiusOfModels ; 
    } 
    inline std::tuple <float , float , float > giveMeanTuple (std::tuple <float , float , float > & tuple1 , std::tuple <float , float , float > tuple2 ){
        
        float meanX = (getXfromTuple( tuple1 ) + getXfromTuple( tuple2 ) ) / 2 ; 
        float meanY = (getYfromTuple( tuple1 ) + getYfromTuple( tuple2 ) ) / 2 ; 
        float meanZ = (getZfromTuple( tuple1 ) + getZfromTuple( tuple2 ) ) / 2 ; 
        return std::make_tuple ( meanX , meanY , meanZ) ; 
    }
    inline void checkForCollisionsInVectorOfPointersToModels (std::vector <myModel *> & models , float allowanceExpansionCofficient ) {
        Time timeObject ; 
        
        auto positionVector = extractPositionVectorFromModelsVector( models ) ;
 
        auto vectorContainingRadiusData = extractSizeFromModelsOfSpheres( models ) ;         
 
        for (int i = 0 ; i < positionVector.size() ; i++) {
 
            for (int j = i + 1 ; j < positionVector.size() ; j++ ) { // Avoid self-collision and duplicate checks
 
                float allowedDistance = fabs( vectorContainingRadiusData[i] + vectorContainingRadiusData[j] ) ; 
                float x = getXfromTuple(positionVector[i]) - getXfromTuple( positionVector[j]) ; 
                float y = getYfromTuple(positionVector[i]) - getYfromTuple( positionVector[j]) ; 
                float z = getZfromTuple(positionVector[i]) - getZfromTuple( positionVector[j]) ; 
                if ( x < allowedDistance * allowanceExpansionCofficient && y < allowedDistance * allowanceExpansionCofficient && z < allowedDistance * allowanceExpansionCofficient ) {
                    
                        inelasticCollideModels( *models[i] , *models[j] ) ;
                        std::cout << "colliding models  "<< i << "  and  " << j  << std::endl ;
                
                }   
            }
        }
        
        timeObject.outputTimeElapsedAfterCreationOfObject("collision detection");
        
        SDL_Delay(100);

    } 
    inline void inelasticCollideModels( myModel & model1 , myModel & model2) {
            if ( std::find ( model1.vectorOfModelsCollidedWithThisModel.begin() , model1.vectorOfModelsCollidedWithThisModel.end() , &model2 ) != model1.vectorOfModelsCollidedWithThisModel.end())
            return ; 
            // calculating the combined momentum of system in different directions 
            float xMomentum = (model1.mass * std::get<0>(model1.velocity)) + model2.mass * std::get<0>(model2.velocity) ;
            float yMomentum = (model1.mass * std::get<1>(model1.velocity) )+ model2.mass * std::get<1>(model2.velocity) ;
            float zMomentum = (model1.mass * std::get<2>(model1.velocity) )+ model2.mass * std::get<2>(model2.velocity) ;
            // calculating the combined mass of the system
            float combinedMass = model1.mass + model2.mass ;
            // calculating the velocity of the system after collision
            float xVelocity = xMomentum / combinedMass ;
            float yVelocity = yMomentum / combinedMass ;
            float zVelocity = zMomentum / combinedMass ;
            // making the velocity of both model1 and model2 equal to the velocity of the system after collision
            auto velocity = std::make_tuple(xVelocity , yVelocity , zVelocity) ;
            model1.velocity = velocity ;
            model2.velocity = velocity ;        
            model1.vectorOfModelsCollidedWithThisModel.push_back( &model2 ) ;
            model2.vectorOfModelsCollidedWithThisModel.push_back( &model1 ) ;
            return ;        
                }   

           
    inline float getXfromTuple ( std::tuple <float , float , float > & tuple  ) {
        return std::get<0> ( tuple ) ; 
        } 
    inline float getYfromTuple ( std::tuple <float , float , float > & tuple  ) {
        return std::get<1> ( tuple ) ; 
        } 
    inline float getZfromTuple ( std::tuple <float , float , float > & tuple  ) {
        return std::get<2> ( tuple ) ; 
        } 

};


#endif 