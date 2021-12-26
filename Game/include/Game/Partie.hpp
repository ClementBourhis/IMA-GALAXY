#pragma once

//Json
#include <json/json.h> 

#include "Plateau.hpp"
#include "Camera.hpp"
#include "AssetsManager.hpp"


class Partie {

	private:
        Plateau _map;
        AssetsManager _assets; //tous les éléments du jeu, dont le personnage et la skybox
        Camera _camera; //reliée au personnage et à ses déplacements
        Element* _explorateur;
        Element* _skybox; //reliée à la caméra et à ses déplacements

        //config en fonction du niveau de difficulté
        std::map<std::string, float> _config;
        unsigned int _framerate = 24;
        unsigned int _niveau;

        unsigned int _direction; //direction de déplacement (nord sud est ouest) entre 0 et 3, par défaut 0
        //unsigned int _score; //score en fonction des pièces ramassées

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

        //getter
        Camera getCamera(){
            return _camera;
        }
        inline const AssetsManager &assets() const{
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
        void avancer();

        void loadConfig(const FilePath &configPath, const int niveau); //charger les données du fichier configurations.json

        void unloadPartie(){
            _assets.unloadAssets();
        }

};