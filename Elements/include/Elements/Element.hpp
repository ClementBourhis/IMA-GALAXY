#pragma once

//STL
#include <string>           //std::string
#include <iostream>         //std::ostream

//glimac
#include <glimac/glm.hpp>   //glm::vec3, glm::mat4, glm::translate, glm::rotate, glm::scale

//Render
#include <Render/ShaderManager.hpp>
#include <Render/Texture.hpp>

//Mesh
#include <Mesh/Mesh.hpp>

//La classe Elements rassemble tous les elements constituant le jeux (sol, personnage, pièce...)
class Element{
    protected :
        //---attributs
        Mesh* _mesh;            //permet que l'élément ai une représentation physique basé sur un mesh
        glm::vec3 _position;    //position de l'element dans la scène
        glm::vec3 _size;        //défini la taille de l'élément
        glm::vec3 _rotation;    //défini la rotation de l'élément
        ShaderManager *_shader; //Associe un shader pour cet element
        Texture *_texture;      //Associe une texture pour cet element


    public :
        //---constructeur
        Element() = default;
        Element(Mesh *mesh, ShaderManager* shader, Texture* texture, const glm::vec3 position = glm::vec3(0.f,0.f,0.f), const glm::vec3 size = glm::vec3(1.f,1.f,1.f), const glm::vec3 rotation = glm::vec3(0.f,0.f,0.f));

        //---destructeur
        ~Element();

        //---méthodes
        //transformations
        inline void translate(const glm::vec3 &vec){
            _position += vec;
        }

        inline void scale(const glm::vec3 &vec){
            _size += vec;
        }

        inline void rotate(const glm::vec3 &vec){
            _rotation += vec;
        }

        //draw
        void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &ViewMatrix);

        //getters
        glm::mat4 MVMatrix() const;

        inline Mesh *mesh() const{
            return _mesh;
        }

        inline const glm::vec3 &position() const{
            return _position;
        }

        inline const glm::vec3 &size() const{
            return _size;
        }

        inline const glm::vec3 &rotation() const{
            return _rotation;
        }

        //setters
        inline glm::vec3 &position(){
            return _position;
        }

        inline glm::vec3 &size(){
            return _position;
        }

        inline glm::vec3 &rotation(){
            return _position;
        }

        inline virtual std::string type() const {
            return "Element";
        }

        //Affichage :
        friend std::ostream &operator<<(std::ostream &os, const Element &element){
            os << "     MVMatrix : " << element.MVMatrix() << "\n";
            os << "     Position : " << element._position << "\n";
            os << "     Size     : " << element._size << "\n";
            os << "     Rotation : " << element._rotation << "\n";
            os << "    +Shader   :\n" << *element._shader;
            os << "    +Texture  :\n" << *element._texture;
            os << "    +Mesh     :\n" << *element._mesh;
            return os;
        }

};