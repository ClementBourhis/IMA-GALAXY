#pragma once

#include <glimac/glm.hpp>
#include <cmath>
#include <iostream>

//Pour l'instant c'est TrackballCamera
class Camera{
    private :
        //attributs
        float _fDistance;
        float _fAngleX;
        float _fAngleY;
        bool _cameraType; //false=centré explorateur ; true=vue première personne

    public :
        //constructeur
        Camera(): _fDistance(-5), _fAngleX(30), _fAngleY(0), _cameraType(false){}

        //méthodes
        void moveFront(float delta) {
            if(_fDistance+delta < 0){
                _fDistance+=delta;
            }
        }

        void rotateLeft(float degrees){
            if(_fAngleX+degrees < 90 && _fAngleX+degrees > -90){
                _fAngleX+=degrees;
            }
        }

        void rotateUp(float degrees){
            _fAngleY+=degrees;
        }

        glm::mat4 getViewMatrix(){
            glm::mat4 VM = glm::mat4(1.f);
            VM = glm::translate(VM, glm::vec3(0.0f, 0.0f, _fDistance));
            VM = glm::rotate(VM, glm::radians(_fAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
            VM = glm::rotate(VM, glm::radians(_fAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
            return VM;
        }
};