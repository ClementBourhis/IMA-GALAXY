#pragma once

#include "AssetsManager.hpp"


class Menu {
	private:
        //---attribut
        const AssetsManager* _assets; //tous les éléments du jeu

	public:
		//---constructeurs-/-destructeur
		Menu() = default;
        Menu(const AssetsManager* assetsPtr)
        : _assets(assetsPtr)
        {};
		~Menu() = default;

		//---methodes
        void draw(){
            glDisable(GL_BLEND);
            _assets->element("menu")->draw();
        };
};