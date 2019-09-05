#include "Parser.h"
#include "Strings.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <errno.h>


static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;
static const int BUFF_SIZE = 256;

int main( int argc, char* argv[] )
{
  SDL_Event event;

  bool running = false;

  Parser * parser;
  /* Filename passed at command line. */
  char * fName;

  /* File pointer. */
  FILE * file;

  /* Iterator. */
  int i;

  SDL_Window* window = NULL;

  SDL_Renderer * renderer = NULL;

  SDL_Surface* screenSurface = NULL;

  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    
    fprintf(stderr,SDL_INIT_FAIL,SDL_GetError());
  
  }else{

    window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, 
    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

    if( window == NULL ){
      
      fprintf(stderr,SDL_WINDOW_FAIL,SDL_GetError());
    
    }else{

      renderer = SDL_CreateRenderer(window, -1, 0);

      screenSurface = SDL_GetWindowSurface( window );

      SDL_FillRect( screenSurface, NULL, 
      SDL_MapRGB( screenSurface->format,0x2F,0x2F,0x2F));

      SDL_UpdateWindowSurface( window );

      SDL_Delay( 10000 );

    }

    /* GAME INITIALIZATION ---------------------------------------------------*/
    
    /* Set the running state to true, then enter the poll event loop */
    running = true;

    /* START GAME LOOP -------------------------------------------------------*/
    /* -----------------------------------------------------------------------*/
    while(running){

      while (SDL_PollEvent (&event)) {

      /* Event Types */
        if(event.type == SDL_QUIT){
	  running = false;
        }

      }

    }
    /* END GAME LOOP ---------------------------------------------------------*/
    /* -----------------------------------------------------------------------*/

    /* Clean up SDL objects. */
    SDL_FreeSurface( screenSurface );
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );
    SDL_Quit();
    
    renderer = 0;
    window = 0;
    screenSurface = 0;

  }



  /* Line buffer, to be processed, initialized null. */
  char line [BUFF_SIZE]; i = 0;
  while(i < BUFF_SIZE) { line[i] = '\0'; i++; }	

  /* Make sure we recieve a filename. */
  if(argc == 1){
    fprintf(stdout,STDIN_USAGE);
    fgets(line, BUFF_SIZE, stdin);

    return 0;

    /* Incorrect usage. */
  }else if(argc > 2){
    fprintf(stdout,WRONG_USAGE);
  }

  /* Get name from args. */
  fName = argv[1];

  errno = 0;
  /* File Mode. */
  file = fopen(fName,FILE_PERMISSIONS);

  if(!file){
    fprintf(stderr,FILE_FAIL,fName,strerror(errno));
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

  file = 0;


  return 0;
}
