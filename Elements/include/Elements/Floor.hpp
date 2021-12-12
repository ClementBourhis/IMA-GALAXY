#pragma once

#include "Element.hpp"

class Floor : public Element {
    //---attributs de Element
    public:
        //---constructeur
        Floor(Mesh *mesh, const glm::vec3 position = glm::vec3(0.f,0.f,0.f), const glm::vec3 size = glm::vec3(1.f,1.f,1.f), const glm::vec3 rotation = glm::vec3(0.f,0.f,0.f)) : Element(mesh,position,size,rotation){
        }

        //---méthodes
        inline std::string type() const override{
            return "Floor";
        }
};