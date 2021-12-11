#pragma once

#include "Plateau.hpp"
#include "Camera.hpp"

class Partie {

	private:
        Plateau _map;
        //Personnage _persoPrincipal;
        //std::vector<Enemy> _enemies; ??
        //config en fonction du niveau de difficulté
        Camera _camera; //reliée au personnage et à ses déplacements
        //skybox skybox; //reliée à la caméra et à ses déplacements

	public:
		//constructeurs-/-destructeur
		Partie() = default;
        Partie(const std::string appPath, const int niveau);
		~Partie() = default;

		//methodes
        //void savePartie() const;
        void renderParcours();
        void getInfosPlateau();

        inline Plateau getMap(){
            return _map;
        }

        
        Camera getCamera(){
            return _camera;
        }
        void setCameraEvent(SDL_Event& e);

        void eventManager(SDL_Event& e);

};