#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Case.hpp"

class Plateau {

	private:
		//attributs
		///* ! Question ! */ std::string _name; //Nécessaire ??????????
		std::vector<Case> _cells; //tableau de cases

	public:
		//constructeurs-/-destructeur
		Plateau() = default; 
		//Plateau(std::string name);
		~Plateau() = default;

		//methodes
		//void addCell(Case cell);
		//void createPath(const int nbCases);
		//void saveConfig() const;
		void loadConfig(const std::string &filename); //charge le chemin à partir du fichier txt
		void infosPlateau();
};