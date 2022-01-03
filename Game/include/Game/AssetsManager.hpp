#pragma once

//STL
#include <map>      //std::map
#include <string>   //std::string
#include <iostream> //std::ostream
#include <stdexcept>//std::error
#include <fstream>  //std::iftream::binary

//Json
#include <json/json.h>  //Json::Value

//glimac
#include <glimac/FilePath.hpp>

//Render
#include <Render/ShaderManager.hpp>
#include <Render/Texture.hpp>

//Mesh
#include <Mesh/Mesh.hpp>
#include <Mesh/Cube.hpp>
#include <Mesh/Square.hpp>
#include <Mesh/MenuMesh.hpp>

//Elements
#include <Elements/Element.hpp>
#include <Elements/Floor.hpp>
#include <Elements/Skybox.hpp>
#include <Elements/Personnage.hpp>

//L'assets Manager s'occupe de charger/créer tous les assets (Shader, Texture, Mesh, Element) pour ensuite nous les utilisions
class AssetsManager{
    private :
        //---attributs
        //Stockage de chaque pointeur vers les objets qui vont nous servir
        FilePath _assetsPath;
        std::map<std::string, ShaderManager*> _shaders;
        std::map<std::string, Texture*> _textures;
        std::map<std::string, Mesh*> _meshs;
        std::map<std::string, Element*> _elements;

    public :
        //---constructeur
        AssetsManager(const FilePath &assetsPath);  //récupère tous les éléments depuis un fichier Json

        //---destructeur
        ~AssetsManager();                           //libère la mémoire

        //---méthodes
        //Initialisation
        void loadAssets(const FilePath &assetsPath);
        void unloadAssets();

        //-Pour tout les assets on va avoir une méthode load pour le charger, et une méthode unload pour libérer la mémoire
        //Shaders
        void loadShaders(const Json::Value &data);
        void loadShader(const Json::Value &data);
        void unloadShaders();

        //Textures
        void loadTextures(const Json::Value &data);
        void loadTexture(const Json::Value &data);
        void unloadTextures();

        //Meshs
        void loadMeshs(const Json::Value &data);
        void loadMesh(const Json::Value &data);
        void unloadMeshs();

        //Elements
        void loadElements(const Json::Value &data);
        void loadElement(const Json::Value &data);
        void unloadElements();

        //Getters
        //on récupère un asset de la liste via son "name"
        ShaderManager *shader(const std::string &name) const;
        Texture *texture(const std::string &name) const;
        Mesh *mesh(const std::string &name) const;
        Element *element(const std::string &name) const;

        //pour reset les éléments dans Partie, on récupère la liste entière
        std::map<std::string, Element*> elements() const;


        //Affichage
        friend std::ostream &operator<<(std::ostream &os, const AssetsManager &assets){
            os << "-Shaders :\n";
            if(assets._shaders.size() > 0){
                int i = 0;
                for(const auto &it : assets._shaders){
                    os << "     ["<<i<<"] --> program '" << it.first << "'\n";
                    i++;
                }
                os << "     nb programs : " << i << "\n";
            }
            else{
                os << " empty\n";
            }

            os << "-Textures :\n";
            if(assets._textures.size() > 0){
                int i = 0;
                for(const auto &it : assets._textures){
                    os << "     ["<<i<<"] --> '" << it.first << "' :: " << *it.second;
                    i++;
                }
                os << "     nb textures : " << i << "\n";
            }
            else{
                os << " empty\n";
            }

            os << "-Meshs :\n";
            if(assets._meshs.size() > 0){
                int i = 0;
                for(const auto &it : assets._meshs){
                    os << "     ["<<i<<"] --> '" << it.first << "' :: " << it.second->type() << "\n";
                    i++;
                }
                os << "     nb meshs : " << i << "\n";
            }
            else{
                os << " empty\n";
            }

            os << "-Elements :\n";
            if(assets._elements.size() > 0){
                int i = 0;
                for(const auto &it : assets._elements){
                    os << "     ["<<i<<"] --> '" << it.first << "' :: " << it.second->type() << "\n";
                    i++;
                }
                os << "     nb elements : " << i << "\n";
            }
            else{
                os << " empty\n";
            }
            return os;
        }
};