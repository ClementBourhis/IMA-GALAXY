#pragma once

#include <string>

#include "Partie.hpp" 
#include "Menu.hpp" 
#include "AssetsManager.hpp"

class GameManager {
	private:
		//---attributs
		AssetsManager* _assets = nullptr;
		Menu* _menu = nullptr;
		Partie* _currentPartie = nullptr;

		//Configurations
		std::string _appPath;
		unsigned int _framerate = 24;
		unsigned int _windowWidth = 800;
		unsigned int _windowHeight = 600;
		float _zNear = 0.1;
		float _zFar = -100;

	public:
		//---constructeur
		GameManager() = default;
		GameManager(const std::string appPath);
        //---destructeur
        ~GameManager()=default;

		//getters
		inline const std::string &appPath() const{
            return _appPath;
        }
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
		inline const AssetsManager *assets() const{
            return _assets;
        }

		inline const Partie* currentPartie() const{
            return _currentPartie;
        }

		//setters
		inline Partie* currentPartie(){
            return _currentPartie;
        }

		//---methodes
		void makeFullscreen();
		void createPartie(const int niveau);
		inline void supprPartie(){
			delete _currentPartie;
			_currentPartie = nullptr;
		};
		inline void deleteGame(){
			_assets->unloadAssets();
			delete _assets;
			_assets = nullptr;

			if(_currentPartie!=nullptr){
				supprPartie();
			}

			delete _menu;
			_menu = nullptr;
		};
		void draw(glm::mat4 ProjMatrix);
		void eventManager(SDL_Event& e);
};