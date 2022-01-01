#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>
#include <Render/Texture.hpp>
#include <Render/VAO.hpp>
#include <glimac/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include <SDL/SDL.h>
#include <math.h>

#include <Game/AssetsManager.hpp>
#include <Game/Menu.hpp>


#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 1800

using namespace glimac;
int main(int argc, char **argv)
{
  // Initialize SDL and open a window
  SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "IMA'GALAXY");

  // Initialize glew for OpenGL3+ support
  GLenum glewInitError = glewInit();
  if (GLEW_OK != glewInitError)
  {
    std::cerr << glewGetErrorString(glewInitError) << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

  /*********************************
   *      INITIALIZATION CODE
   *********************************/

  // Charger et compiler les shaders
  FilePath applicationPath(argv[0]);

  AssetsManager assets(applicationPath.dirPath());
  std::cout << assets.element("menu")->size() << std::endl;
  std::cout << assets.element("menu")->position() << std::endl;
  

  // Application loop:
  bool done = false;
  while (!done)
  {
    // Event loop:
    SDL_Event e;
    while (windowManager.pollEvent(e))
    {
      /* L'utilisateur ferme la fenêtre */
      if (e.type == SDL_QUIT)
      {
        done = true; // Leave the loop after this iteration
      }

      if (e.type == SDL_MOUSEBUTTONDOWN)
      {
        if (e.button.button == SDL_BUTTON_LEFT)
        {
          std::cout << "(" << e.button.x << "," << e.button.y << ")" << std::endl;
          //done = true;
          if (e.button.x > 0.2*WINDOW_WIDTH && e.button.x < 0.39*WINDOW_WIDTH && e.button.y > 0.7*WINDOW_HEIGHT && e.button.y < 0.83*WINDOW_HEIGHT)
          {
            done = true;
          }
          else if (e.button.x > 167 && e.button.x < 311 && e.button.y > 238 && e.button.y < 339)
          {
            
            std::cout << "PLAY ! Level 1 ! Game Begin ! " << std::endl;
          }
          else if (e.button.x > 507 && e.button.x < 748 && e.button.y > 238 && e.button.y < 339)
          {

              std::cout << "PLAY ! Level 2 ! Game Begin ! " << std::endl;
          }
          else if (e.button.x > 507 && e.button.x < 748 && e.button.y > 426 && e.button.y < 491)
          {
            std::cout << "REPLAY ! RUN AGAIN ! Game Begin AGAIN ! " << std::endl;
          }
        }
      }

      /* Traitement d'evenements :*/
      switch (e.type)
      {
        /*Touche clavier*/
      case SDL_KEYDOWN:
        switch (e.key.keysym.sym)
        {
        case SDLK_q:
          done = true;
          break;

        case SDLK_SPACE:
          std::cout << "PLAY ! " << std::endl;
          break;

        case SDLK_ESCAPE:
          done = true;
          break;

        default:
          break;
        }
      }
    }
    /*********************************
     *         RENDERING CODE
     *********************************/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    assets.element("menu")->draw();

    windowManager.swapBuffers();
  }
  //liberation ressources
  assets.unloadAssets();

  return EXIT_SUCCESS;
}
