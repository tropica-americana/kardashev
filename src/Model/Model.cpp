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
