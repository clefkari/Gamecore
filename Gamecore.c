/*			GAMECORE			clefkari@ucsd.edu

#############################################################################*/

#include "Gamecore.h"
	
int run(){
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
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
  initEntity();

	/* texture = getTexture("water.bmp"); */

	/* End Me */

	while (running) {

		/* Random Texture Test -
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

			 default:
			 break;
			 }


			 d.x= rand()%500;
			 d.y= rand()%500;
			 d.w= rand()%500;
			 d.h= rand()%500;

		 */

		while(SDL_PollEvent(&event)){

			if(event.type == SDL_QUIT){

				running = 0;

			}
			
			/* Key Down Events */

			if(event.type == SDL_KEYDOWN){

				if(event.key.keysym.sym == SDLK_BACKQUOTE){

					fgets(buffer,BUFFER_SIZE,stdin);//TODO - insert console commands here.
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
	delete_List(&textureList);
  delete_List(&entityList);

  /* SDL Clean up. */
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;

}
