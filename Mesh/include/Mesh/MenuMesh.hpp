#pragma once

//Mesh
#include "Mesh.hpp"

//Hérite de la classe Mesh, c'est un quad créé avec deux triangles
class MenuMesh : public Mesh{
    //récupère les attributs de Mesh
    private :
        //---méthodes
        void build(float size); //construit les vertex et les envoies dans le conteneur _vertices du Mesh

    public:
        //---constructeurs
        MenuMesh(float size = 2.f);

        inline std::string type() const override{
            return "MenuMesh";
        }
};