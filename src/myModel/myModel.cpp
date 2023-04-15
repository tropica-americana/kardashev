#include "./myModel.h"

myModel::myModel () {
    addVertex(212.5, 675.1, 833.0);  // Given vertex
    addVertex(-90.1, 148.0, 340.1);   // Quadrant II
    addVertex(-278.8, -207.4, 557.6);  // Quadrant III
    addVertex(139.2, -436.1, 204.3);  // Quadrant IV
    addVertex(293.2, 366.2, 683.5);  // Quadrant I
    addVertex(-221.1, 259.8, 369.9);  // Quadrant II
    addVertex(-393.6, -319.2, 612.6);  // Quadrant III
    addVertex(75.0, -514.1, 149.3);  // Quadrant IV
    addVertex(395.1, 188.7, 765.0);  // Quadrant I
    addVertex(-122.4, 486.2, 327.1);  // Quadrant II
    createMesh();
}

void myModel::renderMyself(SDL_Renderer *renderer) {
    if (vertices.size() < 5) {
        std::cout << "not enough vertices to render " << std::endl;
        return;
    }
    SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);
    for (auto &meshLine : Mesh) {
        int meshIndex1 = std::get<0>(meshLine);
        int meshIndex2 = std::get<1>(meshLine);
        SDL_RenderDrawLine(renderer, vertices[meshIndex1]->getOnScreenX(), vertices[meshIndex1]->getOnScreenY(), vertices[meshIndex2]->getOnScreenX(), vertices[meshIndex2]->getOnScreenY());
        std::cout<<vertices[meshIndex1]->z <<std::endl; 
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

void myModel::processInput(const SDL_MouseMotionEvent &mouseEvent) {
    float simultaneousMotionFactor{ 1.0f };
    if (mouseEvent.state & SDL_BUTTON_LMASK) {
        translate(mouseEvent.xrel * simultaneousMotionFactor,
            mouseEvent.yrel * simultaneousMotionFactor, 0.0f);
    }
}

void myModel::addVertex(float xAmount, float yAmount, float zAmount) {
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
        for (int z = 0; z < 4 ; z++){
            Mesh.push_back(std::make_tuple( i , std::get<0>(focusedVertexDistanceFromVerticesMemberTupleVector[z]) )) ; 
        }


    }
    return ; 
            
        }