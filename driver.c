#include "Parser.h" /* Header File Soon. */

#include <SDL2/SDL.h>
#include <stdio.h>

/* Catastrophic. */
static const char FILE_FAIL [] = "File failed to open, exiting program.\n";

static const char WRONG_USAGE [] = "Incorrect usage: Parser <fileame>\n";

static const char STDIN_USAGE [] = "Standarad Input mode:\n";

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;
static const int BUFF_SIZE = 256;

int main( int argc, char* argv[] )
{
  Parser * parser;
  /* Filename passed at command line. */
  char * fName;

  /* File pointer. */
  FILE * file;

  /* Iterator. */
  int i;

  SDL_Window* window = NULL;

  SDL_Surface* screenSurface = NULL;

  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
  }
  else
  {
    window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, 
    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

    if( window == NULL )
    {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
      screenSurface = SDL_GetWindowSurface( window );

      SDL_FillRect( screenSurface, NULL, 
      SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

      SDL_UpdateWindowSurface( window );

      SDL_Delay( 1000 );
    }

    
    SDL_DestroyWindow( window );

    SDL_Quit();
  }



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
