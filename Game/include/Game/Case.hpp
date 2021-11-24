#pragma once

#include <vector>

#include <glimac/glm.hpp>

class Case {

	private:
		//attributs
		glm::vec3 _position;
		glm::vec2 _texCoord;

	public:
		//constructeurs-/-destructeur
		Case() = default; 
		Case(glm::vec3 position, glm::vec2 _texCoord);
		~Case() = default;

		//methodes
		glm::vec3 getPosition();
		glm::vec2 getTexCoord();
};