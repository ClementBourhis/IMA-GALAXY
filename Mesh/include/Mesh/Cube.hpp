#pragma once

//---external libs
#include <GL/glew.h>
#include <iostream>
#include <string>

//---glimac
#include <glimac/SDLWindowManager.hpp>
#include <glimac/common.hpp> //utilisation de la struct ShapeVertex pour créer nos vertex

//---Render
#include <Render/VBO.hpp>
#include <Render/IBO.hpp>
#include <Render/VAO.hpp>
#include <Render/ShaderManager.hpp>
#include <Render/Texture.hpp>

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
        Cube(GLfloat size, ShaderManager* shader, Texture* texture);

        //---destructeurs
        ~Cube() = default;

        //méthodes
        void build(GLfloat size); //remplit les vecteurs _vertices et _indices
};