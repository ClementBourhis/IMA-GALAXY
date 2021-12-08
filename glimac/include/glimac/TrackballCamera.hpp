#pragma once

#include "glm.hpp"
#include <cmath>

namespace glimac
{
    class TrackballCamera{
        private :
            //attributs
            float m_fDistance;
            float m_fAngleX;
            float m_fAngleY;

        public :
            //constructeur
            TrackballCamera(): m_fDistance(-5), m_fAngleX(0), m_fAngleY(0){}

            //méthodes
            void moveFront(float delta) {
                m_fDistance+=delta;
            }

            void rotateLeft(float degrees){
                m_fAngleX+=degrees;
            }

            void rotateUp(float degrees){
                m_fAngleY+=degrees;
            }

            glm::mat4 getViewMatrix(){
                glm::mat4 VM = glm::mat4(1.f);
                 VM = glm::translate(VM, glm::vec3(0.0f, 0.0f, m_fDistance));
                VM = glm::rotate(VM, glm::radians(m_fAngleY), glm::vec3(1.0f, 0.0f, 0.0f));
                VM = glm::rotate(VM, glm::radians(m_fAngleX), glm::vec3(0.0f, 1.0f, 0.0f));
                return VM;
            }
    };
}
