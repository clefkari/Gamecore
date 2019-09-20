/*			ENTITY				clefkari@ucsd.edu

#############################################################################*/

#ifndef ENTITY_H
#define ENTITY_H

#include "Strings.h"
#include "Parser.h"
#include "Texture.h"

/* Global list of all entities in the game. */
List * entityList;

/* struct Entity

	@ Members:

		texture - a pointer to pre-initialized global texture.
		x - x coordinate.
		y - y coordinate.
		w - width.
		h - height.

		*/

typedef struct{
SDL_Texture * texture;
int x, y, w, h;
unsigned long id;
}Entity;

void * newEntity(void * stackEntity);
void deleteEntity(void ** epp);
int equalsEntity(void * lhs, void * rhs);

#endif
