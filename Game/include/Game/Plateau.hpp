#pragma once

//STL
#include <fstream>	//std::ifstream, std::ofstream
#include <stdexcept>//std::error...
#include <iostream>	//std::cerr
#include <string>	//std::string<T>
#include <vector>	//std::vector<T>

//Game
#include "Case.hpp"

/**
 * \file Plateau.hpp
 * \brief Déclaration de la classe Plateau
 */
/**
 * \class Plateau
 * \brief Récupère la position des éléments d'une map pgm
 */

class Plateau {
	private:
		//---attributs
		std::vector<Case> _cells; 		/*!< tableau de cases */
		std::vector<Case> _pieces; 		/*!< tableau de pieces */
		std::vector<Case> _obstacles; 	/*!< tableau d'obstacles */

	public:
		//---constructeurs-/-destructeur
		Plateau() = default; 
		Plateau(const std::string appPath, const int niveau);
		~Plateau() = default;

		//---methodes
		/// \brief charge le chemin à partir du fichier txt
		void loadParcours(const std::string &filename);
		/// \brief affiche en cout les éléments du plateaux
		void infosPlateau();

		//getters
		inline std::vector<Case> getCells() const{
			return _cells;
		}

		inline std::vector<Case> getPieces() const{
			return _pieces;
		}

		inline std::vector<Case> getObstacles() const{
			return _obstacles;
		}
};