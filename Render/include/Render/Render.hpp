#pragma once

//STL
#include <vector>       //std::vector<type>

//GL
#include <GL/glew.h>    //GLuint

//La classe render regroupe les classes VBO/VAO/IBO
//elle permet la création de ces objets et de les manipuler plus aisement  
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
        const GLuint& getId() const;                //retourne l'adresse de l'objet (getter)
        GLuint& getId();                            //retourne l'adresse de l'objet et peut modifier sa valeur (setter)
                                
                        
        void bind();                                //bind l'objet
        void debind();                              //debind l'objet
        
        template <typename type>
        void fillBuffer(std::vector<type> &vec){};  //remplit les datas de l'objet
};