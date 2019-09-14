LINKER_FLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image

driver: driver.o Parser.o Texture.o Gamecore.o
	gcc Parser.o Texture.o Gamecore.o driver.o $(LINKER_FLAGS) -Wall -Wno-long-long -pedantic \
	-o driver

valgrind: driver
	valgrind --leak-check=full --read-var-info=yes --show-reachable=yes \
	./driver $(FILE)

Gamecore.o: Gamecore.c Gamecore.h Strings.h
	gcc -Wall -Wno-long-long -pedantic -c -g Gamecore.c

Texture.o: Texture.c Texture.h Strings.h
	gcc -Wall -Wno-long-long -pedantic -c -g Texture.c

Parser.o: Parser.c Parser.h Strings.h
	gcc -Wall -Wno-long-long -pedantic -c -g Parser.c

driver.o: driver.c Strings.h
	gcc -Wall -Wno-long-long -pedantic -c -g driver.c

clean:
	rm -f *.o *.s *.exe* driver *~
	find . -type f -name "*.sw[klmnop]" -delete

new:
	make clean
	make driver
