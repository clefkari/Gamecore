/*			ENTITY				clefkari@ucsd.edu

#############################################################################*/

#ifndef ENTITY_H
#define ENTITY_H

#include "Strings.h"
#include "Parser.h"
#include "Texture.h"
#include <errno.h>
#include <stdio.h>

/* To identify Components, a long will be used to store up to 64 (or other
 * based on platform) bit flags representing a behavior/characteristic. */

/* Component Bit Flag Map (TODO) */
typedef enum{
PLAYER =  0x1,
NPC = 0x2,
SOLID = 0x4
}Components;

/* Global list of all entities in the game. */
List * entityList;

/* struct Entity

   @ Members:

   texture - a pointer to pre-initialized global texture.
   x - x coordinate.
   y - y coordinate.
   w - width.
   h - height.
   comp - bit flags for components.

*/

typedef struct{
  SDL_Texture * texture;
  long x, y, w, h;
  unsigned long id;
  Components comp;
}Entity;

void * newEntity(void * stackEntity);
void deleteEntity(void ** epp);
int equalsEntity(void * lhs, void * rhs);
int initEntity(int argc, char * argv[]);
int parseEntity(char * cmd);

#endif
