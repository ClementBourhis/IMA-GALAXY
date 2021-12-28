#pragma once

#include "Element.hpp"

class Personnage : public Element {
    //---attributs de Element
    public:
        bool _jumping = false;
        bool _jumpSens = true; //true montée, false descente
        float _maxJump = 0.6;
        float _vitesse; //avancement en bloc par seconde
        float _hauteur; //hauteur d'origine

        //---constructeur
        Personnage(Mesh *mesh,ShaderManager *shader, Texture *texture, const glm::vec3 position = glm::vec3(0.f,0.f,0.f), const glm::vec3 size = glm::vec3(1.f,1.f,1.f), const glm::vec3 rotation = glm::vec3(0.f,0.f,0.f)) : Element(mesh, shader, texture, position,size,rotation){
        }

        //méthodes
        void avancer(unsigned int dir);
        void turnLeft();
        void turnRight();
        void jump();

        //getter
        inline const float &vitesse() const{
            return _vitesse;
        }
        inline const float &hauteur() const{
            return _hauteur;
        }
        //setter
        inline float &vitesse(){
            return _vitesse;
        }
        inline float &hauteur(){
            return _hauteur;
        }
        inline bool &jumping(){
            return _jumping;
        }

        void controlManager(const SDL_Event &e);

        inline std::string type() const override {
            return "Personnage";
        }
};