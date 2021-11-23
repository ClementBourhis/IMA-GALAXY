#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

#include <glimac/glm.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>

#include <glimac/TrackballCamera.hpp>

using namespace glimac;

/*----------Structures----------*/
struct EarthProgram{
    /*-----DATA-----*/
    //on stock le programme
    Program m_program;

    //---stockage la location des variables uniformes---
    //les transformations
    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;

    //les textures
    GLint uEarthTexture;
    GLint uCloudTexture;


    /*-----Constructeur-----*/
    EarthProgram(const FilePath& applicationPath) :
        m_program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/multiText3D.fs.glsl"))
        {
            uMVPMatrix = glGetUniformLocation(m_program.getGLId(), "uMVPMatrix");
            uMVMatrix = glGetUniformLocation(m_program.getGLId(), "uMVMatrix");
            uNormalMatrix = glGetUniformLocation(m_program.getGLId(), "uNormalMatrix");
            uEarthTexture = glGetUniformLocation(m_program.getGLId(), "uTexture");
            uCloudTexture = glGetUniformLocation(m_program.getGLId(), "uTexture2");
        }
};

struct MoonProgram{
    /*-----DATA-----*/
    //on stock le programme
    Program m_program;

    //---stockage la location des variables uniformes---
    //les transformations
    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;

    //la texture
    GLint uTexture;


    /*-----Constructeur-----*/
    MoonProgram(const FilePath& applicationPath) :
        m_program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/text3D.fs.glsl"))
        {
            uMVPMatrix = glGetUniformLocation(m_program.getGLId(), "uMVPMatrix");
            uMVMatrix = glGetUniformLocation(m_program.getGLId(), "uMVMatrix");
            uNormalMatrix = glGetUniformLocation(m_program.getGLId(), "uNormalMatrix");
            uTexture = glGetUniformLocation(m_program.getGLId(), "uTexture");
        }
};


int main(int argc, char** argv) {
    //-----Create camera-----
    TrackballCamera camera;

    // Initialize SDL and open a window
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    /*----------Création des programs----------*/
    //grâce aux strucs on peut spécifier quel shaders vont être utilisé pour chaques programmes
    FilePath applicationPath = argv[0];
    EarthProgram earthProgram(applicationPath);
    MoonProgram moonProgram(applicationPath);


    /*----------Chargement des textures----------*/
    std::unique_ptr<Image> imageEarth = loadImage("/home/clement/Bureau/SI2/GLImac-Template/assets/textures/EarthMap.jpg");
    if(imageEarth == NULL){std::cout<<"Texture non chargé !!! : EarthMap"<<std::endl;}

    std::unique_ptr<Image> imageMoon = loadImage("/home/clement/Bureau/SI2/GLImac-Template/assets/textures/MoonMap.jpg");
    if(imageMoon == NULL){std::cout<<"Texture non chargé !!! : MoonMap"<<std::endl;}

    std::unique_ptr<Image> imageCloud = loadImage("/home/clement/Bureau/SI2/GLImac-Template/assets/textures/CloudMap.jpg");
    if(imageCloud == NULL){std::cout<<"Texture non chargé !!! : CloudMap"<<std::endl;}


    /*----------Construction Sphere----------*/
    Sphere sphere(1, 32, 16);
    int NbVertex = sphere.getVertexCount();

    //on tire 32 rotation aléatoire pour les 32 lunes
    const unsigned int NB_LUNES = 5;
    std::vector<glm::vec3> randomRotAxes;
    std::vector<glm::vec3> randomTranslate;
    for (size_t i = 0; i < NB_LUNES; i++){
        randomRotAxes.push_back(glm::sphericalRand(0.5f));
        randomTranslate.push_back(glm::sphericalRand(2.f));
    }


    /*----------VBO----------*/    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //on a déja notre tableau de vertex avec le getDataPointer()
    glBufferData(GL_ARRAY_BUFFER, NbVertex*sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    /*----------VAO----------*/
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXTURE = 2;

    //transfert des info vers le vao
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //active les attributs
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*) (offsetof(ShapeVertex, position)));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*) (offsetof(ShapeVertex, normal)));
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*) (offsetof(ShapeVertex, texCoords)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


    /*----------Génération des textures----------*/
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageEarth->getWidth(), imageEarth->getHeight(), 0, GL_RGBA, GL_FLOAT,(const char*) imageEarth->getPixels());

    //paramètre
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    //création d'un deuxieme texture object
    GLuint textureId2;
    glGenTextures(1, &textureId2);
    glBindTexture(GL_TEXTURE_2D, textureId2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageCloud->getWidth(), imageCloud->getHeight(), 0, GL_RGBA, GL_FLOAT,(const char*) imageCloud->getPixels());

    //paramètre
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);


    /*----------Activation du test de profondeur du GPU---------*/
    glEnable(GL_DEPTH_TEST);


    /*----------Variable pour la souris----------*/
    float speed = 1.f;
    float cx = 0;
    float cy = 0;


    // Application loop:
    bool done = false;
    while(!done) {
        //Get ViewMatrix
        glm::mat4 viewMatrix = camera.getViewMatrix();

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }

            if(windowManager.isKeyPressed(SDLK_q)){
                camera.rotateLeft(2.f);
            }

            if(windowManager.isKeyPressed(SDLK_d)){
                camera.rotateLeft(-2.f);
            }

            if(windowManager.isKeyPressed(SDLK_SPACE)){
                camera.rotateUp(2.f);
            }

            if(windowManager.isKeyPressed(SDLK_LSHIFT)){
                camera.rotateUp(-2.f);
            }

            if(windowManager.isKeyPressed(SDLK_z)){
                camera.moveFront(2.f);
            }  

            if(windowManager.isKeyPressed(SDLK_s)){
                camera.moveFront(-2.f);
            }

            if(windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)){
                if(cx < windowManager.getMousePosition().x){
                    camera.rotateLeft(speed);
                }
                else{
                    camera.rotateLeft(-speed);
                }
                cx = windowManager.getMousePosition().x;

                if(cy < windowManager.getMousePosition().y){
                    camera.rotateUp(speed);
                }
                else{
                    camera.rotateUp(-speed);
                }
                cy = windowManager.getMousePosition().y;
            }

            if(windowManager.isKeyPressed(SDLK_m)){
                std::cout << "ViewMatrix : " << viewMatrix << std::endl;
                std::cout << "La base : " << glm::translate(glm::mat4(1), glm::vec3(0, 0, -5)) << std::endl;
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        /*----------Nettoyage---------*/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /*----------Dessin----------*/
        glBindVertexArray(vao);

        //-----------La Terre
        earthProgram.m_program.use(); //lancé le prog pour la terre

        //-----Textures
        glUniform1i(earthProgram.uEarthTexture, 0); //associe la texture terre à la texture 0
        glUniform1i(earthProgram.uCloudTexture, 1); //associe la texture nuage à la texture 1

        //activation des textures
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureId2);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageEarth->getWidth(), imageEarth->getHeight(), 0, GL_RGBA, GL_FLOAT,(const char*) imageEarth->getPixels());

        //-----Matrices de transfo
        //Création des matrices de transformation
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, -100.f); 
        glm::mat4 MVMatrix = viewMatrix;
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        //transformation suplémentaire
        //MVMatrix = glm::rotate(MVMatrix, -windowManager.getTime()*0.5f, glm::vec3(0, 1, 0));

        //envoie des matrices au shader
        glUniformMatrix4fv(earthProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(earthProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(earthProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        glDrawArrays(GL_TRIANGLES, 0, NbVertex);

        //-----------Les Lunes
        moonProgram.m_program.use();

        //-----Textures        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageMoon->getWidth(), imageMoon->getHeight(), 0, GL_RGBA, GL_FLOAT,(const char*) imageMoon->getPixels());
        glUniform1i(moonProgram.uTexture, 0);

        //-----Matrices de transfo
        //Création des matrices de transformation
        for(int i = 0; i<NB_LUNES; i++){
            //transformation suplémentaire
            glm::mat4 MoonMVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), randomRotAxes[i]);            
            MoonMVMatrix = MoonMVMatrix * glm::translate(glm::mat4(1), randomTranslate[i]);
            MoonMVMatrix = glm::scale(MoonMVMatrix, glm::vec3(0.2, 0.2, 0.2));

            //envoie des matrices au shader
            ProjMatrix = glm::perspective(glm::radians(70.f), WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, -100.f); 
            NormalMatrix = glm::transpose(glm::inverse(MoonMVMatrix));

            glUniformMatrix4fv(moonProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MoonMVMatrix));
            glUniformMatrix4fv(moonProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MoonMVMatrix));
            glUniformMatrix4fv(moonProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

            glDrawArrays(GL_TRIANGLES, 0, NbVertex);
        }
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);


        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteTextures(1, &textureId);
    glDeleteTextures(1, &textureId2);

    return EXIT_SUCCESS;
}
