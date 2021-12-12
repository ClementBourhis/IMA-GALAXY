#include <Elements/Element.hpp>

Element::Element(Mesh *mesh, ShaderManager* shader, Texture* texture, glm::vec3 position, glm::vec3 size, glm::vec3 rotation)
    :_mesh(mesh), _shader(shader), _texture(texture), _position(position), _size(size), _rotation(rotation){
    _shader->addUniformVariable("uMVPMatrix");
    _shader->addUniformVariable("uMVMatrix");
    _shader->addUniformVariable("uNormalMatrix");
    _shader->addUniformVariable("uTexture");
}

Element::~Element(){
    _mesh->free();
    _texture->free();
}

void Element::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &ViewMatrix){
    //on bind les datas
    _mesh->bind();
    _shader->use();
    _texture->bind();

    _shader->sendUniformMatrix4("uMVPMatrix", ProjMatrix * ViewMatrix * MVMatrix());
    _shader->sendUniformMatrix4("uMVMatrix", ViewMatrix * MVMatrix());
    _shader->sendUniformMatrix4("uNormalMatrix", (glm::transpose(glm::inverse(MVMatrix()))));
    _shader->sendUniformInt("uTexture", 0);

    _mesh->draw();

    //debind les datas
    _texture->debind();
    _mesh->debind();
}

glm::mat4 Element::MVMatrix() const{
    glm::mat4 MVMatrix = glm::translate(glm::mat4(1.f), _position);
    MVMatrix = glm::rotate(MVMatrix, _rotation.x, glm::vec3(1.f, 0.f, 0.f));
    MVMatrix = glm::rotate(MVMatrix, _rotation.y, glm::vec3(0.f, 1.f, 0.f));
    MVMatrix = glm::rotate(MVMatrix, _rotation.z, glm::vec3(0.f, 0.f, 1.f));
    MVMatrix = glm::scale(MVMatrix, _size);
    return MVMatrix;
}