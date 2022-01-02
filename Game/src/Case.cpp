#include <Game/Case.hpp>

Case::Case(int x, int y, float hauteur)
: _position(glm::vec3(x,hauteur,y)){
};

//connaitre la position de la case
glm::vec3 Case::getPosition() const {
    return _position;
};

void Case::setPosition(int x,int y,int z){
    _position = glm::vec3(x,y,z);
};