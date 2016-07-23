CFLAGS=-Wall -g

clean:
	rm -f main

create:
	make clean
	gcc main.c -l ncurses -o rogue
