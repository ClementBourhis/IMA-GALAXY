#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <vector>

#include <Render/VBO.hpp>
#include <Render/VAO.hpp>

using namespace glimac;

struct Vertex3D{
    //attributs
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;

    //constructeurs
    Vertex3D();
    Vertex3D(glm::vec3 _position, glm::vec3 _normal, glm::vec2 _texCoords);
};

//Constructeurs
Vertex3D::Vertex3D()
    : position(glm::vec3(0.f, 0.f, 0.f)), normal(glm::vec3(0.f,0.f,0.f)), texCoords(glm::vec2(0.f,0.f)){
};

Vertex3D::Vertex3D(glm::vec3 _position, glm::vec3 _normal, glm::vec2 _texCoords)
    : position(_position), normal(_normal), texCoords(_texCoords){
};


int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

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

    /*----------Vertex----------*/
    std::vector<Vertex3D> vertices;
    vertices.push_back(Vertex3D(glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(-0.5f, -0.5f, 0.f), glm::vec2(0.f, 0.f)));
    vertices.push_back(Vertex3D(glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.5f, -0.5f, 0.f), glm::vec2(0.f, 0.f)));
    vertices.push_back(Vertex3D(glm::vec3(0.f, 0.5f, 0.f), glm::vec3(0.f, 0.5f, 0.f), glm::vec2(0.f, 0.f)));

    /*----------VBO----------*/
    VBO vbo;
    vbo.fillBuffer(vertices);

    /*----------VAO----------*/
    VAO vao;
    vao.fillBuffer(vertices, &vbo);


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

        glClear(GL_COLOR_BUFFER_BIT);

        //-----DRAW-----
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        vao.debind();

        // Update the display
        windowManager.swapBuffers();
    }

    //-----LIBERATION MEMOIRE-----
    vbo.~VBO();
    vao.~VAO();

    return EXIT_SUCCESS;
}
