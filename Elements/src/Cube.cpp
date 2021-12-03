#include <cmath>
#include <vector>
#include <iostream>
#include <glimac/common.hpp>
#include <Elements/Cube.hpp>

void Cube::build(GLfloat size) {

    //bottom
    _vertices.push_back(Vertex(glm::vec3(-0.5*size, -0.5*size, -0.5*size),glm::vec3(0, -1, 0), glm::vec2(0, 1))); // Sommet 0
    _vertices.push_back(Vertex(glm::vec3(-0.5*size, -0.5*size, 0.5*size),glm::vec3(0, -1, 0), glm::vec2(0, 0))); // Sommet 1
    _vertices.push_back(Vertex(glm::vec3(0.5*size, -0.5*size, 0.5*size),glm::vec3(0, -1, 0), glm::vec2(1, 0))); // Sommet 2
    _vertices.push_back(Vertex(glm::vec3(0.5*size, -0.5*size, -0.5*size),glm::vec3(0, -1, 0), glm::vec2(1, 1))); // Sommet 3
    //top
    _vertices.push_back(Vertex(glm::vec3(-0.5*size, 0.5*size, -0.5*size),glm::vec3(0, 1, 0), glm::vec2(0, 1))); // Sommet 4
    _vertices.push_back(Vertex(glm::vec3(-0.5*size, 0.5*size, 0.5*size),glm::vec3(0, 1, 0), glm::vec2(0, 0))); // Sommet 5
    _vertices.push_back(Vertex(glm::vec3(0.5*size, 0.5*size, 0.5*size),glm::vec3(0, 1, 0), glm::vec2(1, 0))); // Sommet 6
    _vertices.push_back(Vertex(glm::vec3(0.5*size, 0.5*size, -0.5*size),glm::vec3(0, 1, 0), glm::vec2(1, 1))); // Sommet 7
    //front
    _vertices.push_back(Vertex(glm::vec3(-0.5*size, -0.5*size, -0.5*size),glm::vec3(0, 0, -1), glm::vec2(0, 1))); // Sommet 0
    _vertices.push_back(Vertex(glm::vec3(-0.5*size, 0.5*size, -0.5*size),glm::vec3(0, 0, -1), glm::vec2(0, 0))); // Sommet 4
    _vertices.push_back(Vertex(glm::vec3(0.5*size, 0.5*size, -0.5*size),glm::vec3(0, 0, -1), glm::vec2(1, 0))); // Sommet 7
    _vertices.push_back(Vertex(glm::vec3(0.5*size, -0.5*size, -0.5*size),glm::vec3(0, 0, -1), glm::vec2(1, 1))); // Sommet 3
    //left
    _vertices.push_back(Vertex(glm::vec3(-0.5*size, -0.5*size, 0.5*size),glm::vec3(-1, 0, 0), glm::vec2(0, 1))); // Sommet 1
    _vertices.push_back(Vertex(glm::vec3(-0.5*size, 0.5*size, 0.5*size),glm::vec3(-1, 0, 0), glm::vec2(0, 0))); // Sommet 5
    _vertices.push_back(Vertex(glm::vec3(-0.5*size, 0.5*size, -0.5*size),glm::vec3(-1, 0, 0), glm::vec2(1, 0))); // Sommet 4
    _vertices.push_back(Vertex(glm::vec3(-0.5*size, -0.5*size, -0.5*size),glm::vec3(-1, 0, 0), glm::vec2(1, 1))); // Sommet 0
    //back
    _vertices.push_back(Vertex(glm::vec3(0.5*size, -0.5*size, 0.5*size),glm::vec3(0, 0, 1), glm::vec2(0, 1))); // Sommet 2
    _vertices.push_back(Vertex(glm::vec3(0.5*size, 0.5*size, 0.5*size),glm::vec3(0, 0, 1), glm::vec2(0, 0))); // Sommet 6
    _vertices.push_back(Vertex(glm::vec3(-0.5*size, 0.5*size, 0.5*size),glm::vec3(0, 0, 1), glm::vec2(1, 0))); // Sommet 5
    _vertices.push_back(Vertex(glm::vec3(-0.5*size, -0.5*size, 0.5*size),glm::vec3(0, 0, 1), glm::vec2(1, 1))); // Sommet 1
    //right
    _vertices.push_back(Vertex(glm::vec3(0.5*size, -0.5*size, -0.5*size),glm::vec3(1, 0, 0), glm::vec2(0, 1))); // Sommet 3
    _vertices.push_back(Vertex(glm::vec3(0.5*size, 0.5*size, -0.5*size),glm::vec3(1, 0, 0), glm::vec2(0, 0))); // Sommet 7
    _vertices.push_back(Vertex(glm::vec3(0.5*size, 0.5*size, 0.5*size),glm::vec3(1, 0, 0), glm::vec2(1, 0))); // Sommet 6
    _vertices.push_back(Vertex(glm::vec3(0.5*size, -0.5*size, 0.5*size),glm::vec3(1, 0, 0), glm::vec2(1, 1))); // Sommet 2


    _indices = {
    //bottom
        0, 1, 2, 0, 2, 3,
    //top
        4, 5, 6, 4, 6, 7,
    //front
        8, 9, 10, 8, 10, 11,
    //left
        12, 13, 14, 12, 14, 15,
    //back
        16, 17, 18, 16, 18, 19,
    //right
        20, 21, 22, 20, 22, 23,
    }; 
}