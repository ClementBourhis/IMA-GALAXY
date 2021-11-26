#include <Render/VBO.hpp>

VBO::VBO() : Render() {
    glGenBuffers(1, &_id);
}

VBO::~VBO() {
    glDeleteBuffers(1, &_id);
}

void VBO::bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void VBO::debind() const{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}