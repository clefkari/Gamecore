/*			ENTITY				clefkari@ucsd.edu

#############################################################################*/

#include "Entity.h"

static unsigned int entityCounter = 0;

/* We create a new entity by using a stack entity which will recieve the input
from user or file. */

void * copyEntity(void * data){

	Entity * ep = (Entity*)malloc(sizeof(Entity));

	ep->texture = ((Entity*)data)->texture;
	ep->x = ((Entity*)data)->x;
	ep->y = ((Entity*)data)->y;
	ep->w = ((Entity*)data)->w;
	ep->h = ((Entity*)data)->h;

	ep->id = entityCounter++;
	
	fprintf(stderr,NEW_ENTITY,(void*)ep,((Entity*)data)->id);

	return (void*) ep;

}

/* deleteEntity

*/

void deleteEntity(void ** data){

	fprintf(stderr,DELETE_ENTITY,*data,((Entity*)*data)->id);
	
	free(*data);
	*data=0;

}

/* equalsEntity

*/

int equalsEntity(void * lhs, void * rhs){

	Entity * elhs = (Entity *)lhs;
	Entity * erhs = (Entity *)rhs;

	return (elhs->id == erhs->id);

}

int initEntity(){

}
