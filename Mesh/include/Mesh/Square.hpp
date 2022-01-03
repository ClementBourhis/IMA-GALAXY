#pragma once

//Mesh
#include "Mesh.hpp"

/**
 * \file Square.hpp
 * \brief Déclaration de la classe Square
 */
/**
 * \class Square
 * \brief Hérite de la classe Mesh, c'est un quad créé avec deux triangles
 */

class Square : public Mesh{
    //récupère les attributs de Mesh
    private :
        //---méthodes
        /// \brief construit les vertex et les envoies dans le conteneur _vertices du Mesh
        void build(float size);

    public:
        //---constructeurs
        Square(float size = 1.f);

        inline std::string type() const override{
            return "Square";
        }
};