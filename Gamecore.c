/*			GAMECORE			clefkari@ucsd.edu

#############################################################################*/

#include "Gamecore.h"

int run(int argc, char * argv[]){
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;
  SDL_Rect d;

  Node * np;

  char buffer [BUFFER_SIZE] = { 0 };
  char * ch;

  int running = 1;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
    return 3;
  }

  window = SDL_CreateWindow("Gamecore",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH, SCREEN_HEIGHT,
      SDL_WINDOW_RESIZABLE);


  renderer = SDL_CreateRenderer(window, -1, 0);

  /* Global Data List Initialization. */
  initTextures(renderer);
  initEntity(argc,argv);

  while (running) {

    while(SDL_PollEvent(&event)){

      /* Window Closing Event */

      if(event.type == SDL_QUIT){

        running = 0;

      }

      /* Key Down Events */

      if(event.type == SDL_KEYDOWN){

        /* Parse a Console Command */

        if(event.key.keysym.sym == SDLK_BACKQUOTE){

          fprintf(stdout,PROMPT);
          fgets(buffer,BUFFER_SIZE,stdin);
          ch = strchr(buffer,NEWLINE);

          if(ch){

            *ch = 0;
            parseEntity(buffer);

          }

        }

      }

    }

    SDL_RenderClear(renderer);

    /* Boiler Plate */

    np = entityList->front;
    if(np){

      while(np){

        d.x = ((Entity*)(np->data))->x;
        d.y = ((Entity*)(np->data))->y;
        d.h = ((Entity*)(np->data))->h;
        d.w = ((Entity*)(np->data))->w;

        SDL_RenderCopy(renderer, ((Entity*)(np->data))->texture, 
            NULL, &d);

        np = np->pre;

      }

    }

    /* End Boiler Plate */

    SDL_RenderPresent(renderer);

  }

  /* Global Data List Deallocation. */
  deleteList(&textureList);
  deleteList(&entityList);

  /* SDL Clean up. */
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  return 0;

}
