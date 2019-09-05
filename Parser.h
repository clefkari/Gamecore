#ifndef PARSER_H
#define PARSER_H
/*			PARSER			clefkari@ucsd.edu

#############################################################################*/

#include <stdio.h>
#include <stdlib.h>
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
}List;

typedef struct{
	List * lp;	
}Parser;

void * copy_func (void * data);
void delete_func (void ** data);

/* Node   ------------------------------------------------------------ */

Node * new_Node (void * data, void * (*copy_func) (void *));
void delete_Node (List * lp, Node ** np);
void delete_AllNodes(Node * np, List * lp);

/* List   ------------------------------------------------------------ */

List * new_List (void * (*copy_func)(void *),
		void (*delete_func)(void **));
void delete_List (List ** lpp);
void insert_List(List * lp, void * data);
struct Node * remove_List (List * lp, void * data);

/* Parser ------------------------------------------------------------ */

Parser * new_Parser (void * (*copy_func)(void *),
		void (*delete_func)(void **));
void delete_Parser(Parser ** parser);

#endif
