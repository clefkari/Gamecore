#include "Parser.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


/* Texture data - with associated copy/delete functions. */
typedef struct{
SDL_Texture * texture;
char * name;
}Texture;

/* Global list of all textures. */
List * textureList;

int initTextures(SDL_Renderer * renderer);
void * copyTexture(void * data);
void deleteTexture(void ** data);
