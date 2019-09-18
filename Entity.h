#ifndef ENTITY_H
#define ENTITY_H

#include "Parser.h"
#include "Strings.h"
#include "Texture.h"

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
}Entity;


Entity * newEntity(Entity * stackEntity);
void deleteEntity(Entity ** epp);

#endif
