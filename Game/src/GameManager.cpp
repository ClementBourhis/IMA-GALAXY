#include <Game/GameManager.hpp>

GameManager::GameManager(const std::string appPath)
:_appPath(appPath)
{
    _assets = new AssetsManager(_appPath);
    _menu = new Menu(_assets);
}

void GameManager::makeFullscreen(){
    const SDL_VideoInfo *videoInfo;
    videoInfo = SDL_GetVideoInfo();

    _windowWidth = videoInfo->current_w;
    _windowHeight = videoInfo->current_h;
}

void GameManager::createPartie(const int niveau){
    _currentPartie = new Partie(_appPath, niveau, _framerate, _assets);
}

void GameManager::draw(glm::mat4 ProjMatrix){
    if(_currentPartie){
        glEnable(GL_BLEND); //activation de la transparence
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
        _currentPartie->draw(ProjMatrix);
    }
    else{
        glDisable(GL_BLEND);  //désactivation de la transparence
        _menu->draw();
    }
}

void GameManager::eventManager(SDL_Event& e){
    if(_currentPartie){
        _currentPartie->eventManager(e);

        //TEST QUAND ON PERD
        switch(e.type){
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym){
                    case SDLK_p:
                        supprPartie();
                        break;
                }

            default:
                break;
        }
    }
    else{
        //MENU
        //_menu->eventManager(e, _windowWidth, _windowHeight);
        if (e.type == SDL_MOUSEBUTTONDOWN){
            if (e.button.button == SDL_BUTTON_LEFT){
                std::cout << "(" << e.button.x << "," << e.button.y << ")" << std::endl;
                if (e.button.x > 0.2*_windowWidth && e.button.x < 0.39*_windowWidth && e.button.y > 0.7*_windowHeight && e.button.y < 0.83*_windowHeight){
                    //QUIT
                    //done = true;
                }
                else if (e.button.x > 0.2*_windowWidth && e.button.x < 0.39*_windowWidth && e.button.y > 0.39*_windowHeight && e.button.y < 0.57*_windowHeight){
                    std::cout << "PLAY ! Level 1 ! Game Begin ! " << std::endl;
                    createPartie(1);
                }
                else if (e.button.x > 0.6*_windowWidth && e.button.x < 0.93*_windowWidth && e.button.y > 0.39*_windowHeight && e.button.y < 0.57*_windowHeight){
                    std::cout << "PLAY ! Level 2 ! Game Begin ! " << std::endl;
                    createPartie(2);
                }
            }
        }

      //Traitement d'evenements :
        switch (e.type){
            //Touche clavier
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym){
                    case SDLK_SPACE:
                        std::cout << "PLAY ! " << std::endl;
                        createPartie(1);
                        break;

                    default:
                    break;
                }
        }
    }
}