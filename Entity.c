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
  ep->comp = ((Entity*)data)->comp;

  ep->id = entityCounter++;

  fprintf(stderr,NEW_ENTITY,(void*)ep,ep->id,ep->comp);

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

/* initEntity

 */

int initEntity(int argc, char * argv[]){

  entityList = newList(copyEntity,deleteEntity,equalsEntity);

  return 0;

}

/* parseEntity
 *
 * Parses a string and tokenizes it to use as data for members of a stack
 * Entity.  If all is successful a list insertion will be made.
 *
 * @params - cmd - the string to tokenize.
 * @return - int - success/fail 0/-1 */

int parseEntity(char * cmd){

  /* Stack Struct to store input. */
  Entity entity = { 0 };

  /* For processing the command. */
  char * ch, * endptr;

  errno = 0;

  /* Tokenize */

  /* X COORDINATE */

  ch = strtok(cmd,DELIM);

  if(errno){
    fprintf(stderr,ENTITY_FAIL,strerror(errno));
    return -1;
  }

  if(!ch){
    return -1;
  }

  entity.x = strtol(ch,&endptr,DECIMAL);

  if(ch == endptr){
    return -1;  
  }

  /* */

  /* Y COORDINATE */

  ch = strtok(NULL,DELIM);

  if(errno){
    fprintf(stderr,ENTITY_FAIL,strerror(errno));
    return -1;
  }

  if(!ch){
    return -1;
  }

  entity.y = strtol(ch,&endptr,DECIMAL);

  if(ch == endptr){
    return -1;  
  }

  /* */

  /* Width */

  ch = strtok(NULL,DELIM);

  if(errno){
    fprintf(stderr,ENTITY_FAIL,strerror(errno));
    return -1;
  }

  if(!ch){
    return -1;
  }

  entity.w = strtol(ch,&endptr,DECIMAL);

  if(ch == endptr){
    return -1;  
  }

  /* */

  /* Height */

  ch = strtok(NULL,DELIM);

  if(errno){
    fprintf(stderr,ENTITY_FAIL,strerror(errno));
    return -1;
  }

  if(!ch){
    return -1;
  }

  entity.h = strtol(ch,&endptr,DECIMAL);

  if(ch == endptr){
    return -1;  
  }

  /* */

  /* Texture */

  ch = strtok(NULL,DELIM);

  if(errno){
    fprintf(stderr,ENTITY_FAIL,strerror(errno));
    return -1;
  }

  if(!ch){
    return -1;
  }

  entity.texture = getTexture(ch);
  if(!entity.texture){
    return -1;  
  }

  /* */

  /* Components */

  ch = strtok(NULL,DELIM);

  if(errno){
    fprintf(stderr,ENTITY_FAIL,strerror(errno));
    return -1;
  }

  if(!ch){
    return -1;
  }

  entity.comp = strtoul(ch,&endptr,0);
  if(ch == endptr){
    return -1;  
  }
  
  /* Stack Entity is copied and inserted. */
  insertList(entityList,&entity);

  return 0;

}
