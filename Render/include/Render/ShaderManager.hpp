#pragma once

#include <string>
#include <map>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>

//Le ShaderManager permet de simplifier l'utilisation des shaders qui peuvent etre différents par meshs
class ShaderManager {
    private :
        //---attributs
        glimac::Program _program;
        glimac::FilePath _vsFile;
        glimac::FilePath _fsFile;
        std::map<std::string, GLint> _uVariables;

    public :
        //---constructeur-/-destructeur
        ShaderManager() = default;
        ShaderManager(const glimac::FilePath &vsFile, const glimac::FilePath &fsFile);
        ~ShaderManager() = default;

        //---méthodes
        void addUniformVariable(const std::string &name);

        void sendUniformMatrix4(std::string name, glm::mat4 value);
        void sendUniformVector3(std::string name, glm::vec3 value);
        void sendUniformInt(std::string name, int num); //use to send begin of texture

        void use();

        //peut etre appelé régulièrement quand on veut activer une texture (ex _program.use()) on le met donc en inline pour être plus optimisé
        inline GLuint getId() const{
            return _program.getGLId();
        }
};