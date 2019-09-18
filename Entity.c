/*			ENTITY				clefkari@ucsd.edu

#############################################################################*/

#include "Entity.h"

/* We create a new entity by using a stack entity which will recieve the input
from user or file. */

Entity * newEntity(Entity * stackEntity){

	Entity * ep = (Entity*)malloc(sizeof(Entity));

	ep->texture = stackEntity->texture;
	ep->x = stackEntity->x;
	ep->y = stackEntity->y;
	ep->w = stackEntity->w;
	ep->h = stackEntity->h;

	return ep;

}

/* deleteEntity

*/

void deleteEntity(Entity ** epp){

	free(*epp);
	*epp=0;

}
