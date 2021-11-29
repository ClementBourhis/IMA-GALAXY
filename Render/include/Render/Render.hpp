#pragma once

#include <GL/glew.h>
#include <vector>

//La classe render regroupe les classes VBO/VAO/IBO
//elle permet la création de ces objets et de les manipuler plus aisement  
class Render {

    protected :
        //---attributs
        GLuint _id;

    public :
        //---constructeurs-/-destructeur
        Render() = default;
        ~Render() = default;

        //---méthodes
        const GLuint& getId() const; //retourne l'adresse de l'objet (getter)
        GLuint& getId();             //retourne l'adresse de l'objet et peut modifier sa valeur (setter)
        

        void bind();
        void debind();
        
        template <typename type>
        void fillBuffer(std::vector<type> &vec){};
};