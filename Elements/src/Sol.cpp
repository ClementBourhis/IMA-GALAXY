#include <cmath>
#include <vector>
#include <iostream>
#include <glimac/common.hpp>
#include <Elements/Sol.hpp>

void Sol::build(GLfloat size) {
    //On remplit nos vertex
    _vertices.push_back(Vertex(glm::vec3(-0.5*size, 0, -0.5*size),glm::vec3(0, 1, 0), glm::vec2(0, 1))); // Sommet 0
    _vertices.push_back(Vertex(glm::vec3(-0.5*size, 0, 0.5*size),glm::vec3(0, 1, 0), glm::vec2(0, 0))); // Sommet 1
    _vertices.push_back(Vertex(glm::vec3(0.5*size, 0, 0.5*size),glm::vec3(0, 1, 0), glm::vec2(1, 0))); // Sommet 2
    _vertices.push_back(Vertex(glm::vec3(0.5*size, 0, -0.5*size),glm::vec3(0, 1, 0), glm::vec2(1, 1))); // Sommet 3

    //on remplit nos indices
    _indices = {0, 1, 2, 0, 2, 3};
}