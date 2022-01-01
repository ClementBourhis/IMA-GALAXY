#pragma once

#include "Plateau.hpp"
#include "Camera.hpp"
#include "AssetsManager.hpp"


class Partie {

	private:
        Plateau _map;
        const AssetsManager* _assets; //tous les éléments du jeu
        Camera _camera; //reliée au personnage et à ses déplacements
        Personnage* _explorateur;
        Skybox* _skybox; //reliée à la caméra et à ses déplacements

        unsigned int _framerate;
        unsigned int _niveau;

        unsigned int _direction; //direction de déplacement (nord sud est ouest) entre 0 et 3, par défaut 0
        //unsigned int _score; //score en fonction des pièces ramassées

	public:
		//constructeurs-/-destructeur
		Partie() = default;
        Partie(const std::string appPath, const int niveau, const unsigned int framerate, const AssetsManager* assetsPtr);
		~Partie() = default;

		//methodes
        //void savePartie() const;
        void renderParcours();
        void getInfosPlateau();

        inline Plateau getMap(){
            return _map;
        }

        //getter
        Camera getCamera(){
            return _camera;
        }
        inline const AssetsManager *assets() const{
            return _assets;
        }
        inline const unsigned int  &framerate() const{
            return _framerate;
        }
        //setters
        void setCameraPos(const glm::vec3 pos){
            _camera.position() = pos;
        }

        void eventManager(SDL_Event& e);

        void draw(glm::mat4 ProjMatrix);

        void changeDirection(bool goud);

};