/*			PARSER			clefkari@ucsd.edu

#############################################################################*/

#ifndef PARSER_H
#define PARSER_H

#include "Strings.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum { false, true } bool;

void clrbuf (int character);

typedef struct Node{
	struct Node * pre;
	struct Node * next;
	void * data;
}Node;

typedef struct{
	Node * front;
	long list_count;
	long occupancy;
	void * (*copy_func)(void *);
	void (*delete_func)(void **);
	int (*equals_func)(void*,void*);
}List;

typedef struct{
	List * lp;	
}Parser;

/* Node   ------------------------------------------------------------ */

Node * newNode (void * data, void * (*copy_func) (void *));
void deleteNode (List * lp, Node ** np);
void deleteAllNodes(Node ** np, List * lp);
Node * lookupNode (Node * np, void * data,
int (*equals_func)(void*,void*));


/* List   ------------------------------------------------------------ */

List * newList (void * (*copy_func)(void *),
		void (*delete_func)(void **),
		int (*equals_func)(void*,void*));

void deleteList (List ** lpp);
void insertList(List * lp, void * data);
int removeList (List * lp, void * data);
Node * lookupList (List * lp, void * data);

/* Parser ------------------------------------------------------------ */

Parser * newParser (void * (*copy_func)(void *),
		void (*delete_func)(void **));
void deleteParser(Parser ** parser);

#endif
