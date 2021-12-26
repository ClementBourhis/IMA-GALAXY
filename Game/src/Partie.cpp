#include <iostream>
#include <cassert>
#include <fstream>
#include <string>

#include <Game/Partie.hpp>
#include <Game/Plateau.hpp>

Partie::Partie(const std::string appPath, const int niveau)
: _map(appPath, niveau), _assets(appPath), _direction(0), _niveau(niveau)
{
    //loadConfig(appPath+"/../Assets/Niveaux/Configurations.json", niveau);
    _explorateur = _assets.element("explorateur");
    _skybox = _assets.element("skybox"+std::to_string(niveau));

};

void Partie::getInfosPlateau(){
    _map.infosPlateau();
}

void Partie::eventManager(SDL_Event& e){
    //CAMERA
    _camera.controlManager(e);

    //PERSONNAGE
    //_explorateur->controlManager(e);
    
    switch(e.type){
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym){

                case SDLK_q:
                    //_explorateur->turnLeft();
                    _explorateur->rotate(glm::vec3(0,glm::radians(90.f),0));
                    _camera.changeDirection(-90.f);
                    changeDirection(false);
                    break;
                
                case SDLK_d:
                    _explorateur->rotate(glm::vec3(0,glm::radians(-90.f),0));
                    _camera.changeDirection(90.f);
                    changeDirection(true);
                    break;

                case SDLK_z:
                    //_explorateur->jump();
                    _explorateur->translate(glm::vec3(0,0.5,0));
                    break;

                /*case SDLK_s:
                    //_explorateur->glide();
                    break;*/
                
            }

        default:
            break;
    }
}

//dessine tous les elements de la scene
void Partie::draw(glm::mat4 ProjMatrix) {
    //update position camera en fonction de la position de l'explorateur
    _camera.position() = _explorateur->position();
    //_camera.position().z = _explorateur->position().z + (_explorateur->size().z/2);
    _camera.position().y = _explorateur->position().y + _explorateur->size().y/2;
    

    _skybox->updatePosition(_camera.getPositionInScene());
    _skybox->draw(ProjMatrix, _camera.getViewMatrix(), false);

    for(const auto &it : _map.getCells()){
            _assets.element("floor")->updatePosition(it.getPosition());
            _assets.element("floor")->draw(ProjMatrix, _camera.getViewMatrix());
    }

    _explorateur->draw(ProjMatrix, _camera.getViewMatrix());
    avancer();
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

void Partie::avancer(){
    float speed = _niveau; //en bloc par seconde
    float avancement = speed * (1000/_framerate) / 1000;
    switch (_direction){
        case 0:
            _explorateur->translate(glm::vec3(0,0,avancement));
            break;
        
        case 1:
            _explorateur->translate(glm::vec3(-avancement,0,0));
            break;

        case 2:
            _explorateur->translate(glm::vec3(0,0,-avancement));
            break;

        case 3:
            _explorateur->translate(glm::vec3(avancement,0,0));
            break;
    }
}

void Partie::loadConfig(const FilePath &configPath, const int niveau){
    //---Use Json
    std::ifstream configJSON(configPath, std::ifstream::binary);

    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errs;

    Json::parseFromStream(builder, configJSON, &root, &errs);
    
    const Json::Value data = root["niveaux"];
    if(!data)
        throw std::string("loadConfig : Data is missing");

    for(Json::Value const &value : data){
        try{
            _config["vitessePerso"] = value.asFloat();
        }
        catch(const std::exception &e){
            std::cerr << "Error :: loadConfig(" << value["vitessePerso"].asString() << ") : " << e.what() << std::endl;
        }
    }
}