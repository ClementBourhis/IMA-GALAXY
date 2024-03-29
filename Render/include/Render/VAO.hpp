#pragma once

#include "Render.hpp"
#include "VBO.hpp"
#include "IBO.hpp"

/**
 * \file VAO.hpp
 * \brief Déclaration de la classe VAO
 */
/**
 * \class VAO
 * \brief permet de créer des objets VAO et de les manipuler plus simplement. Elle utilise les classe VBO et IBO pour envoyer les informations au shader
 */

class VAO : public Render {
    //---attribut de Render
    public :
        //---constructeurs-/-destructeur
        VAO();
        ~VAO();

        //---méthodes
        /// \brief bind le VAO
        void bind() const;  

        /// \brief debind le VAO
        void debind() const;

        /// \brief Remplissage du VAO
        template <typename type>
        void fillBuffer(const std::vector<type> &vec,  const VBO* vbo, const IBO* ibo = nullptr){
            //on bind tout
            bind();
            vbo->bind();
            //si on utilise un IBO on le bind pour l'utiliser
            if(ibo != nullptr){
                ibo->bind();
            }


            //on active les attributs des vertex (a faire correspondre avec les shaders)
            const GLuint VERTEX_ATTR_POSITION = 0;  //coordonées position
            const GLuint VERTEX_ATTR_NORMAL = 1;    //vecteur normale
            const GLuint VERTEX_ATTR_TEXTURE = 2;   //coordonées texture

            glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
            glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
            glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);


            //on envoie les infos du VBO au shader
            glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(type), (const GLvoid*) (offsetof(type, position)));
            glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(type), (const GLvoid*) (offsetof(type, normal)));
            glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(type), (const GLvoid*) (offsetof(type, texCoords)));

            vbo->debind();
            debind();
        }
};