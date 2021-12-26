#include <Elements/Personnage.hpp>

void Personnage::turnLeft(){
    rotate(glm::vec3(0,glm::radians(90.f),0));
};

void Personnage::turnRight(){
    rotate(glm::vec3(0,glm::radians(-90.f),0));
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