#pragma once

#include "Element.hpp"

class Skybox : public Element {
    //---attributs de Element
    public:
        //---constructeur
        Skybox(Mesh *mesh,ShaderManager *shader, Texture *texture, const glm::vec3 position = glm::vec3(0.f,0.f,0.f), const glm::vec3 size = glm::vec3(1.f,1.f,1.f), const glm::vec3 rotation = glm::vec3(0.f,0.f,0.f)) : Element(mesh, shader, texture, position, size, rotation){
        }

        //méthodes
        void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &ViewMatrix);
        
        void updatePosition(glm::vec3 posCamera){
            _position = posCamera;
        }
};