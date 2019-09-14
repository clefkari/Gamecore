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

Node * new_Node (void * data, void * (*copy_func) (void *));
void delete_Node (List * lp, Node ** np);
void delete_AllNodes(Node ** np, List * lp);
Node * lookup_Node (Node * np, void * data,
int (*equals_func)(void*,void*));


/* List   ------------------------------------------------------------ */

List * new_List (void * (*copy_func)(void *),
		void (*delete_func)(void **),
		int (*equals_func)(void*,void*));

void delete_List (List ** lpp);
void insert_List(List * lp, void * data);
struct Node * remove_List (List * lp, void * data);
Node * lookup_List (List * lp, void * data);

/* Parser ------------------------------------------------------------ */

Parser * new_Parser (void * (*copy_func)(void *),
		void (*delete_func)(void **));
void delete_Parser(Parser ** parser);

#endif
