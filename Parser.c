/*			PARSER			clefkari@ucsd.edu

#############################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definition for ASCII codes. */
#define ASCII_TAB 0x09

const int BUFF_SIZE = 256;

/* Catastrophic. */
const char FILE_FAIL [] = "File failed to open, exiting program.\n";

/* Basic. */
const char WRONG_USAGE [] = "Incorrect usage: Parser <fileame>\n";

const char STDIN_USAGE [] = "Standarad Input mode:\n";

const char NEW_NODE [] = "%X New node constructed: %s\n";

const char DELETE_NODE [] = "%X Node destructed: %s\n";

const char LIST_MADE [] = "%X List %d constructed\n";

const char PARSER_MADE [] = "%X Parser constructed\n";

const char DELETE_PARSER [] = "%X Parser destructed\n";

const char DELETE_LIST [] = "%X List %d destructed\n";

const char NO_FRONT [] = "%X List %d NULL front pointer\n";

const char OCCUPANCY [] = "Occupancy: %d\n";

/* clrbuf

	Clears stdin to the next newline. */

static void clrbuf (int character) {
	while(character != (int)'\n'){
		character = fgetc(stdin);
	}
}	

/* Node
	*/

typedef struct Node{
	struct Node * pre;
	struct Node * next;
	void * data;
}Node;


/* List
	*/

typedef struct{
	Node * front;
	long list_count;
	long occupancy;
	void * (*copy_func)(void *);
	void (*delete_func)(void *);
}List;

static long list_counter = 0;

/* copy_func

	Implements a copy function for a char * string.

	Generic copy function implementation goes here. This is where void *
	data types get their behavior.
	
	@param - void * data
	@return - void * copy of data */

void * copy_func (void * data){
	return  (void*) strdup((char*)data);
}

/* delete_func

	Implements a delete function for a char * string.
	
	Generic delete function implementation goes here.  This deletes the
	void * data and handles memory deallocations. 
		
	@param void * data. */

void delete_func (void ** data) {
	free((char*)(*data));
	*data = 0;
}

	
/* new_Node

	Constructor

	@param - void * data, void * (*copy_func) (void *)
	@return - Node * np

	Takes a generic data void * and it's associated copy function and
	constructs a new Node from it, returning a pointer to it. */

static Node * new_Node (void * data, void * (*copy_func) (void *)) {
	
	Node * np = (Node*)malloc(sizeof(Node));

	np->data = copy_func(data);
	np->pre = np->next = 0;

	fprintf(stderr,NEW_NODE,np,np->data);
	
	return np;
}


/* delete_Node

	Destructor

	@param - Node * np
	
	Deallocates all associated memory. */

static void delete_Node (List * lp, Node ** np) {
	fprintf(stderr,DELETE_NODE,*np,(char*)(*np)->data);

	lp->delete_func(&(*np)->data);	
	lp->occupancy--;

	free(*np);
	*np=0;
}

/* delete_AllNodes

	All Destructor

	@param - Node * np

	Recursively deletes all nodes linked to the specified one. */

static void delete_AllNodes(Node * np, List * lp) {
	if(!np)
		return;
	
	Node * pre = np->pre;
	delete_Node(lp,&np);

	if(pre)
		delete_AllNodes(pre, lp);
}

/* new_List
	
	Constructor
	
	Allocates a List struct and sets its members to their initial values.
	
	@params - function pointers to the generic data type being stored.
	@return - List * - the List. */

static List * new_List (void * (*copy_func)(void *),
	void (*delete_func)(void *)) {

	List * lp = (List*) malloc(sizeof(List));
	lp->occupancy = 0;
	lp->list_count = ++list_counter;
	lp->copy_func = copy_func;
	lp->delete_func = delete_func;
	lp->front = 0;

	fprintf(stderr,LIST_MADE,lp,lp->list_count);

	return lp;
}

/* delete_List

	Destructor
	
	@param - List ** lpp - a pointer to a pointer to a List.

	Deallocates the passed List and all associated data members. */

static void delete_List (List ** lpp){
	fprintf(stderr,DELETE_LIST,*lpp,(*lpp)->list_count);
	list_counter--;
	delete_AllNodes((*lpp)->front,*lpp);
	free(*lpp);
	*lpp=0;
}

//TODO Validity checks on List pointers and others.

/* insert_List
	
	@params - List * lp, char * str

	Inserts a new Node into the specified List, in this case, a string
	is passed and stored. */

static void insert_List(List * lp, void * data){
	/* If the list has no front Node, create it. */
	if(!lp->front){
		lp->front = new_Node(data,copy_func);
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

static Node * remove_List (List * lp, void * data){
	if(!lp->front)
		fprintf(stderr,NO_FRONT,lp,lp->occupancy);

	return 0;
}

/* BOOKMARK ######################################################### strtok */
typedef struct{
	List * lp;	
}Parser;

static Parser * new_Parser (void * (*copy_func)(void *),
	void (*delete_func)(void *)) {

	Parser * parser = (Parser*) malloc(sizeof(Parser));
	parser->lp = new_List(copy_func,delete_func);

	fprintf(stderr,PARSER_MADE,parser);

	return parser;
}

static void delete_Parser(Parser ** parser){
	delete_List(&((*parser)->lp));	
	fprintf(stderr,DELETE_PARSER,*parser);	
	free(*parser);
	*parser=0;
}

/* tokenize_Parser

	Tokenizes the read in nodes of the Parser into words, and manages
	the Parser's 
static void tokenize_Parser(Parser ** parser){

}

/* Main ---------------------------------------------------------------------*/

int main(int argc, char ** argv){
Parser * parser;
/* Filename passed at command line. */
char * fName;
/* File pointer. */
FILE * file;
/* Iterator. */
int i;

/* Line buffer, to be processed, initialized null. */
char line [BUFF_SIZE]; i = 0;
while(i < BUFF_SIZE) { line[i] = '\0'; i++; }	

/* Make sure we recieve a filename. */
if(argc == 1){
	fprintf(stdout,STDIN_USAGE);
	fgets(line, BUFF_SIZE, stdin);
	
	/* Echo. */
	fprintf(stdout,line);
	return 0;

	/* Incorrect usage. */
	}else if(argc > 2){
		fprintf(stdout,WRONG_USAGE);
	}
	
	/* Get name from args. */
	fName = argv[1];

	/* File Mode. */
	file = fopen(fName,"r");
	
	if(!file){
		fprintf(stderr,FILE_FAIL);
		return -1;
	}

	/* Handle a good file -----------------------------------------------*/
	parser = new_Parser(copy_func,delete_func);	

	while(fgets(line, BUFF_SIZE, file) != NULL){
	insert_List(parser->lp,line);
	}

	delete_Parser(&parser);

	/* Close file. */
	if(file != NULL)
		fclose(file);

return 0;

}
