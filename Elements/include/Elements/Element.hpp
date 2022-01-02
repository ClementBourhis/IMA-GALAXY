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
        glm::vec3 _physicBoxO;  //on détermine la zone physique d'un élement par 1 point d'origine O et sa taille

        //si l'élément est draw en plusieurs position, on stock les coordonées pour les physicaliser
        std::vector<glm::vec3> _listOfPosition;
        std::vector<glm::vec3> _blackList;
        std::vector<glm::vec3> _targetHit;

        //---méthode
        //on met à jour la physiqueBox qui se déplace avec l'objet
        inline void updatePhysicBox(){
            _physicBoxO = glm::vec3(_position.x - _size.x*0.5, _position.y - _size.y*0.5, _position.z - _size.z*0.5);
        }

    public :
        //---constructeur
        Element() = default;
        Element(Mesh *mesh, ShaderManager* shader, Texture* texture, const glm::vec3 position = glm::vec3(0.f,0.f,0.f), const glm::vec3 size = glm::vec3(1.f,1.f,1.f), const glm::vec3 rotation = glm::vec3(0.f,0.f,0.f));

        void addListOfPosition(std::vector<glm::vec3> listOfPosition);

        //---destructeur
        ~Element();

        //---méthodes
        //transformations
        inline void translate(const glm::vec3 &vec){
            _position += vec;
            updatePhysicBox();
        }

        inline void scale(const glm::vec3 &vec){
            _size += vec;
            updatePhysicBox();
        }

        inline void rotate(const glm::vec3 &vec){
            _rotation += vec;
        }

        //draw
        inline void draw(){
            //on bind les datas
            _mesh->bind();
            _shader->use();
            _texture->bind();

            _shader->sendUniformInt("uTexture", 0);

            _mesh->draw();

            //debind les datas
            _texture->debind();
            _mesh->debind();
        };

        void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &ViewMatrix, bool depthMask = true);

        void toBlackList(glm::vec3 position){
            _blackList.push_back(position);
        }

        void toTargetHit(glm::vec3 position){
            _targetHit.push_back(position);
        }

        void blackListAllHit(){
            for(const auto &it : _targetHit){
                bool isBlackListed = false;
                for(const auto &blacklisted : _blackList){
                    if(it == blacklisted){
                        isBlackListed = true;
                    }
                }
                if(!isBlackListed){
                    toBlackList(it);
                }
            }
        }

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

        inline const glm::vec3 &physicBoxO() const{
            return _physicBoxO;
        }

        inline const std::vector<glm::vec3> &listOfPosition() const{
            return _listOfPosition;
        }

        inline const std::vector<glm::vec3> &blackList() const{
            return _blackList;
        }

        inline const std::vector<glm::vec3> &targetHit() const{
            return _targetHit;
        }

        //setters
        inline glm::vec3 &position(){
            return _position;
        }

        inline glm::vec3 &size(){
            return _size;
        }

        inline glm::vec3 &rotation(){
            return _rotation;
        }

        inline virtual std::string type() const {
            return "Element";
        }

        inline void updatePosition(glm::vec3 position){
            _position = position;
            updatePhysicBox();
        }

        inline void update2DPosition(glm::vec3 position){ //update pour la map
            _position.x = position.x;
            _position.z = position.z;
            updatePhysicBox();
        }

        inline bool inContactWith(Element &element){    //interaction entre 2 elements retourne true s'il se touchent
            bool contact = false;
            bool contactX = false;
            bool contactY = false;
            bool contactZ = false;
            if(element.listOfPosition().size() > 0){
                for(auto &position : element.listOfPosition()){
                    contactX = false;
                    contactY = false;
                    contactZ = false;

                    glm::vec3 VirtualPhysicBoxO = glm::vec3(position.x - element.size().x*0.5, position.y - element.size().y*0.5, position.z - element.size().z*0.5);
                    if(_physicBoxO.x < VirtualPhysicBoxO.x + element.size().x && _physicBoxO.x + _size.x > VirtualPhysicBoxO.x){
                        contactX = true;
                    }

                    if(_physicBoxO.y < VirtualPhysicBoxO.y + element.size().y && _physicBoxO.y + _size.y > VirtualPhysicBoxO.y){
                        contactY = true;
                    }

                    if(_physicBoxO.z < VirtualPhysicBoxO.z + element.size().z && _physicBoxO.z + _size.z > VirtualPhysicBoxO.z){
                        contactZ = true;
                    }

                    if(contactX && contactY && contactZ){
                        contact = true;
                        if(element.blackList().size() > 0){
                            for(const auto &it : element.blackList()){
                                if(it == position){
                                    contact = false;
                                }
                            }
                        }
                        if(contact){
                            bool isTargetHit = false;
                            if(element.targetHit().size() > 0){
                                for(const auto &it : element.targetHit()){
                                    if(it == position){
                                        isTargetHit = true;
                                    }
                                }
                            }
                            if(!isTargetHit){
                                element.toTargetHit(position);
                            }
                        }
                    }
                }
            }

            else{ 
                if(_physicBoxO.x < element.physicBoxO().x + element.size().x && _physicBoxO.x + _size.x > element.physicBoxO().x){
                    contactX = true;
                }

                if(_physicBoxO.y < element.physicBoxO().y + element.size().y && _physicBoxO.y + _size.y > element.physicBoxO().y){
                    contactY = true;
                }

                if(_physicBoxO.z < element.physicBoxO().z + element.size().z && _physicBoxO.z + _size.z > element.physicBoxO().z){
                    contactZ = true;
                }

                if(contactX && contactY && contactZ){
                    contact = true;
                }
            }

            return contact;
                
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