#pragma once

#include<iostream>
#include<string>
#include<vector>

#include "Case.hpp";

class Plateau {

private:
	//attributs
    /* ! Question ! */ std::string _name; //Nécessaire ??????????
    std::vector<Case> _cells; //tableau de cases

public:
	//constructeurs-/-destructeur
	Plateau(); 
	Plateau(std::string name);
	~Plateau() = default;

	//methodes
	void addCell(Case cell);
	/* ! Concepte ! */ void saveConfig();
	/* ! Concepte ! */ void loadConfig();
};