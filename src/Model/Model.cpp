#include "Model.h"


Model::~Model() {
    for (Vertex * vertex : vertices) {
        delete vertex; 
    }
}
void Model::renderMyself(SDL_Renderer* renderer) {
    if (vertices.size() < 2) {
        // Not enough vertices to draw lines
        return;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (size_t i = 0; i < vertices.size() - 1; i++) {
        SDL_RenderDrawLine(renderer, (*vertices.at(i))[0], (*vertices.at(i))[1],
                           (*vertices.at(i + 1))[0], (*vertices.at(i + 1))[1]);
    }
    // Connect the last vertex to the first
    SDL_RenderDrawLine(renderer, (*vertices.at(0))[0], (*vertices.at(0))[1],
                       (*vertices.at(vertices.size() - 1))[0],
                       (*vertices.at(vertices.size() - 1))[1]);
}

void Model::translate(const glm::vec3& vec3) {
    for (Vertex * vertex : vertices) {
        vertex->translate(vec3);
    }
}

void Model::rotate(const glm::vec3& orientationVec3) {
    for (Vertex * vertex : vertices) {
        vertex->rotateVertex(orientationVec3);
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
        std::vector <std::tuple <int index , float distance >> focusedVertexDistanceFromVerticesMemberTupleVector  ; 

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
        std::sort (focusedVertexDistanceFromVerticesMemberTupleVector.begin(),focusedVertexDistanceFromVerticesMemberTupleVector.end() , [](auto const & v1, auto const & v2) {
            return std::get<1>(v1) < std::get<1>(v2);
        }) ; 
        for (int z = 0; z < 4 ; z++){
            Mesh.push_back(make_tuple( i , std::get<0>focusedVertexDistanceFromVerticesMemberTupleVector[z] ))
        }


    }
    return ; 
            
        }
    
