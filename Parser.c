/*			PARSER			clefkari@ucsd.edu

#############################################################################*/

#include "Parser.h"

static unsigned long list_counter = 0;

/* clrbuf

   Clears stdin to the next newline. */

void clrbuf (int character) {
  while(character != (int)'\n'){
    character = fgetc(stdin);
  }
}	

/* newNode

   Constructor

   @param - void * data, void * (*copy_func) (void *)
   @return - Node * np

   Takes a generic data void * and it's associated copy function and
   constructs a new Node from it, returning a pointer to it. */

Node * newNode (void * data, void * (*copy_func) (void *)) {

  Node * np = (Node*)malloc(sizeof(Node));

  np->data = copy_func(data);
  np->pre = np->next = 0;

  fprintf(stderr,NEW_NODE,(void*)np);

  return np;
}


/* deleteNode

   Destructor

   @param - Node * np

   Deallocates all associated memory. */

void deleteNode (List * lp, Node ** np) {
  fprintf(stderr,DELETE_NODE,(void*)*np);

  lp->delete_func(&(*np)->data);	
  lp->occupancy--;

  free(*np);
  *np=0;
}

/* deleteAllNodes

   All Destructor

   @param - Node * np

   Recursively deletes all nodes linked to the specified one. */

void deleteAllNodes(Node ** np, List * lp) {
  if(!*np)
    return;

  Node * pre = (*np)->pre;
  deleteNode(lp,np);

  deleteAllNodes(&pre, lp);
}

/* newList

   Constructor

   Allocates a List struct and sets its members to their initial values.

   @params - function pointers to the generic data type being stored.
   @return - List * - the List. */

List * newList (void * (*copy_func)(void *),
void (*delete_func)(void **),
int (*equals_func)(void*,void*)) {

  List * lp = (List*) malloc(sizeof(List));
  lp->occupancy = 0;
  lp->list_count = ++list_counter;
  lp->copy_func = copy_func;
  lp->delete_func = delete_func;
  lp->equals_func = equals_func;
  lp->front = 0;

  fprintf(stderr,LIST_MADE,(void*)lp,lp->list_count);

  return lp;

}

/* deleteList

   Destructor

   @param - List ** lpp - a pointer to a pointer to a List.

   Deallocates the passed List and all associated data members. */

void deleteList (List ** lpp){

  fprintf(stderr,DELETE_LIST,(void*)*lpp,(*lpp)->list_count);

  list_counter--;

  deleteAllNodes(&(*lpp)->front,*lpp);
  free(*lpp);
  *lpp=0;

}

//TODO Validity checks on List pointers and others.

/* insertList

   @params - List * lp, char * str

   Inserts a new Node into the specified List, in this case, a string
   is passed and stored. */

void insertList(List * lp, void * data){

  /* If the list has no front Node, create it. */
  if(!lp->front){

    lp->front = newNode(data,lp->copy_func);
    /* Otherwise, push to the top. */

  }else{

    lp->front->next = newNode(data,lp->copy_func);
    lp->front->next->pre = lp->front;
    lp->front = lp->front->next;

  }

  fprintf(stderr,OCCUPANCY,++lp->occupancy);
}

/* removeNode

   Finds and removes a Node by searching for the specified data field. */

int removeList (List * lp, void * data){

  if(!lp->front)
    fprintf(stderr,NO_FRONT,(void*)lp,lp->occupancy);

  return 0;

}


/* lookupNode

*/

Node * lookupNode (Node * np, void * data,
int (*equals_func)(void*,void*)){

  if(equals_func(data,np->data)){

    return np;

  }

  if(!np->pre){

    return NULL;

  }

  return lookupNode (np->pre,data,equals_func);

}

/* lookupList

*/


Node * lookupList (List * lp, void * data){

  if(!lp->front){

    fprintf(stderr,NO_FRONT,(void*)lp,lp->occupancy);

    return NULL;

  }

  Node * np = lookupNode(lp->front,data,lp->equals_func);

  return np;

}

/* newParser

*/

Parser * newParser (void * (*copy_func)(void *),
void (*delete_func)(void **)) {

  Parser * parser = (Parser*) malloc(sizeof(Parser));
  parser->lp = newList(copy_func,delete_func,0);

  fprintf(stderr,PARSER_MADE,(void*)parser);

  return parser;

}

/* deleteParser

*/

void deleteParser(Parser ** parser){

  deleteList(&((*parser)->lp));

  fprintf(stderr,DELETE_PARSER,(void*)*parser);

  free(*parser);
  *parser=0;

}

/* tokenize_Parser

   Tokenizes the read in nodes of the Parser into words, and manages
   the Parser's 
   static void tokenize_Parser(Parser ** parser){

   } */
