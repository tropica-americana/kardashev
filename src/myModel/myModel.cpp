#include "./myModel.h"
#include <cstdio>
#include <sstream>
myModel::myModel () {
        vertices.clear() ;  
}
myModel:: ~myModel() {
    for (auto * pointerToVertice : vertices ) {
        delete pointerToVertice ; 
    }
    //atleast these pointers must be destroyed
}
void myModel::renderMyself(SDL_Renderer *renderer) {
    if (vertices.size() < 5) {
        // std::cout << "not enough vertices to render " << std::endl;
        return;
    }
    SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);
    for (auto &meshLine : Mesh) {
        int meshIndex1 = std::get<0>(meshLine);
        int meshIndex2 = std::get<1>(meshLine);
        SDL_RenderDrawLine(renderer, vertices[meshIndex1]->getOnScreenX(), vertices[meshIndex1]->getOnScreenY(), vertices[meshIndex2]->getOnScreenX(), vertices[meshIndex2]->getOnScreenY());
    }
}
void myModel :: renderMyselfAccordingToZoomLevelAndScreePixelResolution ( SDL_Renderer * renderer , float zoomLevel , float horizontalPixelResolution  , float verticalPixelResolution){
    float z = std::get<2>(getPosition());
    if ( z < -vertices[0]->distanceFromObserver ) {
        // std::cout << "not rendering model " << std::endl;
        return ; 
    }
    if ( z > vertices[0]->distanceFromObserver * 300 ) {
        // std::cout << "not rendering model " << std::endl;
        return ; 
    }

    if ( stringMap["isRendering"] == "false" ) {
        return ; 
    }
    if (vertices.size() < 5) {
        // std::cout << "not enough vertices to render " << std::endl;
        return;
    }
    SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);
    for (auto &meshLine : Mesh) {
        int meshIndex1 = std::get<0>(meshLine);
        int meshIndex2 = std::get<1>(meshLine);
        SDL_RenderDrawLine(renderer, ((vertices[meshIndex1]->getOnScreenX())*zoomLevel + ((horizontalPixelResolution )/2) ) , ((vertices[meshIndex1]->getOnScreenY())*zoomLevel + ((verticalPixelResolution )/2) ) , ((vertices[meshIndex2]->getOnScreenX())*zoomLevel + ((horizontalPixelResolution )/2) ) , ((vertices[meshIndex2]->getOnScreenY())*zoomLevel + ((verticalPixelResolution )/2) ) );
    }
}
void myModel::translate(float xTranslateParameter, float yTranslateParameter, float zTranslateParameter) {
    for (auto &item : vertices) {
        item->translate(xTranslateParameter, yTranslateParameter, zTranslateParameter);
    }
}

void myModel::rotate(float xRotateParameter, float yRotateParameter, float zRotateParameter) {
    for (auto &item : vertices) {
        item->rotateMyVertex(xRotateParameter, yRotateParameter, zRotateParameter);
    }
}
void myModel :: rotateWithAngularVelocityInTime ( size_t time_in_milliseconds ) {
    rotate ( std::get <0> ( angularVelocity) * static_cast<float> ( time_in_milliseconds ) , std::get <1> (angularVelocity) * static_cast<float> ( time_in_milliseconds ) , std::get<2> (angularVelocity) * static_cast<float> ( time_in_milliseconds ) ); 
}

void myModel::processInput(const SDL_MouseMotionEvent &mouseEvent , const SDL_KeyboardEvent &keyboardEvent) {
    if ( stringMap["input"] == "false") 
    return ; 
    bool keyPressed = true ; 
    bool invertedRotation = false ;
    // iterating through all the events of sdl events 
    // check wheter the user is pressing the e key 
    
    if (keyboardEvent.keysym.sym == SDLK_e && keyPressed == true){
        invertedRotation = true ;
    }
    else { invertedRotation = false ; }
    
    if (stringMap["input"] != "false") {
        float simultaneousMotionFactor{ 1.0f }; 
            // check whether user is not pressing any key 
            if (keyboardEvent.type == SDL_KEYUP) {
                keyPressed = false ;
            }
            if (keyboardEvent.type == SDL_KEYDOWN) {
                keyPressed = true ;
            }
            // check wheater the t key is being pressed 
            if (keyboardEvent.keysym.sym == SDLK_t && keyPressed == true) {  
                if (mouseEvent.state & SDL_BUTTON_LMASK) {
                translate(mouseEvent.xrel * simultaneousMotionFactor,
                    mouseEvent.yrel * simultaneousMotionFactor, 0.0f);
                }
            }
            
            // check wheter is r key is being pressed 
            if (keyboardEvent.keysym.sym == SDLK_r && keyPressed == true) {
                simultaneousMotionFactor = 0.01f; 
                if (mouseEvent.state & SDL_BUTTON_LMASK) {
                    rotate(mouseEvent.yrel * simultaneousMotionFactor,
                        mouseEvent.xrel * simultaneousMotionFactor, 0.0f);
                }
            }  
            // check wheater a key is being pressed 
            if (keyboardEvent.keysym.sym == SDLK_a && keyPressed == true) {
                simultaneousMotionFactor = 1.0f; 
                
                
                if (mouseEvent.state & SDL_BUTTON_LMASK) {
                    // check wheter the vertex was finalized or not to check if its the first time user pressed a 
                    if (vertexFinalized == true) {
                        myVertex newVertex ; 
                        //copying the trasnlation values of the first vertex to new vertex
                        newVertex.xTranslate = vertices[0]->xTranslate ;
                        newVertex.yTranslate = vertices[0]->yTranslate ;
                        newVertex.zTranslate = vertices[0]->zTranslate ;
                        newVertex.x = mouseEvent.x - newVertex.xTranslate ;
                        newVertex.y = mouseEvent.y - newVertex.yTranslate ;
                        newVertex.z = 0.01f ;
                        vertices.push_back( new myVertex{newVertex} ) ;
                        vertexFinalized = false ;
                        createMesh() ; 
                    }
                    if ( vertexFinalized == false ) {
                        vertices[vertices.size() - 1]->x += mouseEvent.xrel * simultaneousMotionFactor ;
                        vertices[vertices.size() - 1]->y += mouseEvent.yrel * simultaneousMotionFactor ;
                        // createMesh() ;
                        
                    }
                
                
                }
            }
            if (keyboardEvent.keysym.sym == SDLK_f && keyPressed == true) {
                        vertexFinalized = true ; 
                    }
            float amountToRotate = 0.1f  ; 
            // check whetther the user pressed the 1 key 
            if (keyboardEvent.keysym.sym == SDLK_1 && keyPressed == true){
                //check whether the user is pressing the right mouse button
                std::cout << invertedRotation << std::endl ;
                if (invertedRotation == true) {
                    rotate(-amountToRotate, 0.0f, 0.0f);
                }
                else rotate(amountToRotate, 0.0f, 0.0f);
            }
            // check whetther the user pressed the 2 key
            if (keyboardEvent.keysym.sym == SDLK_2 && keyPressed == true){
                // check whether the user is pressing the right mouse button
                if (invertedRotation == true) {
                    rotate(0.0f,-amountToRotate, 0.0f);
                }
                else rotate(0.0f, amountToRotate, 0.0f);
            
            }
            // check whetther the user pressed the 3 key
            if (keyboardEvent.keysym.sym == SDLK_3 && keyPressed == true){
                // check whether the user is pressing the right mouse button
                if (invertedRotation == true) {
                rotate(0.0f, 0.0f, amountToRotate);
                }
                else rotate(0.0f, 0.0f, -amountToRotate);
            
            }
            // check whether down arrow key was pressed 
            if (keyboardEvent.keysym.sym == SDLK_DOWN && keyPressed == true){
                scale(0.9) ; 
            }
            // check whether up arrow key was pressed
            if (keyboardEvent.keysym.sym == SDLK_UP && keyPressed == true){
                scale(1.1) ; 
            }

            // check if user pressed the s key to save the model 
            if (keyboardEvent.keysym.sym == SDLK_s && keyPressed == true){
                std::string modelName ; 
                std::cout << "Enter the name of the model you want to save" << std::endl ;
                std::cin >> modelName ;
                if (modelName == "" || modelName == " " || modelName == "\n"){
                    return ; 
                }
                saveModel( "data.txt", modelName) ;
            }
    }
    
}
// this might be  a failed function . 
// void myModel::processInput(SDL_Event& event) {
//     if ( currentMode == "translate" ) {
//         if (event.type == SDL_MOUSEBUTTONDOWN) {
//             // getting the mouse motion event 
            
//         }
//     }
//     if (currentMode == "modify"){

//     }

// }


void myModel::addVertex (float xAmount, float yAmount, float zAmount) {
    myVertex* newVertex = new myVertex(xAmount, yAmount, zAmount);
    newVertex->xTranslate = 0.0f ; 
    newVertex->yTranslate = 0.0f ; 
    newVertex->zTranslate = 0.0f ; 
    vertices.push_back(newVertex);
}// bug prone area 

void myModel::addVertex (myVertex vertex) {
    addVertex( vertex.x , vertex.y , vertex.z) ; 
}// bug prone area 
void myModel::createMesh(){

    for (size_t i = 0; i < vertices.size(); i++){
        std::vector <std::tuple <int  , float>> focusedVertexDistanceFromVerticesMemberTupleVector  ; 

        //making a for loop for calculating the distance of each item from the focused vertex and then sorting out
        // top 5 smallest distances from the focused vertex 
        for (int j = 0; j < vertices.size() ; j++) {
            if (j != i ){
            //calculating the x -distance of focused vertex
            float x = vertices[i]->x; 
            //calculating the y -distance of focused vertex
            float y = vertices[i]-> y ; 
            //calculating the z -distance of focused vertex
            float z = vertices[i]-> z ; 
            //calculating the x -distance of current vertex 
            float x2 = vertices[j]->x ; 
            //calculating the y -distance of current vertex 
            float y2 = vertices[j]->y ; 
            //calculating the z -distance of current vertex 
            float z2 = vertices[j]->z ; 
            // calculating the distance between 2 vertcies 
            float distance = sqrt(pow(x - x2, 2) + pow(y - y2, 2) + pow(z - z2, 2)) ; 
            focusedVertexDistanceFromVerticesMemberTupleVector.push_back(std::make_tuple(j, distance));
            }
        }
        //sorting out the smallest distances from the focused vertex
        std::sort (focusedVertexDistanceFromVerticesMemberTupleVector.begin(),focusedVertexDistanceFromVerticesMemberTupleVector.end() 
        , [](auto const & v1, auto const & v2) {
            return std::get<1>(v1) < std::get<1>(v2);
        }) ; 
        for (int z = 0; z < 8 ; z++){
            Mesh.push_back(std::make_tuple( i , std::get<0>(focusedVertexDistanceFromVerticesMemberTupleVector[z]) )) ; 
        }
        // above code joins the 5 closest vertices 

    }
    // removing the similar contents from the mesh vector is undone for now 
    std::vector<std::tuple<int , int >> modifiedMesh  ; 
    std::copy_if (Mesh.begin () , Mesh.end () , std::back_inserter(modifiedMesh) , [&modifiedMesh](auto const & v1) {
       bool found ; 
         for (auto const & v2 : modifiedMesh ) {
              if (std::get<0>(v1) == std::get<1>(v2) && std::get<1>(v1) == std::get<0>(v2)) {
                found = true ; 
                break ; 
              }
              if (std::get<0>(v1) == std::get<1>(v2) && std::get<0>(v1) == std::get<1>(v2)) {
                found = true ; 
                break ; 
              }
         }
        //  if (found == true) {
        //      std::cout << "removing the similar contents from the mesh vector " << std::endl ;
        //   } // this is a sample code 
        return !found ;
         
    }) ;
} 

void myModel :: scale(float length ) {
    for (auto * vertex : vertices ) {
        vertex->scale(length);
    }

}        

void myModel :: saveModel (std::string filename , std::string modelName ) {
    // lowing all the models and finding if the model with the similar name exists and also storing the model in seperate stirngs 
    std::ifstream input_file (filename) ; 
    std::vector<std::string> dataAsLinesInAVector ; 
    std::string currentStringStoringGetLine ; 
    std::string extractedModelNameFromTheFile ; 
    std::string stringContainingModifiedModelData ; 
    bool found = false ;
    while ( !input_file.eof()){
        std::getline(input_file , currentStringStoringGetLine) ; 
        std::istringstream iss(currentStringStoringGetLine) ;
        iss >>  extractedModelNameFromTheFile ; 
        // std::cout << extractedModelNameFromTheFile << " is the extracted model name from the line  " << std::endl; 
        if (extractedModelNameFromTheFile == modelName) {
            found = true ; 
            stringContainingModifiedModelData += extractedModelNameFromTheFile ; 
            for (int i = 0 ; i < vertices.size () ; i++ ){
            stringContainingModifiedModelData += " " ; 
            stringContainingModifiedModelData += std::to_string (vertices [i] ->x  ) + " ";
            stringContainingModifiedModelData += std::to_string (vertices [i] ->y  ) + " ";
            stringContainingModifiedModelData += std::to_string (vertices [i] ->z  ) + " ";
            stringContainingModifiedModelData += std::to_string (vertices [i] ->xTranslate  ) + " ";
            stringContainingModifiedModelData += std::to_string (vertices [i] ->yTranslate   ) + " ";
            stringContainingModifiedModelData += std::to_string (vertices [i] ->zTranslate   ) + " ";
            }
            dataAsLinesInAVector.push_back(stringContainingModifiedModelData);
            // std::cout << "model name matched in the first half of the save model function  " << std::endl;
        }
        if (extractedModelNameFromTheFile != modelName) {
            dataAsLinesInAVector.push_back(currentStringStoringGetLine) ; 
        }
        extractedModelNameFromTheFile = "" ; 
        // apparently iss>> extractModelNameFromTheFile does not work properly and does not nullify the string when the line is empty 
        
    }

        input_file.close () ; 

    // -------- ------------------------------------------------------------
        std::ofstream out (filename)  ; 
        for (auto item : dataAsLinesInAVector) {
            out << item ; 
            // std::cout << item << std::endl ; 
            out << std::endl ; 
        }
        // std::cout << found << std::endl ; 
        if (found  != 1  ) {
            // std::cout << "creating new model and saving it because found is false " <<std::endl; 
            stringContainingModifiedModelData = "" ; 
            stringContainingModifiedModelData += modelName  ; 
            for (int i = 0 ; i < vertices.size () ; i++ ){
            stringContainingModifiedModelData += " " ; 
            stringContainingModifiedModelData += std::to_string (vertices [i] ->x  ) + " ";
            stringContainingModifiedModelData += std::to_string (vertices [i] ->y  ) + " ";
            stringContainingModifiedModelData += std::to_string (vertices [i] ->z  ) + " ";
            stringContainingModifiedModelData += std::to_string (vertices [i] ->xTranslate  ) + " ";
            stringContainingModifiedModelData += std::to_string (vertices [i] ->yTranslate   ) + " ";
            stringContainingModifiedModelData += std::to_string (vertices [i] ->zTranslate   ) + " ";
            }
            out << stringContainingModifiedModelData ; 
        }
       
        out.close() ; 
}
    
bool myModel::loadModel(std::string filename, std::string modelName) {
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return false;
    }

    std::string line;
    bool found = false;
    while (std::getline(inFile, line) && !found) {
        std::istringstream iss(line);
        std::string currentModelName;
        iss >> currentModelName;

        if (currentModelName == modelName) {
            found = true;
            vertices.clear(); // Clear existing vertices before loading new model

            int index = 0;
            float value;
            vertices.push_back(new myVertex());

            while (iss >> value) {
                int moduloIndex = index % 6;
                // bug prone area above 
                switch (moduloIndex) {
                    case 0: vertices.back()->x = value; break;
                    case 1: vertices.back()->y = value; break;
                    case 2: vertices.back()->z = value; break;
                    case 3: vertices.back()->xTranslate = value; break;
                    case 4: vertices.back()->yTranslate = value; break;
                    case 5:
                        vertices.back()->zTranslate = value;
                        vertices.push_back(new myVertex());
                        break;
                }
                index++;
            }
            vertices.pop_back(); // Remove the last unused vertex
            createMesh();
        }
    }

    inFile.close();

    if (found) {
        std::cout << "Model found." << std::endl;
        return true;
    } else {
        std::cout << "Model not found." << std::endl;
        return false;
    }
}

myModel & myModel :: operator = (const myModel & other ) {
        modelName = other.modelName ; 
        for ( const auto & item : other.vertices ) {
            vertices.push_back ( new myVertex ( * item ) ) ; 
        }
        Mesh = other.Mesh ;
        velocity = other.velocity ;
        acceleration = other.acceleration ;
        angularVelocity = other.angularVelocity ;
        mass = other.mass ;
        angularAcceleration = other.angularAcceleration ;
        return *this ; 
}
// myVertex * myModel :: getCenterOfMass( ) {
//     // std::cout << "getting center of mass " << std::endl ; 
//     float x = 0 ; 
//     float y = 0 ; 
//     float z = 0 ; 
//     for (int i = 0 ; i < vertices.size () ; i++ ) {
//         x += vertices [i] -> x ; 
//         y += vertices [i] -> y ; 
//         z += vertices [i] -> z ; 
//     }
//     x /= vertices.size () ; 
//     y /= vertices.size () ; 
//     z /= vertices.size () ; 
//     // std::cout << "center of mass is " << x << " " << y << " " << z << std::endl ; 
//     return new myVertex (x , y , z ) ; 
// }   

void myModel::joinWithMyModel ( myModel & anotherModel  ) { 
        auto & anotherVertices = anotherModel.vertices ;
        for (int i = 0 ; i < anotherVertices.size() ; i++ ) {
                auto pointerToCurrentVertice = anotherVertices[i] ;
                //deleting the value of anotherVertices[i] 
                anotherVertices[i] = nullptr ;
                float x = pointerToCurrentVertice -> x + pointerToCurrentVertice -> xTranslate - vertices [0] -> xTranslate ;
                float y = pointerToCurrentVertice -> y + pointerToCurrentVertice -> yTranslate - vertices [0] -> yTranslate ;
                float z = pointerToCurrentVertice -> z + pointerToCurrentVertice -> zTranslate  - vertices [0] -> zTranslate ;
                pointerToCurrentVertice -> xTranslate  =  vertices [0] -> xTranslate ;
                pointerToCurrentVertice -> yTranslate  =  vertices [0] -> yTranslate ;
                pointerToCurrentVertice -> zTranslate  =  vertices [0] -> zTranslate ;
                pointerToCurrentVertice -> x = x ;
                pointerToCurrentVertice -> y = y ;
                pointerToCurrentVertice -> z = z ;
                vertices.push_back (pointerToCurrentVertice) ;
                }
                createMesh () ;

                }

bool myModel :: isTouchingModel (const SDL_MouseMotionEvent & mousevent ) {
    float yMax = 0  ; 
    float yMin = 0 ;
    float xMax = 0 ;
    float xMin = 0 ;
    for (myVertex * vertex : vertices  ) {
        if (vertex -> getOnScreenY()> yMax ) {
            yMax = vertex -> getOnScreenY() ; 
        }
        if (vertex -> getOnScreenY() < yMin ) {
            yMin = vertex -> getOnScreenY() ;       
        }
        if (vertex -> getOnScreenX() > xMax ) {
            xMax = vertex -> getOnScreenX() ;
        }
        if (vertex -> getOnScreenX() < xMin ) {
            xMin = vertex -> getOnScreenX() ;
        }
    }
    if (mousevent.y > yMin && mousevent.y < yMax && mousevent.x > xMin && mousevent.x < xMax ) {
        return  true ; 
    }
    else {
        return  false ; 
    }
}

void myModel::accelerate ( float x , float y , float z , size_t timeInMilliseconds) {
    std::get<0> ( velocity )  += std::get<0> ( acceleration) *   static_cast<float> (timeInMilliseconds)   ;
    std::get<1> ( velocity )  += std::get<1> ( acceleration) *   static_cast<float> (timeInMilliseconds)   ;
    std::get<2> ( velocity )  += std::get<2> ( acceleration) *   static_cast<float> (timeInMilliseconds)   ;
     
     // zeroing the acceleration after converting it to velocity for the next cycle 
   
}
void myModel :: angularAccelerate (size_t time_in_milliseconds ) {
    std::get <0> (angularVelocity) += std::get<0> (angularAcceleration) * static_cast <float>(time_in_milliseconds) ; 
    std::get <1> (angularVelocity) += std::get<1> (angularAcceleration) * static_cast <float>(time_in_milliseconds) ;
    std::get <2> (angularVelocity) += std::get<2> (angularAcceleration) * static_cast <float>(time_in_milliseconds) ;

}

void myModel :: move ( size_t timeInMilliseconds ) {
    for ( myVertex * vertex : vertices ) {
        vertex -> xTranslate += std::get<0> ( velocity ) * static_cast<float> (timeInMilliseconds)  ;
        vertex -> yTranslate += std::get<1> ( velocity ) * static_cast<float> (timeInMilliseconds)  ;
        vertex -> zTranslate += std::get<2> ( velocity ) * static_cast<float> (timeInMilliseconds)  ;
    }
    accelerate ( std::get<0> ( acceleration) , std::get<1> ( acceleration) , std::get<2> ( acceleration) , timeInMilliseconds ) ;
    rotateWithAngularVelocityInTime ( timeInMilliseconds ) ;
    angularAccelerate ( timeInMilliseconds ) ;
    zeroTheAcceleration () ;
    
}
void myModel :: zeroTheAcceleration () {
    std::get<0> ( acceleration ) = 0 ; 
    std::get<1> ( acceleration ) = 0 ; 
    std::get<2> ( acceleration ) = 0 ; 
}
void myModel :: moveTo ( float x , float y , float z ) {
   
    for ( myVertex * item: vertices ) {
      
            item -> xTranslate = x ; 
            item -> yTranslate = y ;
            item -> zTranslate = z ; 
        }
}

std::tuple<float , float , float > myModel :: getPosition (){
    return std::make_tuple ( vertices [0] -> xTranslate , vertices [0] -> yTranslate , vertices [0] -> zTranslate ) ; 
} 


