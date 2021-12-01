#include <Render/Texture.hpp>

Texture::Texture(FilePath path) 
: _path(path) {
    loadImage(_path);
}

Texture::~Texture(){
    glDeleteTextures(1, &_id);
}

void Texture::bind(){
    glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture::debind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadTexture(){
    //chargement de l'image
    _image = loadImage(_path);

    //!!!!!!!!!!!ETABLIR UN RETOUR ERREUR AVEC EXCEPTION !!!!!!!!!!!!
    if(_image == nullptr){
        std::cout << "Image non chargée ! Fichier non trouvé" << std::endl;
    }

    //génération de texture
    glGenTextures(1, &_id);
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _image->getWidth(), _image->getHeight(), 0, GL_RGBA, GL_FLOAT,(const char*) _image->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    debind();
}