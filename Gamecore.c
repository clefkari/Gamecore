/*			GAMECORE			clefkari@ucsd.edu

#############################################################################*/

#include "Gamecore.h"
	
int run(){
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Event event;
	SDL_Rect d;

	int running = 1;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return 3;
	}

	window = SDL_CreateWindow("SDL_CreateTexture",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_RESIZABLE);


	renderer = SDL_CreateRenderer(window, -1, 0);

	/* Me */

	initTextures(renderer);
	texture = getTexture("water.bmp");

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

					fgetc(stdin);//TODO - insert console commands here.
				
				}

			}

		}

		SDL_RenderClear(renderer);
		/* SDL_RenderCopy(renderer, texture, NULL, &d); */
		SDL_RenderPresent(renderer);
		SDL_Delay(500);

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
