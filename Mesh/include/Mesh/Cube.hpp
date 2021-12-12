#pragma once

//---Mesh
#include <Mesh/Mesh.hpp>

//Classe cube qui hérite de la classe Mesh parce que c'est un mesh plus complexe
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
};