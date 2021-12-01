#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <GL/glew.h>

#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>

using namespace glimac; //utilisation de la lib glimac

//La classe texture permet de créer des objets textures plus simplement
class Texture {
    private :
        //---attributs
        GLuint _id;                         //id de l'objet texture
        FilePath _path;                     //chemin de l'image utilisé
        std::unique_ptr<Image> _image;      //pointeur vers l'image

    public :
        //---constructeur-/-destructeur
        Texture() = default;
        Texture(FilePath path);
        ~Texture();

        //---méthodes
        void bind();                        //bind l'objet texture
        void debind();                      //debind l'objet texture

        void loadTexture();                  //charge l'une image /!\ à ne pas confondre avec la fct loadImage() qui existe déjà dans la lib glimac/Image.hpp
        
        GLuint getId();                     //retourne l'id
        std::unique_ptr<Image> getImage();  //retourne le pointeur ver l'image
};