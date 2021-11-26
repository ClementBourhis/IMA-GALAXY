#pragma once

#include <GL/gl.h>

//à voir si utile
class Render {

    protected :
        //attributs
        GLuint _id;

    public :
        //constructeurs-/-destructeur
        Render() = default;
        ~Render() = default;

        //méthodes
        const GLuint& getId() const; //retourne l'adresse de l'objet (getter)
        GLuint& getId();             //retourne l'adresse de l'objet et peut modifier sa valeur (setter)
};