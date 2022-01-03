#pragma once

#include <string>

#include "Partie.hpp" 
#include "Menu.hpp" 
#include "AssetsManager.hpp"

/**
 * \file GameManager.hpp
 * \brief Déclaration de la classe GameManager
 */

/**
 * \class GameManager
 * \brief moteur de Jeu, qui gère les assets, le menu et la partie
 */

class GameManager {
	private:
		//---attributs
		AssetsManager* _assets = nullptr;
		Menu* _menu = nullptr;
		Partie* _currentPartie = nullptr;

		//Configurations
		std::string _appPath;				//chemin absolue de l'application
		unsigned int _framerate = 24;		//vitesse d'affichage
		unsigned int _windowWidth = 800;	//résolution par défaut : longeur
		unsigned int _windowHeight = 600;	//résolution par défaut : hauteur
		float _zNear = 0.1;					//distance d'affichage  : proche 
		float _zFar = -100;					//distance d'affichage	: loin

		bool _menuVisibility; //visibilité du menu (montrer soit la partie soit le menu)

	public:
		//---constructeur
		/**
		 * \brief constructeur
		 * \param appPath : le chemin du répertoire où se situe le main de l'application
		 */
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
		void makeFullscreen();	//adapte la taille de la fenètre à l'écran 
		void createPartie(const int niveau);	//créer une partie
		void loadPartie(); //charger une partie depuis une sauvegarde

		//suppression d'une partie
		inline void supprPartie(){
			delete _currentPartie;
			_currentPartie->reset();
			_currentPartie = nullptr;

			_menuVisibility = true;
		};

		//quitte le jeu en libérant la mémoire
		inline void deleteGame(){
			delete _assets;
			_assets = nullptr;

			if(_currentPartie!=nullptr){
				supprPartie();
			}

			delete _menu;
			_menu = nullptr;
		};

		//affichage du jeu dans la fenètre
		void draw(glm::mat4 ProjMatrix);

		//gestion des controles et des evènement sur la fenètre
		bool eventManager(SDL_Event& e);
};