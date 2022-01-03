#pragma once

//---glimac
#include <glimac/SDLWindowManager.hpp>  //SDLWindowManager
#include <glimac/common.hpp>            //utilisation de la struct ShapeVertex pour créer nos vertex

//---Render
#include <Render/VBO.hpp>
#include <Render/IBO.hpp>
#include <Render/VAO.hpp>
#include <Render/ShaderManager.hpp>
#include <Render/Texture.hpp>


/**
 * \file Mesh.hpp
 * \brief Déclaration de la classe Mesh
 */
/**
 * \class Mesh
 * \brief permet de créer des éléments et de les dessiner avec des shaders et texture. Elle regroupe également les classes de mesh plus complexe comme la classe Cube.hpp
 */

class Mesh{
    protected :
        //---attributs
        std::vector<ShapeVertex> _vertices; /*!< conteneur des nos vertex. (à envoyer au VBO) */
        std::vector<u_int32_t> _indices;    /*!< conteneur des indices (à envoyer à l'IBO) */

        VBO *_vbo = new VBO();              /*!< objet VBO */
        IBO *_ibo = new IBO();              /*!< objet IBO */
        VAO *_vao = new VAO();              /*!< objet VAO */

        bool _isFill;                       /*!< on vérifie si le mesh à envoyer ses données */
        bool _isBind;                       /*!< on vérifie si le mesh est déjà bind */

    public :
        //---constructeurs
        Mesh() = default;
        Mesh(const std::vector<ShapeVertex> vertices);
        Mesh(const std::vector<ShapeVertex> vertices, const std::vector<u_int32_t> indices);

        //---destructeurs
        ~Mesh(){};
        /// \brief libère la mémoire en supprimant tout les objets VBO, VAO, Texture
        void free();

        //---methodes
        /// \brief bind les éléments permetant de dessiner le mesh (VAO + Texture) et d'activer le program avec les shaders
        void bind();

        /// \brief debind le vao et la texture
        void debind();

        /// \brief on met un fillBuffer pour envoyer les datas aux cibles souhaité
        void fillBuffers(); 
        
        /// \brief dessine le mesh
        void draw();

        //getters
        /// \brief on récupère le nb de vertex utilisé pour le mesh
        inline GLsizei nbVertex() const{
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

        /// \brief on créer une méthode pour vérifier qu'il existe ou non un IBO
        inline bool haveIBO() const{
            return _indices.size() > 0 ? true : false;
        }

        inline virtual std::string type() const{
            return "Mesh";
        }

        //Affichage :
        friend std::ostream &operator<<(std::ostream &os, const Mesh &mesh){
            os << "     nb vertices : "<<mesh._vertices.size()<<"\n";
            os << "     nb indices  : "<<mesh._indices.size()<<"\n";
            if(mesh._isFill){
                os << "     statut : is fill";
            }
            else{
                os << "     statut : is not fill !";
            }
            if(mesh._isBind){
                os << "     statut : is bind";
            }
            else{
                os << "     statut : is not bind !";
            }
            return os;
        }
};