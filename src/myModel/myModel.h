#ifndef _MYMODEL_H_
#define _MYMODEL_H_

#include <iostream>
#include <array>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "../Quadrant/Quadrant.h"
#include "../nothingClass /nothingClass.h"
#include "../myVertex/myVertex.h"
#include <mutex>
#include <tuple>
#include <cmath>
#include <fstream>
#include <regex>
class myModel : public myNothingClass {
public:
    std::string modelName;
    std::vector<myVertex *> vertices;
    std::vector<std::tuple<int, int>> Mesh;
    std::tuple<float , float  , float > velocity ; 
    std::tuple<float , float  , float > acceleration ;
    float mass ; 
    std::string currentMode  = "translate" ; 
    bool vertexFinalized = true ; 
    myModel () ;  
    ~myModel() ;
    void renderMyself(SDL_Renderer *renderer) override;
    void translate(float xTranslateParameter, float yTranslateParameter, float zTranslateParameter) override;
    void rotate(float xRotateParameter, float yRotateParameter, float zRotateParameter) override;
    void processInput(const SDL_MouseMotionEvent &mouseEvent , const SDL_KeyboardEvent & keyboardEvent ) override;
    void addVertex (float xAmount , float yAmount , float zAmount) override;
    void addVertex (myVertex vertex) ; 
    void createMesh() override;
    void scale (float lenght ) ;
    void saveModel(std::string filename , std::string modelName ) ;
    bool loadModel (std::string filename , std::string modelName ) ;  
    void  joinWithMyModel ( myModel  & anotherModel  ) ; 
    bool isTouchingModel ( const SDL_MouseMotionEvent & mouseEvent ) ;
    void accelerate ( float xAcceleration , float yAcceleration , float zAcceleration  , size_t time_in_milliseconds) ;
    void move (size_t timeInMilliseconds) ;
    void moveTo ( float x , float y , float z ) ; 
    std::tuple<float , float , float > getPosition () ; 
    myVertex * getCenterOfMass() ;
    myModel & operator = (const myModel & other) ;
};

#endif 