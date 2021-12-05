#pragma once

//---external libs
#include <GL/glew.h>
#include <iostream>
#include <string>

//---glimac
#include <glimac/SDLWindowManager.hpp>
#include <glimac/common.hpp> //utilisation de la struct ShapeVertex pour créer nos vertex

//---Render
#include <Render/VBO.hpp>
#include <Render/IBO.hpp>
#include <Render/VAO.hpp>
#include <Render/ShaderManager.hpp>
#include <Render/Texture.hpp>

//La classe Mesh permet de créer des éléments et de les dessiner avec des shaders et texture
//Elle regroupe également les classes de mesh plus complexe comme la classe Cube.hpp
class Mesh{
    protected :
        //---attributs
        std::vector<ShapeVertex> _vertices; //conteneur des nos vertex. (à envoyer au VBO)
        std::vector<u_int32_t> _indices;    //conteneur des indices (à envoyer à l'IBO)

        VBO *_vbo = new VBO();
        IBO *_ibo = new IBO();
        VAO *_vao = new VAO();

        ShaderManager *_shader; //création d'un program(vs+fs) spécifique au mesh
        Texture *_texture;

    public :
        //---constructeurs
        Mesh() = default;
        Mesh(const std::vector<ShapeVertex> vertices);
        Mesh(const std::vector<ShapeVertex> vertices, ShaderManager* shader);
        Mesh(const std::vector<ShapeVertex> vertices, ShaderManager* shader, Texture* texture);
        Mesh(const std::vector<ShapeVertex> vertices, const std::vector<u_int32_t> indices);
        Mesh(const std::vector<ShapeVertex> vertices, const std::vector<u_int32_t> indices, ShaderManager* shader);
        Mesh(const std::vector<ShapeVertex> vertices, const std::vector<u_int32_t> indices, ShaderManager* shader, Texture* texture);

        //---destructeurs
        ~Mesh(){};
        void free();

        //---methodes
        void bind();            //bind les éléments permetant de dessiner le mesh (VAO + Texture) et d'activer le program avec les shaders
        void debind();          //debind le vao et la texture
        void fillBuffers();     //on met un fillBuffer pour envoyer les datas aux cibles souhaité

        void draw();
        void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MWMatrix, const glm::mat4 &ViewMatrix);

        //getters
        inline GLsizei nbVertex() const{  //on récupère le nb de vertex utilisé pour le mesh
            return _vertices.size();
        }

        inline std::vector<ShapeVertex> vertices() const{
            return _vertices;
        }

        inline std::vector<u_int32_t> indices() const{
            return _indices;
        }

        inline VBO *vbo() const{
            return _vbo;
        }
        
        inline IBO *ibo() const{
            return _ibo;
        }

        inline VAO *vao() const{
            return _vao;
        }

        inline ShaderManager *shader()const{
            return _shader;
        }

        inline Texture *texture() const{
            return _texture;
        }

        inline bool haveIBO() const{   //on créer une méthode pour vérifier qu'il existe ou non un IBO
            return _indices.size() > 0 ? true : false;
        }
};