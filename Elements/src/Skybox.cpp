#include <Elements/Skybox.hpp>

void Skybox::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &ViewMatrix){
    //on bind les datas
    _mesh->bind();
    _shader->use();
    _texture->bind();

    _shader->sendUniformMatrix4("uMVPMatrix", ProjMatrix * ViewMatrix * MVMatrix());
    _shader->sendUniformMatrix4("uMVMatrix", ViewMatrix * MVMatrix());
    _shader->sendUniformMatrix4("uNormalMatrix", (glm::transpose(glm::inverse(MVMatrix()))));
    _shader->sendUniformInt("uTexture", 0);
    
    glDepthMask(GL_FALSE); //on désactive la profondeur pour que la skybox passse derrière
    _mesh->draw();
    glDepthMask(GL_TRUE);

    //debind les datas
    _texture->debind();
    _mesh->debind();
}