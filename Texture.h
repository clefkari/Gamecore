/*			TEXTURE			clefkari@ucsd.edu

#############################################################################*/

#ifndef TEXTURE_H
#define TEXTURE_H

#include "Parser.h"
#include "Strings.h"
#include <errno.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/* Texture data - with associated copy/delete functions. */
typedef struct{
SDL_Texture * texture;
char * name;
}Texture;

int initTextures(List ** textureList, SDL_Renderer * renderer);
void * copyTexture(void * data);
void deleteTexture(void ** data);
int equalsTexture(void * lhs, void * rhs);
SDL_Texture * getTexture(List * textureList, char * name);

#endif
