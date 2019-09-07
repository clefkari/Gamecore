#include "Texture.h"
#include "Parser.h"
#include "Strings.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <errno.h>


static const int SCREEN_WIDTH = 1200;
static const int SCREEN_HEIGHT = 800;
static const int BUFF_SIZE = 256;

int main(int argc, char* argv[]){
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  SDL_Event event;
  SDL_Rect d;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
    return 3;
  }

  window = SDL_CreateWindow("SDL_CreateTexture",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH, SCREEN_HEIGHT,
      SDL_WINDOW_RESIZABLE);

  d.x = SCREEN_WIDTH / 2;
  d.y = SCREEN_HEIGHT / 2;

  renderer = SDL_CreateRenderer(window, -1, 0);

  /* Me */

  initTextures(renderer);

  /* End Me */

  while (1) {

    switch(rand()%5){
      case 0:
        texture = getTexture("tree.bmp");
        break;

      case 1:
        texture = getTexture("rock.bmp");
        break;

      case 2:
        texture = getTexture("water.bmp");
        break;

      case 3:
        texture = getTexture("voodoo.bmp");
        break;

      case 4:
        texture = getTexture("flameblast.bmp");
        break;

defeault:
        break;
    }

    d.x= rand()%500;
    d.y= rand()%500;
    d.w= rand()%500;
    d.h= rand()%500;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, &d);
    SDL_RenderPresent(renderer);
    SDL_Delay(500);

    SDL_PollEvent(&event);

    if(event.type == SDL_QUIT)
      break;

    /* Me

*/


    /* End Me

*/

  }

  delete_List(&textureList);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();


  return 0;
}
