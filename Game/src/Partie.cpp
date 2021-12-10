#include <iostream>
#include <cassert>
#include <fstream>
#include <string>

#include <Game/Partie.hpp>
#include <Game/Plateau.hpp>

Partie::Partie(const std::string appPath, const int niveau)
: _map(appPath, niveau)
{
};

void Partie::getInfosPlateau(){
    _map.infosPlateau();
}

void Partie::setCameraEvent(SDL_Event& e){
    switch(e.key.keysym.sym) {
        case SDLK_UP:
            std::cout << "Zoom in" << std::endl;
            _camera.moveFront(1.f);
            break;
        case SDLK_DOWN:
            std::cout << "Zoom out" << std::endl;
            _camera.moveFront(-1.f);
            break;
        default:
            break;
    }
}

void Partie::eventManager(SDL_Event& e){
    switch (e.type) {
        case SDL_KEYDOWN:
            switch(e.key.keysym.sym) {
                case SDLK_UP:
                    //std::cout << "Zoom in" << std::endl;
                    _camera.moveFront(1.f);
                    break;
                case SDLK_DOWN:
                    //std::cout << "Zoom out" << std::endl;
                    _camera.moveFront(-1.f);
                    break;
                default:
                    break;
            }
            break;

        case SDL_MOUSEMOTION:
                if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT) == true) { //si le clic gauche est enfoncée
                        if (e.motion.xrel != 0) {
                            _camera.rotateUp(e.motion.xrel / 1.5f);
                        }
                        if (e.motion.yrel != 0) {
                            _camera.rotateLeft(e.motion.yrel / 1.5f);
                        }
                        break;
                }
                break;
        default:
            break;
    }
}