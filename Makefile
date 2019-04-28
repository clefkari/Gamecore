driver: driver.o Parser.o
	gcc Parser.o driver.o -lSDL2 -Wall -Wno-long-long -pedantic -o driver

valgrind: driver
	valgrind --leak-check=full --read-var-info=yes --show-reachable=yes \
	./driver $(FILE)

Parser.o: Parser.c Parser.h
	gcc -Wall -Wno-long-long -pedantic -c -g Parser.c

driver.o: driver.c
	gcc -Wall -Wno-long-long -pedantic -c -g driver.c

clean:
	rm -f *.o *.s driver
	find . -type f -name "*.sw[klmnop]" -delete

new:
	make clean
	make driver
