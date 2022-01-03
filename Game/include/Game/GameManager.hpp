#pragma once

#include <string>

#include "Partie.hpp" 
#include "Menu.hpp" 
#include "AssetsManager.hpp"

// ========== DOXYGEN MENU ========== //
/// \mainpage
/// \tableofcontents
/// \section introduction_sec Introduction
/// Projet de synthèse d'image, programmation, et architecture logicielle lors du semestre 3 à l'IMAC, inspiré du jeu Temple Run.
/// Par Clément Bourhis, Sirine Bradai, Sacha Chouvin, et Estelle Thouvenin.
/// \section install_bigsec Installer le jeu
/// \subsection dependencies_sec Librairies nécessaires
/// \li SDL
/// \li OpenGL
/// \li GLEW
/// \li Doxygen pour la documentation (optionnel)
/// \subsection install_sec Compiler le projet avec cmake (Linux / Mac)
/// \li mkdir build
/// \li cd build
/// \li cmake [chemin vers la racine du dossier du projet]
/// \li make
/// \li ./Jeu/Jeu_Temple_Run
/// \li documentation optionnelle : commande 'doxygen' depuis la racine du dossier du projet
// ================================= //


/**
 * \file GameManager.hpp
 * \brief Déclaration de la classe GameManager
 */
/**
 * \class GameManager
 * \brief Le GameManager est le noeud du jeu, il crée des parties et rassemble tous les éléments du jeu
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
		GameManager() = default;
		/**
		 * \brief constructeur
		 * \param appPath : le chemin du répertoire où se situe le main de l'application
		 */
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
		/// \brief adapte la taille de la fenètre à l'écran
		void makeFullscreen();
		/// \brief créer une partie
		void createPartie(const int niveau);
		/// \brief charger une partie depuis une sauvegarde
		void loadPartie();

		/// \brief suppression d'une partie
		inline void supprPartie(){
			delete _currentPartie;
			_currentPartie->reset();
			_currentPartie = nullptr;

			_menuVisibility = true;
		};

		/// \brief quitte le jeu en libérant la mémoire
		inline void deleteGame(){
			delete _assets;
			_assets = nullptr;

			if(_currentPartie!=nullptr){
				supprPartie();
			}

			delete _menu;
			_menu = nullptr;
		};

		/// \brief affichage du jeu dans la fenètre
		void draw(glm::mat4 ProjMatrix);

		/// \brief gestion des controles et des evènement sur la fenètre
		bool eventManager(SDL_Event& e);
};