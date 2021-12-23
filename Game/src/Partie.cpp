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

void Partie::eventManager(SDL_Event& e){
    _camera.controlManager(e);
}

//update tous les elements de la scene
void Partie::update() {
    //_camera.update();
    //_skybox.update();
    //_explorateur.update();
}

//dessine tous les elements de la scene
void Partie::draw() {
    //_skybox.draw();
    //_explorateur.draw();
}