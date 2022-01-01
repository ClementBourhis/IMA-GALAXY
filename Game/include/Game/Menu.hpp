#pragma once

#include "AssetsManager.hpp"


class Menu {

	private:
        const AssetsManager* _assets; //tous les éléments du jeu

	public:
		//constructeurs-/-destructeur
		Menu() = default;
        Menu(const AssetsManager* assetsPtr)
        : _assets(assetsPtr)
        {};
		~Menu() = default;

		//methodes
        void eventManager(SDL_Event& e, unsigned int wwidth, unsigned int wheight);
        void draw(){
            glDisable(GL_BLEND);
            _assets->element("menu")->draw();
        };
};