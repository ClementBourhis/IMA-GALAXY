#pragma once

//STL
#include <iostream>             //std::cerr
#include <stdexcept>            //std::error...
#include <vector>               //std::vector<T>
#include <string>               //std::string

//GL
#include <GL/glew.h>            //GLuint

//glimac
#include <glimac/FilePath.hpp>  //FilePath
#include <glimac/Image.hpp>     //loadImage

using namespace glimac; //utilisation de la lib glimac


/**
 * \file Texture.hpp
 * \brief Déclaration de la classe Texture
 */
/**
 * \class Texture
 * \brief Permet de créer des objets textures plus simplement
 */

class Texture {
    private :
        //---attributs
        GLuint _id;                         /*!< id de l'objet texture */
        FilePath _path;                     /*!< chemin de l'image utilisé */
        std::unique_ptr<Image> _image;      /*!< pointeur vers l'image */

    public :
        //---constructeur-/-destructeur
        Texture() = default;
        Texture(FilePath path);
        ~Texture(){};

        /// \brief destructeur qui supprime l'objet texture
        void free();                        


        //---méthodes
        /// \brief bind l'objet texture
        void bind();                        

        /// \brief debind l'objet texture
        void debind();                      

        /// \brief charge l'une image /!\ à ne pas confondre avec la fct loadImage() qui existe déjà dans la lib glimac/Image.hpp
        void loadTexture();                  
        

        /// \brief retourne l'id
        GLuint getId();              

        /// \brief retourne le pointeur ver l'image       
        std::unique_ptr<Image> getImage(); 

        //Affichage :
        friend std::ostream &operator<<(std::ostream &os, const Texture &texture){
            os << "     image : " << texture._path << "\n";
            return os;
        }
};