#pragma once

#include "AssetsManager.hpp"

//La classe Menu prend en charge l'affichage du menu
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