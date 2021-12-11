#pragma once

//STL
#include <fstream>	//std::ifstream, std::ofstream
#include <stdexcept>//std::error...
#include <iostream>	//std::cerr
#include <string>	//std::string<T>
#include <vector>	//std::vector<T>

//Game
#include "Case.hpp"

class Plateau {
	private:
		//---attributs
		std::vector<Case> _cells; //tableau de cases

	public:
		//---constructeurs-/-destructeur
		Plateau() = default; 
		Plateau(const std::string appPath, const int niveau); 
		~Plateau() = default;

		//---methodes
		//void addCell(Case cell);
		//void createPath(const int nbCases);
		void loadParcours(const std::string &filename); //charge le chemin à partir du fichier txt
		void infosPlateau();

		inline std::vector<Case> getCells() const{
			return _cells;
		}
};