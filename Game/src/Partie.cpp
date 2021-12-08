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