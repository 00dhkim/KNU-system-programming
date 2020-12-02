
all: snake_lib.o main.o
	gcc -W -Wall -o main main.o snake_lib.o -g -lcurses

snake_lib.o: snake_lib.c
	gcc -W -Wall -c snake_lib.c -o snake_lib.o -g -lcurses

main.o: main.c
	gcc -W -Wall -c main.c -o main.o -g

clean: 
	rm *.o
