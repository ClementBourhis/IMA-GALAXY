#pragma once

//STL
#include <string> 			//std::string

//glimac
#include <glimac/glm.hpp> 	//glm::vec3, glm::vec2

/**
 * \file Case.hpp
 * \brief Déclaration de la classe Case
 */
/**
 * \class Case
 * \brief Permet de prendre en charge les plateformes sur lequel le personnage va évoluer
 */

class Case {
	private:
		//---attributs
		glm::vec3 _position;

	public:
		//---constructeurs-/-destructeur
		Case() = default; 
		/// \brief constructeur à partir de la position de la case sur une grille 2D
		Case(int x, int y, float hauteur);
		~Case() = default;

		//---methodes
		/// \brief getter de la position
		glm::vec3 getPosition() const;

		/// \brief setter de la position
		void setPosition(int x,int y,int z);
};