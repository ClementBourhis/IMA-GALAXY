#include <glimac/SDLWindowManager.hpp>

#include <GL/glew.h>
#include <iostream>
#include <vector>

#include <Mesh/Mesh.hpp>
#include <Game/Camera.hpp>

using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 600;

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
    /*CAMERA*/
    Camera camera;

    /*----------Vertex----------*/
    std::vector<ShapeVertex> vertices;
    vertices.push_back(ShapeVertex(glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(-0.5f, -0.5f, 0.f), glm::vec2(0.f, 1.f)));
    vertices.push_back(ShapeVertex(glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.5f, -0.5f, 0.f), glm::vec2(1.f, 1.f)));
    vertices.push_back(ShapeVertex(glm::vec3(0.f, 0.5f, 0.f), glm::vec3(0.5f, 0.5f, 0.f), glm::vec2(0.5f, 0.f)));

    std::vector<u_int32_t> indices;
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    /*----------SHADERS---------*/
    FilePath applicationPath(argv[0]); // chemin du programme
    FilePath vsPath = applicationPath.dirPath() + "shaders/camera.vs.glsl";
    FilePath fsPath = applicationPath.dirPath() + "shaders/camera.fs.glsl";

    ShaderManager shader(vsPath, fsPath);

    shader.addUniformVariable("uMVPMatrix");
    shader.addUniformVariable("uMVMatrix");
    shader.addUniformVariable("uNormalMatrix");
    shader.addUniformVariable("uTexture");

    /*----------Texture----------*/
    FilePath texturePath = applicationPath.dirPath()+"../../Temple_Run/Assets/textures/test/triforce.png";
    Texture texture(texturePath);

    texture.bind();
    shader.sendUniformInt("uTexture", 0);
    texture.debind();

    /*----------MESH----------*/
    Mesh triangle(vertices, indices);
    triangle.fillBuffers();

    //----Transfo
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, -100.f); 
    glm::mat4 MVMatrix = glm::mat4(1.f);

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            camera.controlManager(e);
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT);

        //-----DRAW-----
        triangle.bind();
        shader.use();
        texture.bind();

        shader.sendUniformMatrix4("uMVPMatrix", ProjMatrix * camera.getViewMatrix() * MVMatrix);
        shader.sendUniformMatrix4("uMVMatrix", camera.getViewMatrix() * MVMatrix);
        shader.sendUniformMatrix4("uNormalMatrix", (glm::transpose(glm::inverse(MVMatrix))));

        triangle.draw();
        texture.debind();
        triangle.debind();

        // Update the display
        windowManager.swapBuffers();
    }

    //-----LIBERATION MEMOIRE-----
    triangle.free();
    texture.free();

    return EXIT_SUCCESS;
}
