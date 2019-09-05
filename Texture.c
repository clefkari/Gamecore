#include "Texture.h"
#include "Strings.h"
#include <errno.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

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
	textureList = new_List(&copyTexture,&deleteTexture);
	
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

		surface = IMG_Load(de->d_name);

		if(!surface){

			failures++;
			fprintf(stderr,TEXTURE_FAIL,de->d_dname);
		
		}else{
			texture.texture = 
			insert_List(textureList,(void*)texture);

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

	return (void *) tp;
}

void deleteTexture(void ** data){

	SDL_DestroyTexture( ( (Texture*) (*data) )->texture );
	free( ( (Texture*) (*data) )->name );
	((Texture*)(*data))->texture = 0;
	((Texture*)(*data))->name = 0;

}
