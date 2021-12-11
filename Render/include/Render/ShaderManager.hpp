#pragma once

//STL
#include <string>               //std::string
#include <map>                  //std::map<T,T>

//glimac
#include <glimac/Program.hpp>   //Program
#include <glimac/FilePath.hpp>  //FilePath
#include <glimac/glm.hpp>       //glm::mat4, glm::vec3

//Le ShaderManager permet de simplifier l'utilisation des shaders qui peuvent etre différents par meshs
class ShaderManager {
    private :
        //---attributs
        glimac::Program _program;                   //relie les shader
        glimac::FilePath _vsFile;                   //chemin du Vertex shader
        glimac::FilePath _fsFile;                   //chemin du Fragment shader
        std::map<std::string, GLint> _uVariables;   //Conteneur stockant les variables uniforme

    public :
        //---constructeur-/-destructeur
        ShaderManager() = default;
        ShaderManager(const glimac::FilePath &vsFile, const glimac::FilePath &fsFile);
        ~ShaderManager() = default;

        //---méthodes
        void addUniformVariable(const std::string &name);           //ajoute une variable uniforme dans _uVariable

        void sendUniformMatrix4(std::string name, glm::mat4 value); //envoie une matrices4*4 a une variable uniforme
        void sendUniformVector3(std::string name, glm::vec3 value); //envoie une vector*3 a une variable uniforme
        void sendUniformInt(std::string name, int num);             //use to send begin of texture

        void use();                                                 //use program

        //peut etre appelé régulièrement quand on veut activer une texture (ex _program.use()) on le met donc en inline pour être plus optimisé
        inline GLuint getId() const{
            return _program.getGLId();
        }
};