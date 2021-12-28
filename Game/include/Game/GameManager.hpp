#pragma once

#include "Partie.hpp" 

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
		//---constructeur
        GameManager() = default;
        //---destructeur
        ~GameManager()=default;

		//getters
		inline const unsigned int &framerate() const{
            return _framerate;
        }
		inline const unsigned int &windowWidth() const{
            return _windowWidth;
        }
		inline const unsigned int &windowHeight() const{
            return _windowHeight;
        }
		inline const float &zNear() const{
            return _zNear;
        }
		inline const float &zFar() const{
            return _zFar;
        }

		//---methodes
		//void draw();
};