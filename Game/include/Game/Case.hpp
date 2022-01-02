#pragma once

//STL
#include <string> 			//std::string

//glimac
#include <glimac/glm.hpp> 	//glm::vec3, glm::vec2

//La classe Case permet de prendre en charge les plateformes sur lequel le personnage va évoluer
class Case {
	private:
		//---attributs
		glm::vec3 _position;

	public:
		//---constructeurs-/-destructeur
		Case() = default; 
		Case(int x, int y, float hauteur);	//constructeur à partir de la position de la case sur une grille 2D
		~Case() = default;

		//---methodes
		//getter
		glm::vec3 getPosition() const;

		//setter
		void setPosition(int x,int y,int z);
};