#include <Game/GameManager.hpp>

GameManager::GameManager(const std::string appPath)
:_appPath(appPath), _menuVisibility(true)
{
    _assets = new AssetsManager(_appPath);
    _menu = new Menu(_assets);
}

void GameManager::makeFullscreen(){
    const SDL_VideoInfo *videoInfo;
    videoInfo = SDL_GetVideoInfo();

    _windowWidth = videoInfo->current_w;
    _windowHeight = videoInfo->current_h;
    _assets->element("menu")->size() = glm::vec3(_windowWidth, _windowHeight, 0);
}

void GameManager::createPartie(const int niveau){
    if(_currentPartie!=nullptr){
		supprPartie();
	}
    _menuVisibility = false;
    _currentPartie = new Partie(_appPath, niveau, _framerate, _assets);
}

void GameManager::loadPartie(){
    if(_currentPartie!=nullptr){
		supprPartie();
	}
    _currentPartie = new Partie(_appPath, _framerate, _assets);
    _menuVisibility = false; //(on place le changement de visibilité après au cas où le chargement de partie ne marche pas)
}

void GameManager::draw(glm::mat4 ProjMatrix){
    if(_menuVisibility){
        glDisable(GL_BLEND);  //désactivation de la transparence
        _menu->draw();
    }
    else{
        if(_currentPartie){ //si il y a bien une partie en cours
            glEnable(GL_BLEND); //activation de la transparence
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
            _currentPartie->draw(ProjMatrix);
        }
    }
}

bool GameManager::eventManager(SDL_Event& e){
    bool done = false; 

    if(_menuVisibility){
        //====== MENU ======
        switch (e.type){
            //Touche clavier
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym){
                    case SDLK_SPACE:
                        std::cout << "PLAY ! " << std::endl;
                        createPartie(1);
                        break;

                    case SDLK_DELETE:
                        done = true;
                        break;

                    default:
                    break;
                }
                break;
            
            //Clic souris
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT){
                    std::cout << "(" << e.button.x << "," << e.button.y << ")" << std::endl;
                    if (e.button.x > 0.2*_windowWidth && e.button.x < 0.39*_windowWidth && e.button.y > 0.7*_windowHeight && e.button.y < 0.83*_windowHeight){
                        //QUIT
                        done = true;
                    }
                    else if (e.button.x > 0.2*_windowWidth && e.button.x < 0.39*_windowWidth && e.button.y > 0.39*_windowHeight && e.button.y < 0.57*_windowHeight){
                        std::cout << "PLAY ! Level 1 ! Game Begin ! " << std::endl;
                        createPartie(1);
                    }
                    else if (e.button.x > 0.6*_windowWidth && e.button.x < 0.93*_windowWidth && e.button.y > 0.39*_windowHeight && e.button.y < 0.57*_windowHeight){
                        std::cout << "PLAY ! Level 2 ! Game Begin ! " << std::endl;
                        createPartie(2);
                    }
                    else if (e.button.x > 0.6*_windowWidth && e.button.x < 0.93*_windowWidth && e.button.y > 0.7*_windowHeight && e.button.y < 0.83*_windowHeight){
                        try{
                            loadPartie();
                            std::cout << "Chargement de la partie sauvegardé " << std::endl;
                        }
                        catch(const std::string &e){
                            //si le chargement de la partie ne fonctionne pas, on ne fait rien
                        }
                        
                    }
                }
            break;
        }
        
    }
    else if(!_menuVisibility && _currentPartie){ //si le menu n'est pas visible et qu'il y a une partie en cours
        _currentPartie->eventManager(e);

        switch(e.type){
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym){                  
                    //TEST QUAND ON PERD
                    case SDLK_p:
                        supprPartie();
                        break;
                }
            default:
                break;
        }
    }


    if(_currentPartie){ //si il y a une partie en cours, on peut mettre le jeu en pause et voir le menu
        switch(e.type){
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym){
                    case SDLK_ESCAPE:
                        _menuVisibility ? _menuVisibility = false : _menuVisibility = true; //toggle le menu
                        break;

                    //test pour sauvegarde de la partie
                    case SDLK_u:
                        _currentPartie->save(_appPath);
                        break;
                }
            default:
                break;
        }
    }

    return done;
}