#include <iostream>
#include <cassert>
#include <fstream>
#include <string>

#include <Game/Plateau.hpp>


Plateau::Plateau(const std::string appPath, const int niveau)
{
    loadParcours(appPath + std::to_string(niveau) + ".pgm");
};

void Plateau::loadParcours(const std::string &filename) {
    std::ifstream file(filename);

    if (file.fail()){
        std::cerr << "Error: " << strerror(errno);
    }

    //on récupère notre fichier ligne par ligne
    std::string line;
    //on passe les deux premières lignes qui contiennent P2 et created by gimp
    std::getline(file, line);
    std::getline(file, line);

    int widthGrid, heightGrid, value;
    file >> widthGrid;
    file >> heightGrid;

    /*std::cout << widthGrid << std::endl;
    std::cout << heightGrid << std::endl;*/

    //valeur max b&w
    std::getline(file, line);
    std::getline(file, line);
    //std::cout << "VALEUR MAX :" << line << std::endl;

    for (int i=0; i<heightGrid; i++) {
        for (int j=0; j<widthGrid; j++) {
            std::getline(file, line);
            if(line!="0"){
                Case cell(j,((heightGrid-1)-i)); //heightGrid-i pour avoir la case du bas comme la premiere en (0,0,0)
                _cells.push_back(cell);
            }
        }
    }

    file.close();
}

//voir les infos des cases entrées dans le plateau
void Plateau::infosPlateau(){
    for(int i=0; i<_cells.size(); i++){
        std::cout << _cells[i].getPosition() << std::endl;
    }
};

/*void Plateau::saveConfig() const {
    std::ofstream file("Chemin.txt");
    
    file.close();
};*/