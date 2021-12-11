#include <Game/Camera.hpp>

Camera::Camera()
    : _distance(-5.0f), _angleX(10.f), _angleY(0.f), _position(0.f, 0.f, 0.f), _cameraType(false), _maxAngle(40.f){
    computeDirectionVector();
}

void Camera::initialization(const float &distance, const float &angleY, const glm::vec3 &position, const float &maxAngle){
    _position = position;
    _distance = distance;
    rotateUp(angleY);
    _maxAngle = maxAngle;
}

void Camera::controlManager(const SDL_Event &e){
    switch(e.type){
        case SDL_MOUSEMOTION:
            if (!_cameraType && SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                if (e.motion.xrel != 0) {
                    rotateUp(e.motion.xrel / 1.5f);
                }
                if (e.motion.yrel != 0) {
                    rotateLeft(e.motion.yrel / 1.5f);
                }
                break;
            }

        case SDL_KEYDOWN:
            switch (e.key.keysym.sym){
                case SDLK_UP:
                    if(!_cameraType){
                        moveFront(0.5f);
                    }
                    break;

                case SDLK_DOWN:
                    if(!_cameraType){
                        moveFront(-0.5f);
                    }
                    break;
                
                case SDLK_c:
                    bool cameraType = false;
                    if(_cameraType == cameraType){
                        cameraType = true;
                    }
                    changeCameraType(cameraType);
                    break;
            }

        default:
            break;
    }

    if(e.button.button == SDL_BUTTON_WHEELUP){
        if(!_cameraType){
            moveFront(0.5f);
        }
    }

    if(e.button.button == SDL_BUTTON_WHEELDOWN){
        if(!_cameraType){
            moveFront(-0.5f);
        }
    }
}

void Camera::changeCameraType(bool type){
    _cameraType = type;
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
    _angleX+=degrees;
}

void Camera::rotateUp(float degrees){
    _angleY+=degrees;
}

glm::mat4 Camera::getViewMatrix(){
    glm::mat4 VM = glm::mat4(1.f);
    VM = glm::translate(VM, glm::vec3(0.0f, 0.0f, _distance));
    VM = glm::rotate(VM, glm::radians(_angleX), glm::vec3(1.0f, 0.0f, 0.0f));
    VM = glm::rotate(VM, glm::radians(_angleY), glm::vec3(0.0f, 1.0f, 0.0f));
    return VM;
}

//---Freefly
