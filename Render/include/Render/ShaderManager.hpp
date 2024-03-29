#pragma once

//STL
#include <string>               //std::string
#include <map>                  //std::map<T,T>

//glimac
#include <glimac/Program.hpp>   //Program
#include <glimac/FilePath.hpp>  //FilePath
#include <glimac/glm.hpp>       //glm::mat4, glm::vec3


/**
 * \file ShaderManager.hpp
 * \brief Déclaration de la classe ShaderManager
 */
/**
 * \class ShaderManager
 * \brief permet de simplifier l'utilisation des shaders qui peuvent etre différents par meshs
 */

class ShaderManager {
    private :
        //---attributs
        glimac::Program _program;                   /*!< relie les shader */
        glimac::FilePath _vsFile;                   /*!< chemin du Vertex shader */
        glimac::FilePath _fsFile;                   /*!< chemin du Fragment shader */
        std::map<std::string, GLint> _uVariables;   /*!< Conteneur stockant les variables uniforme */

    public :
        //---constructeur-/-destructeur
        ShaderManager() = default;
        ShaderManager(const glimac::FilePath &vsFile, const glimac::FilePath &fsFile);
        ~ShaderManager() = default;

        //---méthodes
        /// \brief ajoute une variable uniforme dans _uVariable
        void addUniformVariable(const std::string &name);           


        /// \brief envoie une matrices4*4 a une variable uniforme
        void sendUniformMatrix4(std::string name, glm::mat4 value); 

        /// \brief envoie une vector*3 a une variable uniforme
        void sendUniformVector3(std::string name, glm::vec3 value); 

        /// \brief use to send begin of texture
        void sendUniformInt(std::string name, int num);             


        /// \brief use program
        void use();                                                 


        /// \brief peut etre appelé régulièrement quand on veut activer une texture (ex _program.use()) on le met donc en inline pour être plus optimisé
        inline GLuint getId() const{
            return _program.getGLId();
        }

        //Affichage :
        friend std::ostream &operator<<(std::ostream &os, const ShaderManager &shader){
            os << "     vs file : " << shader._vsFile << "\n";
            os << "     fs file : " << shader._fsFile << "\n";
            if(shader._uVariables.size() != 0){
                os << "     uniform variables :\n";
                int i = 0;
                for(const auto &it : shader._uVariables){
                    os << "     ["<< i <<"] : "<< it.first << " | " << it.second << "\n";
                    i++;
                }
            }
            else{
                os << "     uniform variables : empty\n";
            }
            return os;
        }
};