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

#define TEXTURE_BUFFER 256
#define NAME_BUFFER 512

/* Global list of all textures. */
List * textureList;

/* Texture data - with associated copy/delete functions. */
typedef struct{
SDL_Texture * texture;
char * name;
}Texture;

int initTextures(SDL_Renderer * renderer);
void * copyTexture(void * data);
void deleteTexture(void ** data);
int equalsTexture(void * lhs, void * rhs);
SDL_Texture * getTexture(char * name);

#endif
