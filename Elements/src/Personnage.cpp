#include <Elements/Personnage.hpp>

void Personnage::avancer(unsigned int dir){
    switch (dir){
        case 0:
            translate(glm::vec3(0,0,_vitesse));
            break;
        
        case 1:
            translate(glm::vec3(-_vitesse,0,0));
            break;

        case 2:
            translate(glm::vec3(0,0,-_vitesse));
            break;

        case 3:
            translate(glm::vec3(_vitesse,0,0));
            break;
    }
};

void Personnage::turnLeft(){
    rotate(glm::vec3(0,glm::radians(90.f),0));
};

void Personnage::turnRight(){
    rotate(glm::vec3(0,glm::radians(-90.f),0));
};

void Personnage::jump(){
    if (_jumping) {
        if(_position.y<(_hauteur+_maxJump) && _jumpSens){
            translate(glm::vec3(0,_vitesse,0));
        }
        else{
            _jumpSens = false;
            translate(glm::vec3(0,-_vitesse,0));
        }
        
        // if the jump is over
        if (_position.y <= _hauteur) {
        _jumping = false;
        _jumpSens = true;

        _position.y = _hauteur;
        _rotation.x = glm::radians(0.f);
        }
    }
};

void Personnage::controlManager(const SDL_Event &e){
    switch(e.type){
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym){

                case SDLK_q:
                    turnLeft();
                    break;
                
                case SDLK_d:
                    turnRight();
                    break;
               
            }

        default:
            break;
    }
}