#pragma once

#include <string>

#include "Partie.hpp" 
#include "Menu.hpp" 
#include "AssetsManager.hpp"

/// \class GameManager
/// \file GameManager.hpp
/// \brief class defining a vector for linear algebra operations. TEST

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

		bool _menuVisibility; //visibilité du menu (montrer soit la partie soit le menu)

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
		void loadPartie(); //charger une partie depuis une sauvegarde
		inline void supprPartie(){
			delete _currentPartie;
			_currentPartie = nullptr;

			_menuVisibility = true;
		};
		inline void deleteGame(){
			delete _assets;
			_assets = nullptr;

			if(_currentPartie!=nullptr){
				supprPartie();
			}

			delete _menu;
			_menu = nullptr;
		};
		void draw(glm::mat4 ProjMatrix);
		bool eventManager(SDL_Event& e);
};