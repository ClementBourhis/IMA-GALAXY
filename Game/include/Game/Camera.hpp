#pragma once

//glimac
#include <glimac/glm.hpp>               //glm::radian, glm::mat4, glm::vec3
#include <glimac/SDLWindowManager.hpp>  //SDL_Event

//STL
#include <cmath>                        //cos, sin


/**
 * \file Camera.hpp
 * \brief Déclaration de la classe Camera
 */
/**
 * \class Camera
 * \brief Permet de créer un objet camera qui prend en compte une version trackball et une version freefly. Elle embarque tous ses controles dans le controleManager.
 */

class Camera{
    private :
        //---attributs
        //paramètre pour la caméra Trackball
        glm::vec3 _position;        /*!< position du centre de l'objet que suis la caméra */
        float _distance;            /*!< distance par rapport à l'objet */
        float _angleX;              /*!< angle horizontal */
        float _angleY;              /*!< angle vertical */

        //paramètre pour la camera en Freefly
        float _phi;
        float _theta;               
        glm::vec3 _frontVector;
        glm::vec3 _leftVector;
        glm::vec3 _upVector;

        float _angleDir;    /*!< angle de la direction de la caméra (utilisé pour l'angle maximum de la caméra freefly) */

        float _maxAngle;    /*!< angle max qui permet de tourner la tete de l'explorateur */
        bool _cameraType;   /*!< choix de la camera Trackball(false) ou camera freefly(true) */
        bool _blocked;      /*!< camera bloquée quand true */

    public :
        //---constructeur
        Camera();
        /// \brief constructeur
        /// \param dir : direction du personnage
        Camera(unsigned int dir);

        //---destructeur
        ~Camera(){};

        //---méthodes
        /// \brief regroupement des contrôles pour la camera
        void controlManager(const SDL_Event &e);
        /// \brief change le type de la camera
        void changeCameraType(bool type);
        /// \brief bloque ou débloque l'angle de vu de la caméra
        void changeBlock();

        //méthode Trackball
        /// \brief changement du centre de la trackball
        void setPosition(const glm::vec3 &position);
        /// \brief récupère la position de la caméra dans la scène pour la skybox
        glm::vec3 getPositionInScene(){
            return glm::vec3(glm::inverse(getViewMatrix())[3]);
        };

        //mouvements
        void moveFront(float delta);
        void rotateLeft(float degrees);
        void rotateUp(float degrees);
        void changeDirection(float degrees);
        
        /// \brief récupère la matrice ViewMatrix
        glm::mat4 getViewMatrix();

        //méthodes freefly

        /// \brief calcul les vecteurs pour la camera freefly
        void computeDirectionVectors(){
            _frontVector = glm::vec3(cos(_theta) * sin(_phi), sin(_theta), cos(_theta) * cos(_phi));
            _leftVector = glm::vec3(sin(_phi+(M_PI/2)), 0, cos(_phi+(M_PI/2)));
            _upVector = glm::cross(_frontVector, _leftVector);
        }

        //setters
        inline glm::vec3 &position(){
            return _position;
        }

        inline void translate(const glm::vec3 &vec){
            _position += vec;
        }
        /// \brief change le point d'origine de la caméra au niveau des yeux de l'explorateur et non de son centre
        inline void translateEyes(const glm::vec3 &size, unsigned int dir){
            float haut = size.y/2;
            float dvt = size.z/2;
            switch (dir){
                case 0:
                    translate(glm::vec3(0,haut,dvt));
                    break;
                
                case 1:
                    translate(glm::vec3(-dvt,haut,0));
                    break;

                case 2:
                    translate(glm::vec3(0,haut,-dvt));
                    break;

                case 3:
                    translate(glm::vec3(dvt,haut,0));
                    break;
            }
        }
        
};