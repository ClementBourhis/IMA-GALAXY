#pragma once

#include<iostream>
#include<vector>
#include<glimac/glm.hpp>

class Plateau {

private:
    glm::vec3 _position;
    glm::vec2 _texCoord;

public:

	Plateau(); 
	Plateau(const double radius);
	~Circle() = default;

	double surface() const override; 
    void draw() const override;
};