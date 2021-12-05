#pragma once

#include <GL/glew.h>
#include "glm.hpp"

namespace glimac {

struct ShapeVertex {
    ShapeVertex();
    ShapeVertex(const glm::vec3 &_position, const glm::vec3 &_normal, const glm::vec2 &_texCoords) 
        : position(_position), normal(_normal), texCoords(_texCoords){
    }

    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

}
