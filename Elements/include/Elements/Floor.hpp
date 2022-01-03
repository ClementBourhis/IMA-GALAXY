#pragma once

#include "Element.hpp"


/**
 * \file Floor.hpp
 * \brief Déclaration de la classe Floor
 */
/**
 * \class Floor
 * \brief permet de spécifier à l'élément qu'il s'agit d'un floor, et au besoin de lui donner des méthodes spécifiques
 */

class Floor : public Element {
    //---attributs de Element
    public:
        //---constructeur
        Floor(Mesh *mesh,ShaderManager *shader, Texture *texture, const glm::vec3 position = glm::vec3(0.f,0.f,0.f), const glm::vec3 size = glm::vec3(1.f,1.f,1.f), const glm::vec3 rotation = glm::vec3(0.f,0.f,0.f)) : Element(mesh, shader, texture, position,size,rotation){
        }

        //---méthodes
        inline std::string type() const override {
            return "Floor";
        }
};