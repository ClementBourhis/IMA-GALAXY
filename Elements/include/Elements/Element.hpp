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

/**
 * \file Element.hpp
 * \brief Déclaration de la classe Element
 */
/**
 * \class Element
 * \brief rassemble tous les elements constituant le jeu (sol, personnage, pièce...)
 */

class Element{
    protected :
        //---attributs
        Mesh* _mesh;            /*!< permet que l'élément ai une représentation physique basé sur un mesh */
        glm::vec3 _position;    /*!< position de l'element dans la scène */
        glm::vec3 _size;        /*!< défini la taille de l'élément */
        glm::vec3 _rotation;    /*!< défini la rotation de l'élément */
        ShaderManager *_shader; /*!< Associe un shader pour cet element */
        Texture *_texture;      /*!< Associe une texture pour cet element */
        glm::vec3 _physicBoxO;  /*!< on détermine la zone physique d'un élement par 1 point d'origine O et sa taille */

        //si l'élément est draw en plusieurs position, on stock les coordonées pour les physicaliser
        std::vector<glm::vec3> _listOfPosition; /*!< liste des positions où l'objet s'affiche */
        std::vector<glm::vec3> _blackList;      /*!< liste des positions où l'objet ne dois plus s'afficher (ex : pour les pièces) */
        std::vector<glm::vec3> _targetHit;      /*!< liste des positions où l'objet à été touché */

        //---méthode
        //on met à jour la physiqueBox qui change de taille où se déplace avec l'objet
        inline void updatePhysicBox(){
            _physicBoxO = glm::vec3(_position.x - _size.x*0.5, _position.y - _size.y*0.5, _position.z - _size.z*0.5);
        }

    public :
        //---constructeur
        Element() = default;
        Element(Mesh *mesh, ShaderManager* shader, Texture* texture, const glm::vec3 position = glm::vec3(0.f,0.f,0.f), const glm::vec3 size = glm::vec3(1.f,1.f,1.f), const glm::vec3 rotation = glm::vec3(0.f,0.f,0.f));

        //---destructeur
        ~Element();

        //---méthodes
        /// \brief transformation de la position d el'élément
        inline void translate(const glm::vec3 &vec){
            _position += vec;
            updatePhysicBox();
        }

        /// \brief transformation de la taille de l'élément
        inline void scale(const glm::vec3 &vec){
            _size += vec;
            updatePhysicBox();
        }
        /// \brief rotation de l'élément
        inline void rotate(const glm::vec3 &vec){
            _rotation += vec;
        }

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


        /// \brief méthodes pour un éléments multi-affiché, on indique à l'élément toutes les positions où il devra s'afficher
        void addListOfPosition(std::vector<glm::vec3> listOfPosition); 
        /// \brief méthodes pour un éléments multi-affiché, on indique à quel position on souhaite que l'élément ne s'affiche plus
        void toBlackList(glm::vec3 position){
            _blackList.push_back(position);
        }
        /// \brief méthodes pour un éléments multi-affiché, on indique quel position l'objet à été touché
        void toTargetHit(glm::vec3 position){
            _targetHit.push_back(position);
        }
        /// \brief méthodes pour un éléments multi-affiché, on blacklist tout les objets qui ont été touché
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
        /// \brief on récupère ma ViewMatrice de l'élément
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

        /// \brief retourne en string de quel type est l'élément (à spécifier dans les classes fille de élément)
        inline virtual std::string type() const {
            return "Element";
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

        inline void updatePosition(glm::vec3 position){
            _position = position;
            updatePhysicBox();
        }

        /// \brief Quand la partie se termine on reset les listes de contact des éléments pour recommencer à zero
        inline void resetElement(){
            for(int i = 0; i<_targetHit.size(); i++){
                _targetHit.pop_back();
            }
            for(int i = 0; i<_blackList.size(); i++){
                _blackList.pop_back();
            }
        }

        /// \brief interaction entre 2 elements retourne true s'ils se touchent
        inline bool inContactWith(Element &element, bool Yaxe = true){
            bool contact = false;   //les éléments sont en contact s'ils se rencontre sur les 3 axes
            bool contactX = false;
            bool contactY = false;
            bool contactZ = false;

            //Dans le cas où l'élément est multi-affiché, il faut vérifier le contact avec toutes ces positions d'affichage car en réalité une fois sa boucle draw terminé, l'élément ne se trouve qu'a 1 seul endroit dans la scène
            if(element.listOfPosition().size() > 0){
                for(auto &position : element.listOfPosition()){
                    //reset pour la nouvelle position
                    contactX = false;
                    contactY = false;
                    contactZ = false;

                    //on calcule le point d'origine de la physiqueBox de la position d'affichage de l'élément 
                    glm::vec3 VirtualPhysicBoxO = glm::vec3(position.x - element.size().x*0.5, position.y - element.size().y*0.5, position.z - element.size().z*0.5);
                    
                    //on vérifie le contact sur les 3 axes
                    if(_physicBoxO.x < VirtualPhysicBoxO.x + element.size().x && _physicBoxO.x + _size.x > VirtualPhysicBoxO.x){
                        contactX = true;
                    }

                    if(_physicBoxO.y < VirtualPhysicBoxO.y + element.size().y && _physicBoxO.y + _size.y > VirtualPhysicBoxO.y){
                        contactY = true;
                    }

                    if(_physicBoxO.z < VirtualPhysicBoxO.z + element.size().z && _physicBoxO.z + _size.z > VirtualPhysicBoxO.z){
                        contactZ = true;
                    }

                    //si on ne prend pas en compte l'axe Y (ex pour le sol où la comète survole le chemin et peu sauter)
                    if(!Yaxe){
                        contactY = true;
                    }

                    //si l'objet est blacklisté, il n'est pas considéré comme touché
                    if(contactX && contactY && contactZ){
                        contact = true;
                        if(element.blackList().size() > 0){
                            for(const auto &it : element.blackList()){
                                if(it == position){
                                    contact = false;
                                }
                            }
                        }
                        //s'il y a contact, on indique à l'élément touché qu'elle position à été en contact
                        //s'il a été déjà touché à cette position on ne le rajoute pas dans les éléments déjà touché 
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

            //dans le cas où l'élément est unique on vérifie seulment si on le touche
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

        /// \brief Affichage
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