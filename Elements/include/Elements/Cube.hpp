#pragma once

#include <vector>
#include <glimac/common.hpp>
#include "Vertex.hpp"

class Cube {
    private:
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices; //tableau d'indices

    public:
    // Constructeur: alloue le tableau de données et construit les attributs des vertex
    Cube(GLfloat size) {
        build(size); // Construction (voir le .cpp)
    }

    // Renvoit le pointeur vers les données
    const Vertex* getDataPointer() const {
        return &_vertices[0];
    }
    
    // Renvoit le nombre de vertex
    GLsizei getVertexCount() const {
        return _vertices.size();
    }

    // Renvoit le nombre d'indices
    GLsizei getIndexCount() const {
        return _indices.size();
    }

    // Renvoit le pointeur vers les indices
    const unsigned int* getIndexPointer() const {
        return &_indices[0];
    }

    //méthodes
    // Alloue et construit les données (implantation dans le .cpp)
    void build(GLfloat size);

    void getVerticesInfos(){
        for(int i=0; i<_vertices.size(); i++){
            std::cout << "JDGJH" << _vertices[i].position << std::endl;
        }
    };

    std::vector<Vertex> getVertices() const {
        return _vertices;
    }

    std::vector<unsigned int> getIndices() const {
        return _indices;
    }
};