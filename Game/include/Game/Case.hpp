#pragma once

#include <vector>

#include <glimac/glm.hpp>

class Case {

	private:
		//attributs
		glm::vec3 _position;
		std::string type;

	public:
		//constructeurs-/-destructeur
		Case() = default; 
		//constructeur à partir de la position de la case sur une grille 2D
		Case(int x, int y);
		~Case() = default;

		//methodes
		glm::vec3 getPosition() const;
		void setPosition(int x,int y,int z);
		glm::vec2 getTexCoord();
};