CC = gcc
CFLAGS= -l ncurses -I$(IDIR)

IDIR    = ./include/
SRCDIR  = ./src/
SOURCES = $(SRCDIR)*.c

play: rogue run clean

rogue:
	$(CC) $(SOURCES) $(CFLAGS) -o $@

run:
	./rogue

clean:
	rm rogue
