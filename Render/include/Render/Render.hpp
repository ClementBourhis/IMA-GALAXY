#pragma once

//STL
#include <vector>       //std::vector<type>

//GL
#include <GL/glew.h>    //GLuint

/**
 * \file Render.hpp
 * \brief Déclaration de la classe Render
 */
/**
 * \class Render
 * \brief regroupe les classes VBO VAO IBO. Permet la création de ces objets et de les manipuler plus aisement
 */

class Render {

    protected :
        //---attributs
        GLuint _id;

    public :
        //---constructeur
        Render() = default;

        //---destructeur
        ~Render() = default;

        //---méthodes
        /// \brief retourne l'adresse de l'objet (getter)
        const GLuint& getId() const;                

        /// \brief retourne l'adresse de l'objet et peut modifier sa valeur (setter)
        GLuint& getId();                            
                                
                        
        /// \brief bind l'objet
        void bind();                                

        /// \brief debind l'objet
        void debind();                              
        
        /// \brief remplit les datas de l'objet
        template <typename type>
        void fillBuffer(std::vector<type> &vec){}; 
};