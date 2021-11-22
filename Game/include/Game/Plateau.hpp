#pragma once

#include<iostream>
#include<string>
#include<vector>

class Plateau {

private:
    std::string _name;
    std::vector _cells; //tableau de cases

public:

	Plateau(); 
	Plateau(std::string name, );
	~Circle() = default;

	double surface() const override; 
    void draw() const override;
};