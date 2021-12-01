#pragma once

#include "Plateau.hpp"

class Partie {

	private:
        Plateau _map;
        //Personnage _persoPrincipal;
        //std::vector<Enemy> _enemies;
        //config en fonction du niveau de difficulté

	public:
		//constructeurs-/-destructeur
		Partie() = default;
        Partie(const std::string appPath, const int niveau);
		~Partie() = default;

		//methodes
        //void savePartie() const;
};