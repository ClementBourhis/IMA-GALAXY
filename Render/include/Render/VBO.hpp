#pragma once

#include "Render.hpp"

/**
 * \file VBO.hpp
 * \brief Déclaration de la classe VBO
 */
/**
 * \class VBO
 * \brief permet de créer des objets VBO et de les manipuler plus simplement. Hérite de la classe Render
 */

class VBO : public Render {
    //---attribut de Render
    public :
        //---constructeurs-/-destructeur
        VBO();
        ~VBO();

        //---méthodes
        void bind() const;  //bind le VBO
        void debind() const;//debind le VBO

        //Remplissage du VBO
        template <typename type>
        void fillBuffer(const std::vector<type> &vec){
            bind();
            glBufferData(GL_ARRAY_BUFFER, vec.size()*sizeof(type), vec.data(), GL_STATIC_DRAW);
            debind();
        }
};