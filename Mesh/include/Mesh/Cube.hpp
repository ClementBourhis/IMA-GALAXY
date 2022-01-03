#pragma once

//---Mesh
#include <Mesh/Mesh.hpp>

//Classe cube hérite de la classe Mesh, elle construit les vertices nécessaire pour la création d'un cube
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
        void build(GLfloat size); //remplit les vecteurs _vertices et _indices

        inline std::string type() const override{
            return "Cube";
        }
};