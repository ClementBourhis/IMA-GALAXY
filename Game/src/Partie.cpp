#include <iostream>
#include <cassert>
#include <fstream>
#include <string>

#include <Game/Partie.hpp>
#include <Game/Plateau.hpp>

Partie::Partie(const std::string appPath, const int niveau)
: _map(appPath, niveau), _assets(appPath), _direction(0), _niveau(niveau)
{
    //explorateur
    _explorateur = dynamic_cast<Personnage*>(_assets.element("explorateur"));
    _explorateur->vitesse() = static_cast<float>(_niveau) * (1000/static_cast<float>(_framerate)) / 1000;
    _explorateur->hauteur() = _explorateur->position().y;

    //skybox
    _skybox = dynamic_cast<Skybox*>(_assets.element("skybox"+std::to_string(niveau)));
};

void Partie::getInfosPlateau(){
    _map.infosPlateau();
}

void Partie::eventManager(SDL_Event& e){
    //CAMERA
    _camera.controlManager(e, _direction);

    //PERSONNAGE
    //_explorateur->controlManager(e);
    
    //Controles de Jeu
    switch(e.type){
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym){

                case SDLK_q:
                    //_explorateur->turnLeft();
                    _explorateur->rotate(glm::vec3(0,glm::radians(90.f),0));
                    _camera.changeDirection(-90.f);
                    changeDirection(false);
                    break;
                
                case SDLK_d:
                    _explorateur->rotate(glm::vec3(0,glm::radians(-90.f),0));
                    _camera.changeDirection(90.f);
                    changeDirection(true);
                    break;

                case SDLK_z:
                    _explorateur->jumping() = true;
                    //_explorateur->translate(glm::vec3(0,0.5,0));
                    break;
                
            }

        default:
            break;
    }
}

//dessine tous les elements de la scene
void Partie::draw(glm::mat4 ProjMatrix) {
    //update position camera en fonction de la position de l'explorateur
    _camera.position() = _explorateur->position();
    //se mettre au niveau des yeux de l'explorateur
    _camera.translateEyes(_explorateur->size(), _direction);
    

    _skybox->updatePosition(_camera.getPositionInScene());
    _skybox->draw(ProjMatrix, _camera.getViewMatrix(), false);

    for(const auto &it : _map.getCells()){
            _assets.element("floor")->update2DPosition(it.getPosition());
            _assets.element("floor")->draw(ProjMatrix, _camera.getViewMatrix());
    }

    for(const auto &it : _map.getPieces()){
            _assets.element("piece")->update2DPosition(it.getPosition());
            _assets.element("piece")->draw(ProjMatrix, _camera.getViewMatrix());
    }
    //rotation des pièces
    _assets.element("piece")->rotate(glm::vec3(0,0,glm::radians(180 * (1000/static_cast<float>(_framerate))/1000)));

    _explorateur->jump();
    _explorateur->draw(ProjMatrix, _camera.getViewMatrix());
    _explorateur->avancer(_direction);
}

void Partie::changeDirection(bool goud){ //gauche (0) ou droite (1)
    if(goud){
        if(_direction==3){
            _direction=0;
        }
        else{
            _direction++;
        }
    }
    else{
        if(_direction==0){
            _direction=3;
        }
        else{
            _direction--;
        }
    }
}