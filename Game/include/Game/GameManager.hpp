#pragma once

//STL
#include <string> 			//std::string

//glimac
#include <glimac/glm.hpp> 	//glm::vec3, glm::vec2

class GameManager {
	private:
		//---attributs
		//Menu _menu;
		//Partie _currentPartie;

		//Configurations
		unsigned int _framerate = 24;
		unsigned int _windowWidth = 800;
		unsigned int _windowHeight = 600;
		float _zNear = 0.1;
		float _zFar = -100;

	public:
		//---constructeurs-/-destructeur
		GameManager() = default; 
		~gameManager() = default;

		//---methodes
		//void draw();
};