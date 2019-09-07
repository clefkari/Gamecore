/*			PARSER			clefkari@ucsd.edu

#############################################################################*/
#include "Parser.h"
#include "Strings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static long list_counter = 0;

/* clrbuf

   Clears stdin to the next newline. */

void clrbuf (int character) {
	while(character != (int)'\n'){
		character = fgetc(stdin);
	}
}	

/* new_Node

   Constructor

   @param - void * data, void * (*copy_func) (void *)
   @return - Node * np

   Takes a generic data void * and it's associated copy function and
   constructs a new Node from it, returning a pointer to it. */

Node * new_Node (void * data, void * (*copy_func) (void *)) {

	Node * np = (Node*)malloc(sizeof(Node));

	np->data = copy_func(data);
	np->pre = np->next = 0;

	fprintf(stderr,NEW_NODE,(void*)np);

	return np;
}


/* delete_Node

   Destructor

   @param - Node * np

   Deallocates all associated memory. */

void delete_Node (List * lp, Node ** np) {
	fprintf(stderr,DELETE_NODE,(void*)*np);

	lp->delete_func(&(*np)->data);	
	lp->occupancy--;

	free(*np);
	*np=0;
}

/* delete_AllNodes

   All Destructor

   @param - Node * np

   Recursively deletes all nodes linked to the specified one. */

void delete_AllNodes(Node ** np, List * lp) {
	if(!*np)
		return;

	Node * pre = (*np)->pre;
	delete_Node(lp,np);

	delete_AllNodes(&pre, lp);
}

/* new_List

   Constructor

   Allocates a List struct and sets its members to their initial values.

   @params - function pointers to the generic data type being stored.
   @return - List * - the List. */

List * new_List (void * (*copy_func)(void *),
		void (*delete_func)(void **)) {

	List * lp = (List*) malloc(sizeof(List));
	lp->occupancy = 0;
	lp->list_count = ++list_counter;
	lp->copy_func = copy_func;
	lp->delete_func = delete_func;
	lp->front = 0;

	fprintf(stderr,LIST_MADE,(void*)lp,lp->list_count);

	return lp;
}

/* delete_List

   Destructor

   @param - List ** lpp - a pointer to a pointer to a List.

   Deallocates the passed List and all associated data members. */

void delete_List (List ** lpp){
	fprintf(stderr,DELETE_LIST,(void*)*lpp,(*lpp)->list_count);
	list_counter--;
	delete_AllNodes(&(*lpp)->front,*lpp);
	free(*lpp);
	*lpp=0;
}

//TODO Validity checks on List pointers and others.

/* insert_List

   @params - List * lp, char * str

   Inserts a new Node into the specified List, in this case, a string
   is passed and stored. */

void insert_List(List * lp, void * data){
	/* If the list has no front Node, create it. */
	if(!lp->front){
		lp->front = new_Node(data,lp->copy_func);
		/* Otherwise, push to the top. */
	}else{
		lp->front->next = new_Node(data,lp->copy_func);
		lp->front->next->pre = lp->front;

		lp->front = lp->front->next;
	}

	fprintf(stderr,OCCUPANCY,++lp->occupancy);
}

/* remove_Node

   Finds and removes a Node by searching for the specified data field. */

Node * remove_List (List * lp, void * data){
	if(!lp->front)
		fprintf(stderr,NO_FRONT,(void*)lp,lp->occupancy);

	return 0;
}

/* BOOKMARK ######################################################### strtok */

Parser * new_Parser (void * (*copy_func)(void *),
		void (*delete_func)(void **)) {

	Parser * parser = (Parser*) malloc(sizeof(Parser));
	parser->lp = new_List(copy_func,delete_func);

	fprintf(stderr,PARSER_MADE,(void*)parser);

	return parser;
}

void delete_Parser(Parser ** parser){
	delete_List(&((*parser)->lp));	
	fprintf(stderr,DELETE_PARSER,(void*)*parser);	
	free(*parser);
	*parser=0;
}

/* tokenize_Parser

   Tokenizes the read in nodes of the Parser into words, and manages
   the Parser's 
   static void tokenize_Parser(Parser ** parser){

   } */
