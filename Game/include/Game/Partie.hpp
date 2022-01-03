#pragma once

#include "Plateau.hpp"
#include "Camera.hpp"
#include "AssetsManager.hpp"

/**
 * \file Partie.hpp
 * \brief Déclaration de la classe Partie
 */
/**
 * \class Partie
 * \brief Génère un niveau de jeu qui selon la map pgm sélectionnée réorganise les éléments
 */

class Partie {
	private:
        //---attributs
        Plateau _map;
        const AssetsManager* _assets;   //tous les éléments du jeu
        Camera _camera;                 //reliée au personnage et à ses déplacements
        Personnage* _explorateur;       //Personnage que l'on va contrôler
        Skybox* _skybox;                //reliée à la caméra et à ses déplacements

        unsigned int _framerate;        //vitesse d'affichage
        unsigned int _niveau;           //numéro associé au niveau sélectioné

        unsigned int _direction;        //direction de déplacement (nord sud est ouest) entre 0 et 3, par défaut 0
        unsigned int _score;            //score en fonction des pièces ramassées

        bool _gameOver;

	public:
		//---constructeurs-/-destructeur
		Partie() = default;
        Partie(const std::string appPath, const unsigned int framerate, const AssetsManager* assetsPtr);
        Partie(const std::string appPath, const int niveau, const unsigned int framerate, const AssetsManager* assetsPtr);
		~Partie() = default;

		//---methodes
        void getInfosPlateau(); //retourne les infos du plateau utilisé dans la partie

        //initialisation de la position et de l'orientation de l'explorateur 
        void initExploParam();
        void initExploParam(unsigned int dir, float posX, float posZ);

        //initialise l'explorateur et la skybox
        void initAssets();

        //gestion de niveau
        void save(const std::string appPath) const;
        void load(const std::string appPath);
        void reset();

        //getter
        inline Plateau getMap(){
            return _map;
        }

        Camera getCamera(){
            return _camera;
        }
        inline const AssetsManager *assets() const{
            return _assets;
        }
        inline const unsigned int  &framerate() const{
            return _framerate;
        }

        inline const bool &gameOver() const{
            return _gameOver;
        }

        //setters
        void setCameraPos(const glm::vec3 pos){
            _camera.position() = pos;
        }

        void eventManager(SDL_Event& e);

        void draw(glm::mat4 ProjMatrix);

        void changeDirection(bool goud);
};