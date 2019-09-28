/*			GAMECORE			clefkari@ucsd.edu

#############################################################################*/

#ifndef GAMECORE_H
#define GAMECORE_H

#include "Strings.h"
#include "Entity.h"
#include "Texture.h"
#include "Parser.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <errno.h>

typedef struct{
  SDL_Window * window;
  SDL_Renderer * renderer;
  SDL_Event event;
  SDL_Rect rect;
	char running;
	List * textureList, * entityList;
}Gamecore;

Gamecore * newGamecore(int argc, char* argv[]);
int executeGamecore(Gamecore * core);
void deleteGamecore(Gamecore ** gpp);

#endif
