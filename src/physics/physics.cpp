
#ifndef PHYSICS_CPP
#define PHYSICS_CPP

#include "../myModel/myModel.h"
#include "../myVertex/myVertex.h"
#include "../game/game.h"
#include <iostream>
#include <cmath>
#include <numbers>
#include <mutex>
float GRAVITATIONAL_CONSTANT = 600;
class Physics {

    public: 
    inline float calculateDistanceBetweenTwoModels ( myModel & model1 , myModel & model2 ) {
        float x1 , y1 , z1 , x2 , y2 , z2 ;
        std::tie(x1 , y1 , z1) = model1.getPosition() ;
        std::tie(x2 , y2 , z2) = model2.getPosition() ;
        float distance = std::sqrt( std::pow(x1 - x2 , 2) + std::pow(y1 - y2 , 2) + std::pow(z1 - z2 , 2) ) ;
        return distance ; 
    }

    inline std::tuple<float , float , float  > calculateGravitationalForce ( myModel & model1 , myModel & model2) {
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
    inline void checkForCollisionsInVectorOfPointersToModels (std::vector <myModel *> & models , float allowanceExpansionCofficient , Game  & game  , std::mutex & mutex) {
        while ( game.isRunning) 
       { 
            mutex.lock() ;
            auto positionVector = extractPositionVectorFromModelsVector( models ) ;
            auto vectorContainingRadiusData = extractSizeFromModelsOfSpheres( models ) ; 
            
            std::vector<int> toRemove;
            for (int i = 0 ; i < positionVector.size() ; i++) {
                for (int j = i + 1 ; j < positionVector.size() ; j++ ) { // Avoid self-collision and duplicate checks
                    float allowedDistance = fabs( vectorContainingRadiusData[i] + vectorContainingRadiusData[j] ) ; 
                    float x = getXfromTuple(positionVector[i]) - getXfromTuple( positionVector[j]) ; 
                    float y = getYfromTuple(positionVector[i]) - getYfromTuple( positionVector[j]) ; 
                    float z = getZfromTuple(positionVector[i]) - getZfromTuple( positionVector[j]) ; 
                    if ( x < allowedDistance * allowanceExpansionCofficient || y < allowedDistance * allowanceExpansionCofficient || z < allowedDistance * allowanceExpansionCofficient ) {
                        toRemove.push_back(i);
                        toRemove.push_back(j);
                    
                        myModel * doublePointer = new  myModel{ inelasticCollideModels( *models[i] , *models[j])} ; 
            
                        models.push_back(doublePointer);
                    
                    }   
                }
            }

            for ( int i = 0 ; i < toRemove.size() ; i++ ) {
                if ( models[toRemove[i]] != nullptr ) {
                    delete models[toRemove[i]] ;
                    models[toRemove[i]] = nullptr ; }
            } 

        
            std::vector <myModel *> duplicatesRemoved; 
            duplicatesRemoved.clear() ;
            for ( int i = 0 ; i < models.size() ; i++ ) {
                if ( models[i] != nullptr ) {
                    duplicatesRemoved.push_back(models[i]) ; 
                }
            }
        
            models.clear() ;
            models = duplicatesRemoved ;
            
            duplicatesRemoved.clear() ;
            mutex.unlock() ;
            SDL_Delay(100);
        }

            } 
    inline myModel inelasticCollideModels( myModel & model1 , myModel & model2) {
            myModel model3 ; 
            model3 = model1 ;
            model3.scale( 3.0f ) ;
            model3.mass = model1.mass + model2.mass ; 
            model3.velocity = giveMeanTuple( model1.velocity , model2.velocity) ; 
            model3.angularAcceleration = giveMeanTuple ( model1.acceleration , model2.acceleration) ;
            model3.angularVelocity = giveMeanTuple ( model1.angularVelocity , model2.angularVelocity) ;
            return model3 ;    
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