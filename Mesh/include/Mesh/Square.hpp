#pragma once

#include "Mesh.hpp"

//un sol pour le parcours, c'est un quad carré
class Square : public Mesh{
    //récupère les attributs de Mesh
    private :
        //---méthodes
        void build(float size);

    public:
    //---constructeurs
    Square(float size);
    Square(float size, ShaderManager* shader, Texture* texture);
};