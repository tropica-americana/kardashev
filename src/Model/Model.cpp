#include "Model.h"

Model::Model () {
    addVertex(Vertex(glm::vec3(150.0f, -250.0f, 350.0f)));
    addVertex(Vertex(glm::vec3(12.0f, 180.0f, 220.0f)));
    addVertex(Vertex(glm::vec3(-800.0f, 160.0f, 280.0f)));
    addVertex(Vertex(glm::vec3(50.0f, -100.0, 130.0f)));
    addVertex(Vertex(glm::vec3(-400.0f, 300.0f, 150.0f)));
    addVertex(Vertex(glm::vec3(650.0f, 120.0f, 280.0f)));
    addVertex(Vertex(glm::vec3(300.0f, -400.0f, 500.0f)));
    addVertex(Vertex(glm::vec3(-70.0f, 280.0f, 400.0f)));
    addVertex(Vertex(glm::vec3(900.0f, -200.0f, 350.0f)));
    addVertex(Vertex(glm::vec3(-250.0f, 50.0f, 180.0f)));
    addVertex(Vertex(glm::vec3(600.0f, -450.0f, 220.0f)));
    addVertex(Vertex(glm::vec3(150.0f, 500.0f, 300.0f)));
    addVertex(Vertex(glm::vec3(-50.0f, 80.0f, 420.0f)));
    createMesh();
}
Model::~Model() {
    for (Vertex * vertex : vertices) {
        delete vertex; 
    }
}

void Model::renderMyself(SDL_Renderer* renderer) {
    if (vertices.size() < 9) {
       std::cout <<"not enough vertices to render " << std::endl;
        return;
    }
    SDL_SetRenderDrawColor(renderer , 250, 250, 250, 255);
    for ( auto & meshLine : Mesh ) {
        int meshIndex1 = std::get<0>(meshLine) ;
        int meshIndex2 = std::get<1>(meshLine) ;
        SDL_RenderDrawLine(renderer , (*(vertices[meshIndex1]))[0] , (*(vertices[meshIndex1]))[1] , (*(vertices[meshIndex2]))[0] , (*(vertices[meshIndex2]))[1] ) ; 
    }

}

void Model::translate(const glm::vec3& vec3) {
    for (Vertex * vertex : vertices) {
        vertex->translate(vec3);
    }
}


void Model::rotate(const glm::vec3& orientationVec3) {
    for (auto * vertex : vertices) {
        vertex->rotateVertexGpt(orientationVec3.x , orientationVec3.y , orientationVec3.z);

    }
}


void Model::processInput(const SDL_MouseMotionEvent& mouseEvent) {
    float simultaneousMotionFactor{1.0f};
    if (mouseEvent.state & SDL_BUTTON_LMASK) {
        translate(glm::vec3(mouseEvent.xrel * simultaneousMotionFactor,
                            mouseEvent.yrel * simultaneousMotionFactor, 0.0f));
    }
}

void Model::addVertex(const Vertex & vertex) {
    Vertex * vertexPtr { new Vertex }; 
    *vertexPtr = vertex;
    vertices.push_back( vertexPtr);
}

void Model :: createMesh () {

    for (size_t i = 0; i < vertices.size(); i++){
        std::vector <std::tuple <int  , float>> focusedVertexDistanceFromVerticesMemberTupleVector  ; 

        //making a for loop for calculating the distance of each item from the focused vertex and then sorting out
        // top 5 smallest distances from the focused vertex 
        for (int j = 0; j < vertices.size() ; j++) {
            if (j != i ){
            //calculating the x -distance of focused vertex
            float x = vertices[i]-> getAtIndexExcludingTranslate(0) ; 
            //calculating the y -distance of focused vertex
            float y = vertices[i]-> getAtIndexExcludingTranslate(1) ; 
            //calculating the z -distance of focused vertex
            float z = vertices[i]->getAtIndexExcludingTranslate(2) ; 
            //calculating the x -distance of current vertex 
            float x2 = vertices[j]->getAtIndexExcludingTranslate(0) ; 
            //calculating the y -distance of current vertex 
            float y2 = vertices[j]->getAtIndexExcludingTranslate(1) ; 
            //calculating the z -distance of current vertex 
            float z2 = vertices[j]->getAtIndexExcludingTranslate(2) ; 
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
    
