#include <Render/VBO.hpp>

void VBO::bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}