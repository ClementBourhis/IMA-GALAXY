#include <Game/Camera.hpp>

Camera::Camera()
    : _distance(-5.0f), _angleX(180.f), _angleY(25.f), _position(0.f, 1.f, 0.f), _cameraType(false), _maxAngle(40.f), _phi(0), _theta(0), _blocked(false), _angleDir(0) {
    computeDirectionVectors();
}

void Camera::initialization(const float &distance, const float &angleY, const float &angleX, const glm::vec3 &position, const float &maxAngle){
    _position = position;
    _distance = distance;
    rotateUp(angleY);
    //rotateLeft(angleX);
    _maxAngle = maxAngle;
} //on utilise pas cette fonction ?

void Camera::controlManager(const SDL_Event &e){
    switch(e.type){
        case SDL_MOUSEMOTION:
            if (!_blocked && SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                if (e.motion.xrel != 0) {
                    rotateLeft(e.motion.xrel / 1.5f);
                }
                if (e.motion.yrel != 0) {
                    rotateUp(e.motion.yrel / 1.5f);
                }
                break;
            }

        case SDL_KEYDOWN:
            switch (e.key.keysym.sym){
                case SDLK_UP:
                    if(!_cameraType && !_blocked){
                        moveFront(0.5f);
                    }
                    break;

                case SDLK_DOWN:
                    if(!_cameraType && !_blocked){
                        moveFront(-0.5f);
                    }
                    break;

                case SDLK_l:
                    changeBlock();
                    break;
                
                case SDLK_c:
                    if(!_blocked){
                        bool cameraType = false;
                        if(_cameraType == cameraType){
                            cameraType = true;
                        }
                        changeCameraType(cameraType);
                    }
                    break;
                
            }

        default:
            break;
    }

    if(e.button.button == SDL_BUTTON_WHEELUP){
        if(!_cameraType && !_blocked){
            moveFront(0.5f);
        }
    }

    if(e.button.button == SDL_BUTTON_WHEELDOWN){
        if(!_cameraType && !_blocked){
            moveFront(-0.5f);
        }
    }
}

void Camera::changeCameraType(bool type){
    _cameraType = type;
}

void Camera::changeBlock(){
    if(_blocked)
        _blocked = false;
    else
        _blocked = true;
}

//---TrackBall
void Camera::setPosition(const glm::vec3 &position){
    _position = position;
}

void Camera::moveFront(float delta) {
    if(_distance+delta<=0){
        _distance+=delta;
    }
}

void Camera::rotateLeft(float degrees){
    if(_cameraType){
        if(_phi+(degrees*0.01) >= glm::radians(_angleDir-_maxAngle) && _phi+(degrees*0.01) <= glm::radians(_angleDir+_maxAngle)){
            _phi+=degrees*0.01;
            computeDirectionVectors();
        }
        
    }
    else{
        _angleX+=degrees;
    }
}

void Camera::changeDirection(float degrees){
    _angleDir-=degrees;
    //freefly
    _phi-=glm::radians(degrees);
    computeDirectionVectors();

    //trackball
    _angleX+=degrees;
}

void Camera::rotateUp(float degrees){
    if(_cameraType){
        if(_theta+(degrees*0.01) >= glm::radians(-_maxAngle) && _theta+(degrees*0.01) <= glm::radians(_maxAngle)){
            _theta+=degrees*0.01;
            computeDirectionVectors();
        }
    }
    else{
        if(_angleY+degrees>=-90.f && _angleY+degrees<=90.f){ // on met les contraintes pour ne pas aller à l'envers
            _angleY+=degrees;
        }
    }
}

glm::mat4 Camera::getViewMatrix(){
    if(_cameraType){
        return glm::lookAt(_position, _position+_frontVector, _upVector);
    }
    else{
        glm::mat4 VM = glm::mat4(1.f);
        VM = glm::translate(VM, glm::vec3(0.0f, 0.0f, _distance));
        VM = glm::rotate(VM, glm::radians(_angleY), glm::vec3(1.0f, 0.0f, 0.0f));
        VM = glm::rotate(VM, glm::radians(_angleX), glm::vec3(0.0f, 1.0f, 0.0f));
        VM = glm::translate(VM, -_position);
        return VM;
    }
}


void Camera::update(){
    //update la position en fonction de l'explorateur
}
