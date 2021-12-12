#include <Elements/Element.hpp>

Element::Element(Mesh *mesh, glm::vec3 position, glm::vec3 size, glm::vec3 rotation)
    :_mesh(mesh), _position(position), _size(size), _rotation(rotation){
}

Element::~Element(){
    _mesh->free();
}

void Element::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &ViewMatrix, const bool isBind){
    if(!isBind){
        _mesh->bind();
    }
    _mesh->draw(ProjMatrix, MVMatrix(), ViewMatrix);
    if(!isBind){
        _mesh->debind();
    }
}

glm::mat4 Element::MVMatrix() const{
    glm::mat4 MVMatrix = glm::translate(glm::mat4(1.f), _position);
    MVMatrix = glm::rotate(MVMatrix, _rotation.x, glm::vec3(1.f, 0.f, 0.f));
    MVMatrix = glm::rotate(MVMatrix, _rotation.y, glm::vec3(0.f, 1.f, 0.f));
    MVMatrix = glm::rotate(MVMatrix, _rotation.z, glm::vec3(0.f, 0.f, 1.f));
    MVMatrix = glm::scale(MVMatrix, _size);
    return MVMatrix;
}