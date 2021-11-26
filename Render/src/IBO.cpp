#include <Render/IBO.hpp>

IBO::IBO() : Render() {
    glGenBuffers(1, &_id);
}

IBO::~IBO() {
    glDeleteBuffers(1, &_id);
}

void IBO::bind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
}

void IBO::debind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}