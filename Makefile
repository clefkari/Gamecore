#OBJS specifies which files to compile as part of the project
OBJS = Parser.c

#Debug for valgrind
DEBUG = mesa.txt

#CC specifies which compiler we're using
CC = gcc

MINGW = -I/usr/include -L/usr/lib

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\sdlming\include\SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\sdlming\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -w -Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = driver

#FILE_
FILE = cse12.txt

#This is the target that compiles our executable
#all: $(OBJS)
#	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
#
# START OF MAKEFILE #

driver: Parser.o
	gcc Parser.o -o driver

valgrind: driver
	valgrind --leak-check=full --read-var-info=yes --show-reachable=yes ./driver $(FILE)

Parser.o: $(OBJS)
	gcc -Wall -Wno-long-long -pedantic -c -g $(OBJS)

clean:
	rm -f *.o driver
	find . -type f -name "*.sw[klmnop]" -delete

new:
	make clean
	make driver
