#pragma once

#include "Element.hpp"

//la classe Personnage permet de spécifier à l'élément qu'il s'agit d'un personnage, 
//on lui attribut un état particulier et des commandes pour le contrôler
class Personnage : public Element {
    //---attributs de Element
    public:
        bool _jumping = false;  //vérivie l'état de saut
        bool _jumpSens = true;  //true montée, false descente
        float _maxJump = 0.8;   //hauteur maximal de saut
        float _vitesse;         //avancement en bloc par seconde
        float _hauteur;         //hauteur d'origine

        //---constructeur
        Personnage(Mesh *mesh,ShaderManager *shader, Texture *texture, const glm::vec3 position = glm::vec3(0.f,0.f,0.f), const glm::vec3 size = glm::vec3(1.f,1.f,1.f), const glm::vec3 rotation = glm::vec3(0.f,0.f,0.f)) : Element(mesh, shader, texture, position,size,rotation){
        }

        //---méthodes
        //Controle du personnage
        void avancer(unsigned int dir);
        void turnLeft();
        void turnRight();
        void jump();

        //getters
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

        inline std::string type() const override {
            return "Personnage";
        }
};