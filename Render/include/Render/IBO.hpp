#pragma once

#include <GL/glew.h>
#include <vector>

#include "Render.hpp"

//La classe IBO est sensiblement la même que la classe VBO

class IBO : public Render { 
    //attribut de Render
    public :
        //constructeurs-/-destructeur
        IBO();
        ~IBO();

        //méthodes
        void bind() const;
        void debind() const;

        template <typename type>
        void fillBuffer(const std::vector<type> &vec){
            bind();
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, vec.size()*sizeof(type), vec.data(), GL_STATIC_DRAW);
        }
};