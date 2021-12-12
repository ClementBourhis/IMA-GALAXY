#include <Render/Texture.hpp>

//---Constructeur
Texture::Texture(FilePath path) 
: _path(path) {
    try{
        loadTexture();
    }
    catch (const std::exception &e){
        std::cerr << "Error : " << e.what() << std::endl;
    }
}

//---Destructeur
void Texture::free(){
    glDeleteTextures(1, &_id);
}

//---Méthodes
void Texture::bind(){
    glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture::debind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadTexture(){
    //chargement de l'image
    _image = loadImage(_path);

    //envoie d'une exeption si l'image n'est pas chargé
    if(_image == nullptr){
        throw std::ios_base::failure("Texture::loadTexture() : error : can't load file: " + (const std::string) _path);
    }

    //génération de l'objet texture
    glGenTextures(1, &_id);
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _image->getWidth(), _image->getHeight(), 0, GL_RGBA, GL_FLOAT,(const char*) _image->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    debind();
}