#pragma once

//---Mesh
#include <Mesh/Mesh.hpp>

/**
 * \file Cube.hpp
 * \brief Déclaration de la classe Cube
 */
/**
 * \class Cube
 * \brief hérite de la classe Mesh, elle construit les vertices nécessaire pour la création d'un cube
 */

class Cube : public Mesh{
    protected :
        //on reprend les attributs qui sont déjà dans Mesh

    public :
        //---constructeurs
        Cube(); //constructeur si pas de size donné
        Cube(GLfloat size);

        //---destructeurs
        ~Cube() = default;

        //méthodes
        /// \brief remplit les vecteurs _vertices et _indices
        void build(GLfloat size);

        /// \brief retourne un string qui indique le type du mesh
        inline std::string type() const override{
            return "Cube";
        }
};