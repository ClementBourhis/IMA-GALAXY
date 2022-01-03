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
        const AssetsManager* _assets;   /*!< tous les éléments du jeu  */
        Camera _camera;                 /*!< reliée au personnage et à ses déplacements */
        Personnage* _explorateur;       /*!< Personnage que l'on va contrôler */
        Skybox* _skybox;                /*!< reliée à la caméra et à ses déplacements */

        unsigned int _framerate;        /*!< vitesse d'affichage */
        unsigned int _niveau;           /*!< numéro associé au niveau sélectioné */

        unsigned int _direction;        /*!< direction de déplacement (nord sud est ouest) entre 0 et 3, par défaut 0 */
        unsigned int _score;            /*!< score en fonction des pièces ramassées */

        bool _gameOver;

	public:
		//---constructeurs-/-destructeur
		Partie() = default;
        Partie(const std::string appPath, const unsigned int framerate, const AssetsManager* assetsPtr);
        Partie(const std::string appPath, const int niveau, const unsigned int framerate, const AssetsManager* assetsPtr);
		~Partie() = default;

		//---methodes
        void getInfosPlateau(); //retourne les infos du plateau utilisé dans la partie

        /// \brief initialisation de la position et de l'orientation de l'explorateur, avec al direction et la position à 0 par défaut (la première fois qu'on lance une partie par exemple)
        void initExploParam();
        /// \brief surcharge de l'initialisation de la position et de l'orientation de l'explorateur, lorsque la partie créée est construite à partir d'une partie sauvegardée
        void initExploParam(unsigned int dir, float posX, float posZ);

        /// \brief initialise l'explorateur et la skybox
        void initAssets();

        /// \brief sauvegarde de niveau
        void save(const std::string appPath) const;
        /// \brief chargement d'un niveau sauvergardé
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

        /// \brief controle des événements de la partie
        void eventManager(SDL_Event& e);

        void draw(glm::mat4 ProjMatrix);

        void changeDirection(bool goud);
};