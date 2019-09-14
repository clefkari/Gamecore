/*			TEXTURE			clefkari@ucsd.edu

#############################################################################*/

#include "Texture.h"

/* init_Textures

	 Initializes all game textures in the data section of memory to be pointed to
	 by surfaces.  The number of failures is the return value of the function.
	 The initializer opens the Texture directory to parse images.

	 @return - int - number of failures or -1 on error.

 */

int initTextures(SDL_Renderer * renderer){

	char name[NAME_BUFFER] = { 0 };
	Texture texture = {.texture = NULL, .name = NULL};
	SDL_Surface * surface = NULL;

	/* Initialize a Texture List with the correct copy/delete functions. */
	textureList = new_List(&copyTexture,&deleteTexture,&equalsTexture);

	int failures = 0;
	int counter = 0;
	errno = 0;

	struct dirent * de;
	DIR * dr = opendir(TEXTURE_DIR);

	if(!dr){
		fprintf(stderr,DIR_FAIL,TEXTURE_DIR,strerror(errno));
		return -1;
	}

	while((de = readdir(dr)) != NULL){

		memset(name, 0, sizeof(name));
		sprintf(name,TEXTURE_FORMAT,de->d_name);
		surface = SDL_LoadBMP(name);

		if(!surface){//TODO

			failures++;
			fprintf(stderr,SURFACE_FAIL,name);

		}else{

			texture.texture = SDL_CreateTextureFromSurface(renderer,surface);
			if(!texture.texture){

				failures++;
				fprintf(stderr,TEXTURE_FAIL,de->d_name);
			}else{
				texture.name = de->d_name;
				insert_List(textureList,(void*)&texture);

			}

		}

		SDL_FreeSurface(surface);

	}

	closedir(dr);

	return failures;

}

/* Polymorphic copy function for Texture data. 

	 The Texture is created on the stack, and then a duplicate is made.
	 The duplicate uses the stack versions pointer to the texture, and is
	 in charge of deallocating it later.  The name is strdup'd and also
	 must be free'd.

	 @return void * - the Texture.

 */

void * copyTexture(void * data){

	Texture * tp = (Texture *) malloc(sizeof(Texture));
	tp->texture = ((Texture *)data)->texture;

	tp->name = strdup(((Texture*)data)->name);

	fprintf(stderr,NEW_TEXTURE,(void*)tp,tp->name);

	return (void *) tp;
}

void deleteTexture(void ** data){

	fprintf(stderr,DELETE_TEXTURE,*data,((Texture*)(*data))->name);

	SDL_DestroyTexture( ( (Texture*) (*data) )->texture );
	((Texture*)(*data))->texture = 0;

	free( ( (Texture*) (*data) )->name ); //TODO
	((Texture*)(*data))->name = 0;

	free(*data);
	*data = 0;

}

int equalsTexture(void * lhs, void * rhs){

	Texture * tlhs = (Texture *)lhs;
	Texture * trhs = (Texture *)rhs;

	return !strcmp(tlhs->name,trhs->name);

}

SDL_Texture * getTexture(char * name){

	Texture texture = {.texture = NULL, .name = name};

	Node * np = lookup_List(textureList,&texture);

	if(np)
		return ((Texture*)(np->data))->texture;
	else
		return NULL;

}
