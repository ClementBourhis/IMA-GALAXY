#include <Render/VAO.hpp>

VAO::VAO() : Render() {
    glGenVertexArrays(1, &_id);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &_id);
}

void VAO::bind() const{
    glBindVertexArray(_id);
}

void VAO::debind() const{
    glBindVertexArray(0);
}