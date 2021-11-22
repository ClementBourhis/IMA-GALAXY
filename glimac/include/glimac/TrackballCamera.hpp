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
                return glm::translate(glm::mat4(1), glm::vec3(0, 0, m_fDistance)) * glm::rotate(glm::mat4(1), (float)(m_fAngleY * M_PI/180), glm::vec3(1, 0, 0))  * glm::rotate(glm::mat4(1), (float)(m_fAngleX * M_PI/180), glm::vec3(0, 1, 0));
            }
    };
}
