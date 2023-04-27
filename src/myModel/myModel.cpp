#include "./myModel.h"
#include <cstdio>
#include <sstream>
myModel::myModel () {

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

void myModel::processInput(const SDL_MouseMotionEvent &mouseEvent , const SDL_KeyboardEvent &keyboardEvent) {
    bool keyPressed = true ; 
    if (currentMode == "translate"){
        float simultaneousMotionFactor{ 1.0f };
        if (mouseEvent.state & SDL_BUTTON_LMASK) {
            translate(mouseEvent.xrel * simultaneousMotionFactor,
                mouseEvent.yrel * simultaneousMotionFactor, 0.0f);
    }}
    if (currentMode == "modify") {
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
                    vertices.push_back( new myVertex(mouseEvent.x * simultaneousMotionFactor , mouseEvent.y * simultaneousMotionFactor , 0.0f) ) ;
                    vertexFinalized = false ;
                    createMesh() ; 
                }
                if ( vertexFinalized == false ) {
                    vertices[vertices.size() - 1]->x = mouseEvent.x * simultaneousMotionFactor ; 
                    vertices[vertices.size() - 1]->y = mouseEvent.y * simultaneousMotionFactor ; 
                    vertices[vertices.size() - 1]->z = 0.0f ; 
                    createMesh() ;
                }
                // check wheater the user pressed f key to finalize the vertex
             
            }
        }
         if (keyboardEvent.keysym.sym == SDLK_f && keyPressed == true) {
                    vertexFinalized = true ; 
                }
        
         
    }
    
}

void myModel::addVertex (float xAmount, float yAmount, float zAmount) {
    myVertex* newVertex = new myVertex(xAmount, yAmount, zAmount);
    vertices.push_back(newVertex);
}

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
        for (int z = 0; z < 5 ; z++){
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

void myModel :: saveModel (std::string filename , std::string modelName  ) {
    // loading all the models and finding if the model with the similar name exists and also storing the model in seperate stirngs 
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
            stringContainingModifiedModelData += std::to_string (vertices [i] ->xRotate  ) + " ";
            stringContainingModifiedModelData += std::to_string (vertices [i] ->yRotate  ) + " ";
            stringContainingModifiedModelData += std::to_string (vertices [i] ->zRotate  ) + " ";
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
            stringContainingModifiedModelData += std::to_string (vertices [i] ->xRotate  ) + " ";
            stringContainingModifiedModelData += std::to_string (vertices [i] ->yRotate  ) + " ";
            stringContainingModifiedModelData += std::to_string (vertices [i] ->zRotate  ) + " ";
            stringContainingModifiedModelData += std::to_string (vertices [i] ->xTranslate  ) + " ";
            stringContainingModifiedModelData += std::to_string (vertices [i] ->yTranslate   ) + " ";
            stringContainingModifiedModelData += std::to_string (vertices [i] ->zTranslate   ) + " ";
            }
            out << stringContainingModifiedModelData ; 
        }
       
        out.close() ; 
}
    
bool myModel :: loadModel (std::string filename , std::string modelName )  {

        std::ifstream in ; 
        std::string currentStringLine ;  
        std::string currentWord ; 
        float currentFloat ; 
        std::smatch match ; 
        bool found = false ;
        // std::regex matchAFloat("^[+-]?[0-9]+(\\.[0-9]+)?$");
        // std::regex matchAString ("^[A-Za-z]+[\\s]+([A-Za-z]+[\\s]?)+$"); 
        in.open(filename ) ; // opening the file 
        if (!in.is_open () ) // chekcing if file is opened succesfully  
        {
            std::cerr << "Failed to open the file: " << filename << std::endl;
        }
        while ( ! in.eof() && !found ){
            // iterating through the file till the end of the file arrives 
            std::getline ( in , currentStringLine) ;
            // std::cout<<currentStringLine<<std::endl; // ---> a good breakpoint
            std::istringstream iss (currentStringLine);
            iss >> currentWord ; 
            int currentIndex = 0 ; 
            int numberOfTimesWhileLoopIterated = 0 ; 
            vertices.push_back( new myVertex ) ; // adding the first vertex to the vertices 
            std::cout << currentWord << std::endl;
            if (currentWord == modelName) { //----------------------------------------------------------------
            found = true ; 
            while ( iss >> currentFloat ){
                int moduloIndex = numberOfTimesWhileLoopIterated % 9  ;
                if (moduloIndex == 0 && numberOfTimesWhileLoopIterated > 0 ){
                    currentIndex += 1 ; 
                    vertices.push_back( new myVertex ) ; 
                    }  
                if (moduloIndex == 0) vertices[currentIndex]->x = currentFloat ; 
                if (moduloIndex == 1) vertices[currentIndex]->y = currentFloat ; 
                if (moduloIndex == 2) vertices[currentIndex]->z = currentFloat ; 
                if (moduloIndex == 3) vertices[currentIndex]->xRotate = currentFloat ; 
                if (moduloIndex == 4) vertices[currentIndex]->yRotate = currentFloat ; 
                if (moduloIndex == 5) vertices[currentIndex]->zRotate = currentFloat ; 
                if (moduloIndex == 6) vertices[currentIndex]->xTranslate = currentFloat ; 
                if (moduloIndex == 7) vertices[currentIndex]->yTranslate = currentFloat ; 
                if (moduloIndex == 8) vertices[currentIndex]->zTranslate = currentFloat ; 
                numberOfTimesWhileLoopIterated += 1 ;

            }
            createMesh() ; // ---------very important to create a mesh to render 

            } 
           
            else if ( currentWord != modelName ) {
                    // std::cout << "model not found "<<std::endl;
                }
        }  
        if (found == true ) {
             std::cout << "model found "<<std::endl; 
            return true ;  
            }
        if (found == false) {
            std::cout << "model not found "<<std::endl;
            return  false  ;
            }
          
            }

myModel & myModel :: operator = (const myModel & other ) {
        modelName = other.modelName ; 
        for ( const auto & item : other.vertices ) {
            vertices.push_back ( new myVertex ( * item ) ) ; 
        }
        Mesh = other.Mesh ;
        
        return *this ; 
}