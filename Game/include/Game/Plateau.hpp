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
		Plateau(const std::string appPath, const int niveau); 
		//Plateau(std::string name);
		~Plateau() = default;

		//methodes
		//void addCell(Case cell);
		//void createPath(const int nbCases);
		void loadParcours(const std::string &filename); //charge le chemin à partir du fichier txt
		void infosPlateau();

		inline std::vector<Case> getCells(){
			return _cells;
		}
};