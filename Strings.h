/* Basic. */

#define NEW_TEXTURE "%p Texture constructed: %s.\n"
#define DELETE_TEXTURE "%p Texture destructed: %s.\n"

#define NEW_NODE "%p New node constructed.\n"
#define DELETE_NODE "%p Node destructed.\n"
#define LIST_MADE "%p List %ld constructed\n"
#define PARSER_MADE "%p Parser constructed\n"
#define DELETE_PARSER "%p Parser destructed\n"
#define DELETE_LIST "%p List %ld destructed\n"
#define NO_FRONT "%p List %ld NULL front pointer\n"
#define OCCUPANCY "Occupancy: %ld\n"

/* File */
#define TEXTURE_FORMAT "./Textures/%s"
#define TEXTURE_DIR "./Textures"
#define FILE_PERMISSIONS "r"

/* Catastrophic. */
#define SURFACE_FAIL "Surface %s failed to load.\n"
#define TEXTURE_FAIL "Texture %s failed to load.\n"
#define DIR_FAIL "Directory %s failed to open: %s.\n"
#define FILE_FAIL "File %s failed to open: %s.\n"
#define WRONG_USAGE "Incorrect usage: Parser <fileame>\n"
#define STDIN_USAGE "Standarad Input mode:\n"
#define SDL_INIT_FAIL "SDL could not initialize! SDL_Error: %s\n"
#define SDL_WINDOW_FAIL "Window could not be created! SDL_Error: %s\n"
