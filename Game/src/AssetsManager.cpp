#include <Game/AssetsManager.hpp>

AssetsManager::AssetsManager(const FilePath &assetsPath)
    : _assetsPath(assetsPath+"/../Assets/assets.json"){
    loadAssets(_assetsPath);
}

AssetsManager::~AssetsManager(){
    unloadAssets();
}

//Initialisation
void AssetsManager::loadAssets(const FilePath &assetsPath){
    //---Use Json
    //on creer les outils qui vont permettre de lire le fichier Json
    std::ifstream assetsJSON(assetsPath, std::ifstream::binary);

    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errs;

    Json::parseFromStream(builder, assetsJSON, &root, &errs);

    //---Load assets
    loadShaders(root["shaders"]);
    loadTextures(root["textures"]);
    loadMeshs(root["meshs"]);
    loadElements(root["elements"]);
}

void AssetsManager::unloadAssets(){
    //unloadShaders(); --> double free, pas nécessaire
    unloadTextures();
    unloadMeshs();
    unloadElements();
}

//---Shaders
void AssetsManager::loadShaders(const Json::Value &data){
    if(!data)
        throw std::string("loadShaders : Data is missing");
    
    for(Json::Value const &value : data){
        try{
            loadShader(value);
        }
        catch(const std::exception &e){
            std::cerr << "Error :: loadShader(" << value["name"].asString() << ") : " << e.what() << std::endl;
        }
    };
}

void AssetsManager::loadShader(const Json::Value &data){
    //récupération des fichiers de shaders
    FilePath vs = _assetsPath.dirPath() + data["vs"].asString();
    FilePath fs = _assetsPath.dirPath() + data["fs"].asString();

    //création du program qui associe les 2 fichiers
    ShaderManager *shader = new ShaderManager(vs, fs);

    //ajoute les variables uniformes
    shader->addUniformVariable("uMVPMatrix");
    shader->addUniformVariable("uMVMatrix");
    shader->addUniformVariable("uNormalMatrix");
    shader->addUniformVariable("uTexture");

    //stock le program dans la map shaders de l'assetsmanager
    _shaders[data["name"].asString()] = shader;
}

void AssetsManager::unloadShaders(){
    for(const auto &it : _shaders){
        delete it.second;
    }
}


//---textures
void AssetsManager::loadTextures(const Json::Value &data){
    for(Json::Value const &value : data){
        try{
            loadTexture(value);
        }
        catch(const std::exception &e){
            std::cerr << "Error :: loadTexture(" << value["name"].asString() << ") : " << e.what() << std::endl;
        }
    }
}

void AssetsManager::loadTexture(const Json::Value &data){
    //on récupère l'emplacement de l'image
    FilePath image = _assetsPath.dirPath() + data["image"].asString();
    
    //On créer la texture
    Texture *texture = new Texture(image);

    //on stock la texture dans _textures
    _textures[data["name"].asString()] = texture;
}

void AssetsManager::unloadTextures(){
    for(const auto &it : _textures){
        it.second->free();
        //delete it.second; --> double free
    }
}


//---Mesh
void AssetsManager::loadMeshs(const Json::Value &data){
    for(Json::Value const &value : data){
        try{
            loadMesh(value);
        }
        catch(const std::exception &e){
            std::cerr << "Error :: loadMesh(" << value["name"].asString() << ") : " << e.what() << std::endl;
        }
    }
}

void AssetsManager::loadMesh(const Json::Value &data){
    //on récupère le type du mesh utilisé
    std::string meshType = data["type"].asString();

    //on créer le mesh en fonction de son type
    Mesh *mesh;
    if(meshType == "Cube"){
        if(data["size"]){
            mesh = new Cube(data["size"].asFloat()); 
        }
        else{
            mesh = new Cube();
        }
    }

    if(meshType == "Square"){
        if(data["size"]){
            mesh = new Square(data["size"].asFloat()); 
        }
        else{
            mesh = new Square();
        }
    }

    //on fillbuffer le mesh
    mesh->fillBuffers();

    //on stock le mesh dans le conteneur meshs
    _meshs[data["name"].asString()] = mesh;
}

void AssetsManager::unloadMeshs(){
    for(const auto &it : _meshs){
        it.second->free();
        //delete it.second; --> double free
    }
}


//---Element
void AssetsManager::loadElements(const Json::Value &data){
    for(const Json::Value &value : data){
        try{
            loadElement(value);
        }
        catch(const std::exception &e){
            std::cerr << "Error :: loadElement(" << value["name"].asString() << ") : " << e.what() << std::endl;
        }
    }
}

void AssetsManager::loadElement(const Json::Value &data){
    //on récupère les informations sur l'élement
    Mesh *mesh = _meshs.at(data["mesh"].asString());
    ShaderManager *shader = _shaders.at(data["shader"].asString());
    Texture *texture = _textures.at(data["texture"].asString());

    glm::vec3 position = glm::vec3(0.f,0.f,0.f);
    glm::vec3 size = glm::vec3(1.f,1.f,1.f);
    glm::vec3 rotation = glm::vec3(0.f,0.f,0.f);

    //si il existe des conditions spécifique de création d'élément
    if(data["position"]){
        position = glm::vec3(data["position"][0].asFloat(), data["position"][1].asFloat(), data["position"][2].asFloat());
    }

    if(data["size"]){
        size = glm::vec3(data["size"][0].asFloat(), data["size"][1].asFloat(), data["size"][2].asFloat());
    }

    if(data["rotation"]){
        rotation = glm::vec3(data["rotation"][0].asFloat(), data["rotation"][1].asFloat(), data["rotation"][2].asFloat());
    }

    //on créer l'élément en fonction de son type
    Element *element;
    if(data["type"]){
        std::string type = data["type"].asString();
        if(type == "Floor"){
            element = new Floor(mesh, shader, texture, position, size, rotation);
        }
        if(type == "Skybox"){
            element = new Skybox(mesh, shader, texture, position, size, rotation);
        }
        if(type == "Personnage"){
            element = new Personnage(mesh, shader, texture, position, size, rotation);
        }
    }
    else{
        element = new Element(mesh, shader, texture, position, size, rotation);
    }

    //on stock les éléments
    _elements[data["name"].asString()]=element;
}

void AssetsManager::unloadElements(){
    for(const auto &it : _elements){
        it.second->~Element();
    }
}

//---Getters
ShaderManager* AssetsManager::shader(const std::string &name) const{
    return _shaders.at(name);
}

Texture* AssetsManager::texture(const std::string &name) const{
    return _textures.at(name);
}

Mesh* AssetsManager::mesh(const std::string &name) const{
    return _meshs.at(name);
}

Element* AssetsManager::element(const std::string &name) const{
    return _elements.at(name);
}

std::map<std::string, Element*> AssetsManager::elements() const{
    return _elements;
}