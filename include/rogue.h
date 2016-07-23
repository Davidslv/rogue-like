#ifndef ROGUE_H
#define ROGUE_H

#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

typedef struct Position {
  int x, y;
} Position;

typedef struct Room {
  Position position;
  int height;
  int width;

  Position ** doors;

  // Monster ** monsters;
  // Item ** items;
} Room;

typedef struct Player {
  Position position;
  int health;
} Player;

int screenSetup();

// room functions
Room ** mapSetup();
Room * createRoom(int y, int x, int height, int width);
int drawRoom(Room * room);
int connectDoors(Position * doorOne, Position * doorTwo);

Player * playerSetup();
int handleInput(int input, Player * player);
int playerMove(int y, int x, Player * player);
int checkPlayerPosition(int newY, int newX, Player * player);
#endif
