#pragma once

//glimac
#include <glimac/glm.hpp>               //glm::radian, glm::mat4, glm::vec3
#include <glimac/SDLWindowManager.hpp>  //SDL_Event

//STL
#include <cmath>                        //cos, sin

//La classe camera créer un objet camera qui prend en compte une version trackball (à amélioré pour faire une version freefly) 
class Camera{
    private :
        //---attributs
        //paramètre pour la caméra Trackball
        glm::vec3 _position;     
        float _distance;
        float _angleX;
        float _angleY;

        //paramètre pour la camera en Freefly
        float _phi;
        float _theta;
        glm::vec3 _frontVector;
        glm::vec3 _leftVector;
        glm::vec3 _upVector;

        float _maxAngle;
        bool _cameraType; //choix de la camera Trackball(false) ou camera freefly(true)

        //---méthodes
        //calcul les vecteurs pour la camera freefly
        void computeDirectionVector(){
            _frontVector = glm::vec3(cos(_theta) * sin(_phi), sin(_theta), cos(_theta) * cos(_phi));
            _leftVector = glm::vec3(sin(glm::radians(_phi)), 0, cos(glm::radians(_phi)));
            _upVector = glm::cross(_frontVector, _leftVector);
        }

    public :
        //---constructeur
        Camera();

        //---destructeur
        ~Camera(){};

        //---méthodes
        void initialization(const float &distance = -5, const float &angleY = 20.f, const glm::vec3 &position = glm::vec3(), const float &maxAngle = 40.f); //initialisation des paramètre de la caméra
        void controlManager(const SDL_Event &e);                                                                                                            //regroupement des contrôles pour la camera
        void changeCameraType(bool type);                                                                                                                   //change le type de la camera
        
        //méthode Trackball
        void setPosition(const glm::vec3 &position); //changement du centre de la trackball
        glm::vec3 getPosition(){
            return _position;
        }; //récupère la position du centre de la caméra

        //mouvements
        void moveFront(float delta);
        void rotateLeft(float degrees);
        void rotateUp(float degrees);

        glm::mat4 getViewMatrix(); //récupère la matrice ViewMatrix

        //méthode freefly
        //...
        
};