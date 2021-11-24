#pragma once

#include <GL/glew.h>
#include <vector>

#include "Render.hpp"

class VBO : public Render {
    //attribut de Render
    public :
        //constructeurs-/-destructeur
        VBO();
        ~VBO();

        //méthodes
        void bind() const;
        void debind() const;

        template <typename type>
        void fillBuffer(const std::vector<type> &vec){
            bind();
            glBufferData(GL_ARRAY_BUFFER, vec.size()*sizeof, vec.data(), GL_STATIC_DRAW);
        }
};