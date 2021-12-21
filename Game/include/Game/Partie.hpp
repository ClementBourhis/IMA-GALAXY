#pragma once

#include "Plateau.hpp"
#include "Camera.hpp"

//Elements 
#include <Elements/Skybox.hpp>

class Partie {

	private:
        Plateau _map;
        //Personnage* _persoPrincipal;
        //AssetManager _assets; //tous les éléments du jeu, dont le personnage et la skybox
        //config en fonction du niveau de difficulté
        Camera _camera; //reliée au personnage et à ses déplacements
        //Skybox* _skybox(); //reliée à la caméra et à ses déplacements

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

        void eventManager(SDL_Event& e);

        void draw();

};