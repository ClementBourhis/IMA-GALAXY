#pragma once

//Mesh
#include "Mesh.hpp"

//Hérite de la classe Mesh, c'est un quad créé avec deux triangles
class Square : public Mesh{
    //récupère les attributs de Mesh
    private :
        //---méthodes
        void build(float size); //construit les vertex et les envoies dans le conteneur _vertices du Mesh

    public:
        //---constructeurs
        Square(float size = 1.f);
};