#include <Elements/Element.hpp>

Element::Element(Mesh *mesh, ShaderManager* shader, Texture* texture, glm::vec3 position, glm::vec3 size, glm::vec3 rotation)
    :_mesh(mesh), _shader(shader), _texture(texture), _position(position), _size(size), _rotation(glm::vec3(glm::radians(rotation.x),glm::radians(rotation.y),glm::radians(rotation.z))){
}

void Element::addListOfPosition(std::vector<glm::vec3> listOfPosition){
    _listOfPosition = listOfPosition;
}

Element::~Element(){
    _mesh->free();
    _texture->free();
}

void Element::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &ViewMatrix, bool depthMask, bool position2D){
    //on bind les datas
    _mesh->bind();
    _shader->use();
    _texture->bind();

    if(_listOfPosition.size() > 0){
        for(const auto &position : _listOfPosition){
            bool blacklisted = false;
            for(const auto &it : _blackList){
                if(position == it){
                    blacklisted = true;
                }
            }
            if(!blacklisted){
                if(position2D){
                    update2DPosition(position);
                }
                else{
                    updatePosition(position);
                }

                _shader->sendUniformMatrix4("uMVPMatrix", ProjMatrix * ViewMatrix * MVMatrix());
                _shader->sendUniformMatrix4("uMVMatrix", ViewMatrix * MVMatrix());
                _shader->sendUniformMatrix4("uNormalMatrix", (glm::transpose(glm::inverse(MVMatrix()))));
                _shader->sendUniformInt("uTexture", 0);

                //on désactive le gldepthmask (utile pour la skybox)
                if(!depthMask){
                    glDepthMask(GL_FALSE); 
                }

                _mesh->draw();

                if(!depthMask){
                    glDepthMask(GL_TRUE); 
                }
            }
        }
    }

    else{
        _shader->sendUniformMatrix4("uMVPMatrix", ProjMatrix * ViewMatrix * MVMatrix());
        _shader->sendUniformMatrix4("uMVMatrix", ViewMatrix * MVMatrix());
        _shader->sendUniformMatrix4("uNormalMatrix", (glm::transpose(glm::inverse(MVMatrix()))));
        _shader->sendUniformInt("uTexture", 0);

        //on désactive le gldepthmask (utile pour la skybox)
        if(!depthMask){
        glDepthMask(GL_FALSE); 
        }

        _mesh->draw();

        if(!depthMask){
        glDepthMask(GL_TRUE); 
        }
    }

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