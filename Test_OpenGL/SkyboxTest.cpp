#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <Render/VBO.hpp>
#include <Render/IBO.hpp>
#include <Render/VAO.hpp>
#include <Game/Partie.hpp>
#include <Elements/Cube.hpp>
#include <Elements/Sol.hpp>


/* ***************************************************
Commandes pour compiler :

- aller dans le dossier Temple_Run
- cd ../build
- cmake ../Temple_Run
- make
- ./Test_OpenGL/Test_OpenGL_SkyboxTest 3D.vs.glsl normals.fs.glsl

*************************************************** */

using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    const int WINDOW_WIDTH = 2400;
    const int WINDOW_HEIGHT = 1800;
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
    //Temporaire, utilisation de shaders test
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/"+argv[1], applicationPath.dirPath() + "shaders/"+argv[2]);
    program.use();

    //VARIABLES UNIFORMES
    GLint locationMVP = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint locationMV = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint locationNormal = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    glEnable(GL_DEPTH_TEST);

    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), (float)(WINDOW_WIDTH)/(float)(WINDOW_HEIGHT), 0.1f, 100.f);
    glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, -5));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    glUniformMatrix4fv(locationMVP, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
    glUniformMatrix4fv(locationMV, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(locationNormal, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

    //on crée et on récupère les infos du plateau
    Partie partieTest("../Temple_Run/Game/Niveaux/", 1);
    partieTest.getInfosPlateau();

    //on crée un cube
    Cube skybox(1);

    //LE VBO
    /*GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    Cube skybox(1);
    skybox.getVerticesInfos();
    //Sphere sphere(1, 32, 16);
    //Sol sol(1);
    glBufferData(GL_ARRAY_BUFFER, skybox.getVertexCount()*sizeof(Vertex), skybox.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);*/

    VBO vbo;
    vbo.fillBuffer(skybox.getVertices());

    // L'IBO
    /*GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    // => On remplit l'IBO avec les indices:
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, skybox.getIndexCount() * sizeof(unsigned int), skybox.getIndexPointer(), GL_STATIC_DRAW);
    // => Comme d'habitude on debind avant de passer à autre chose
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/

    IBO ibo;
    ibo.fillBuffer(skybox.getIndices());

    //LE VAO
    /*GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXCOORDS = 2;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(const GLvoid*)offsetof(Vertex,position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(const GLvoid*)offsetof(Vertex,normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(const GLvoid*)offsetof(Vertex,texCoords));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);*/

    VAO vao;
    vao.fillBuffer(skybox.getVertices(), &vbo, &ibo);


    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glBindVertexArray(vao);
        vao.bind();

        glDrawElements(GL_TRIANGLES, skybox.getIndexCount(), GL_UNSIGNED_INT, 0);
        //glBindVertexArray(0);
        vao.debind();

        // Update the display
        windowManager.swapBuffers();
    }

    //la libération des ressources
    //glDeleteBuffers(1, &vbo);
    //glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}
