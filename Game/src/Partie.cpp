#include <iostream>
#include <cassert>
#include <fstream>
#include <string>

#include <Game/Partie.hpp>
#include <Game/Plateau.hpp>

Partie::Partie(const std::string appPath, const unsigned int framerate, const AssetsManager* assetsPtr)
: _assets(assetsPtr), _framerate(framerate)
{
    load(appPath);
    const int niv = _niveau;
    _map = Plateau(appPath, niv);
    _camera = Camera(_direction);
    
    initAssets();
};

Partie::Partie(const std::string appPath, const int niveau, const unsigned int framerate, const AssetsManager* assetsPtr)
: _map(appPath, niveau), _assets(assetsPtr), _direction(0), _niveau(niveau), _framerate(framerate)
{
    initExploParam();
    initAssets();
};

void Partie::initExploParam(){
    _assets->element("explorateur")->rotation().y = glm::radians(180.f);
    _assets->element("explorateur")->position() = glm::vec3(0.f,0.5f,0.f);
}
void Partie::initExploParam(unsigned int dir, float posX, float posZ){
    _assets->element("explorateur")->rotation().y = glm::radians(180.f-(dir*90));
    _assets->element("explorateur")->position() = glm::vec3(posX,0.5f,posZ);
}

void Partie::initAssets(){
    //explorateur
    _explorateur = dynamic_cast<Personnage*>(_assets->element("explorateur"));
    _explorateur->vitesse() = static_cast<float>(_niveau) * (1000/static_cast<float>(_framerate)) / 1000;
    _explorateur->hauteur() = _explorateur->position().y;

    //skybox
    _skybox = dynamic_cast<Skybox*>(_assets->element("skybox"+std::to_string(_niveau)));
};

void Partie::getInfosPlateau(){
    _map.infosPlateau();
}

void Partie::eventManager(SDL_Event& e){
    //CAMERA
    _camera.controlManager(e);
    
    //Controles de Jeu
    switch(e.type){
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym){

                case SDLK_q:
                    _explorateur->turnLeft();
                    _camera.changeDirection(-90.f);
                    changeDirection(false);
                    break;
                
                case SDLK_d:
                    _explorateur->turnRight();
                    _camera.changeDirection(90.f);
                    changeDirection(true);
                    break;

                case SDLK_z:
                case SDLK_SPACE:
                    _explorateur->jumping() = true;
                    break;
                
            }

        default:
            break;
    }
}

//dessine tous les elements de la scene
void Partie::draw(glm::mat4 ProjMatrix) {
    //update position camera en fonction de la position de l'explorateur
    _camera.position() = _explorateur->position();
    //se mettre au niveau des yeux de l'explorateur
    _camera.translateEyes(_explorateur->size(), _direction);
    
    //----Skybox----
    _skybox->updatePosition(_camera.getPositionInScene());
    _skybox->draw(ProjMatrix, _camera.getViewMatrix(), false);

    //----Sol----
    for(const auto &it : _map.getCells()){
            _assets->element("floor")->update2DPosition(it.getPosition());
            _assets->element("floor")->draw(ProjMatrix, _camera.getViewMatrix(), true);
    }

    //----Pièces----
    for(const auto &it : _map.getPieces()){
            _assets->element("piece")->update2DPosition(it.getPosition());
            _assets->element("piece")->draw(ProjMatrix, _camera.getViewMatrix(), true);
    }
    //rotation des pièces
    _assets->element("piece")->rotate(glm::vec3(0,0,glm::radians(180 * (1000/static_cast<float>(_framerate))/1000)));

    //----Explorateur----
    _explorateur->jump();
    _explorateur->draw(ProjMatrix, _camera.getViewMatrix(), true);
    _explorateur->avancer(_direction);
}

void Partie::changeDirection(bool goud){ //gauche (0) ou droite (1)
    if(goud){
        if(_direction==3){
            _direction=0;
        }
        else{
            _direction++;
        }
    }
    else{
        if(_direction==0){
            _direction=3;
        }
        else{
            _direction--;
        }
    }
}

void Partie::save(const std::string appPath) const {
    std::string filename = appPath + "/../Assets/Niveaux/" + "sauvegarde.txt";
    std::ofstream file(filename);

    if(!file.is_open()){
        std::cerr << "error: can not create file: " << filename << std::endl;
    }

    //Niveau
    file << _niveau << std::endl;

    //Position
	file << _explorateur->position().x << " ";
    file << _explorateur->position().z << " ";
    file << std::endl;

    //Orientation de l'explorateur
    file << _direction << std::endl;

    //Score de la partie
    //file << _score << std::endl;
    
    file.close();
}

void Partie::load(const std::string appPath) {
    std::string filename = appPath + "/../Assets/Niveaux/" + "sauvegarde.txt";
    std::ifstream file(filename);

    if(!file.is_open()){
        std::cerr << "error: cannot find file: " << filename << std::endl;
        throw std::string("cannot find file load Partie");
    }

	// recup niveau
    unsigned int niveau;
	file >> niveau;
    _niveau = niveau;

    //recup position explorateur
    float posX;
    file >> posX;
    float posZ;
    file >> posZ;

    //recup direction explorateur
    unsigned int dir;
    file >> dir;
    _direction = dir;

    initExploParam(_direction, posX, posZ);
    
    file.close();
}