/*			GAMECORE			clefkari@ucsd.edu

#############################################################################*/

#include "Gamecore.h"

Gamecore * newGamecore(int argc, char* argv[]){

	Gamecore * gp;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return NULL;
	}

	gp = (Gamecore*) malloc(sizeof(Gamecore));

	gp->window = SDL_CreateWindow("Gamecore",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_RESIZABLE);

	gp->renderer = SDL_CreateRenderer(gp->window, -1, 0);

	initTextures(&gp->textureList, gp->renderer);
	initEntity(&gp->entityList);

	gp->running = 1;

	return gp;

}

/* executeGamecore

 */

int executeGamecore(Gamecore * gp){

	char buffer [BUFFER_SIZE] = { 0 };
	char * ch;
	Node * np;

	while (gp->running) {

		while(SDL_PollEvent(&gp->event)){

			/* Window Closing Event */

			if(gp->event.type == SDL_QUIT){

				gp->running = 0;
				break;

			}

			/* Key Down Events */

			if(gp->event.type == SDL_KEYDOWN){

				/* Parse a Console Command */

				if(gp->event.key.keysym.sym == SDLK_BACKQUOTE){

					fprintf(stdout,PROMPT);
					fgets(buffer,BUFFER_SIZE,stdin);
					ch = strchr(buffer,NEWLINE);

					if(ch){

						*ch = 0;
						parseEntity(gp->entityList,gp->textureList, buffer);

					}

				}

			}

		}

		SDL_RenderClear(gp->renderer);

		/* Boiler Plate */

		np = gp->entityList->front;
		if(np){

			while(np){

				gp->rect.x = ((Entity*)(np->data))->x;
				gp->rect.y = ((Entity*)(np->data))->y;
				gp->rect.h = ((Entity*)(np->data))->h;
				gp->rect.w = ((Entity*)(np->data))->w;

				SDL_RenderCopy(gp->renderer, ((Entity*)(np->data))->texture, 
						NULL, &gp->rect);

				np = np->pre;

			}

		}

		/* End Boiler Plate */

		SDL_RenderPresent(gp->renderer);

	}

	return 0;

}

void deleteGamecore(Gamecore ** gpp){

	/* Data List Deallocation. */
	deleteList(&(*gpp)->textureList);
	deleteList(&(*gpp)->entityList);

	/* SDL Clean up. */
	SDL_DestroyRenderer((*gpp)->renderer);
	SDL_DestroyWindow((*gpp)->window);
	SDL_Quit();

	/* Gamecore Deallocation */
	free(*gpp);
	*gpp=0;

}
