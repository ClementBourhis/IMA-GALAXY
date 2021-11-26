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