#pragma once

#include "Render.hpp"

/**
 * \file IBO.hpp
 * \brief Déclaration de la classe IBO
 */
/**
 * \class IBO
 * \brief La classe IBO est sensiblement la même que la classe VBO. Elle permet de créer des objets IBO et de les manipuler plus simplement
 */

class IBO : public Render { 
    //---attribut de Render
    public :
        //---constructeurs-/-destructeur
        IBO();
        ~IBO();

        //---méthodes
        void bind() const;
        void debind() const;

        template <typename type>
        void fillBuffer(const std::vector<type> &vec){
            bind();
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, vec.size()*sizeof(type), vec.data(), GL_STATIC_DRAW);
            debind();
        }
};