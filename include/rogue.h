#ifndef ROGUE_H
#define ROGUE_H

#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

typedef struct Level {
  int level;
  char ** tiles;

  int numberOfRooms;
  int numberOfMonsters;

  struct Room ** rooms;
  struct Monster ** monsters;
} Level;

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

typedef struct Monster {
  Position position;

  char symbol;
  int health;
  int attack;
  int defence;
  int speed;
  int pathfinding;

} Monster;

int screenSetup();

// level functions
Room ** roomsSetup();
char ** saveLevelPositions();
Level * createLevel(int level);

Room * createRoom(int y, int x, int height, int width);
int drawRoom(Room * room);
int connectDoors(Position * doorOne, Position * doorTwo);

// player functions
Player * playerSetup();
Position * handleInput(int input, Player * player);
int checkPlayerPosition(Position * newPosition, Player * player, char ** level);
int playerMove(Position * newPosition, Player * player, char ** level);
#endif
