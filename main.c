#include <stdlib.h>
#include <ncurses.h>

typedef struct Position {
  int x, y;
} Position;

typedef struct Room {
  Position position;
  int height;
  int width;

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

Player * playerSetup();
int handleInput(int input, Player * player);
int playerMove(int y, int x, Player * player);
int checkPlayerPosition(int newY, int newX, Player * player);

int main() {
  Player * player;
  int ch;
  screenSetup();

  mapSetup();

  player = playerSetup();

  // main game loop
  // until user presses 'q' key
  while((ch = getch()) != 'q') {
    handleInput(ch, player);
  }
  endwin();

  return 0;
}

int screenSetup() {
  initscr();
  printw("Hey!");
  noecho();
  refresh();

  return 1;
}

// room functions
Room * createRoom(int y, int x, int height, int width) {
  Room * newRoom;
  newRoom = malloc(sizeof(Room));

  newRoom->position.x = x;
  newRoom->position.y = y;

  newRoom->height = height;
  newRoom->width = width;

  return newRoom;
}

Room ** mapSetup() {
  Room ** rooms;
  rooms = malloc(sizeof(Room) * 6);

  rooms[0] = createRoom(13, 13, 6, 8);
  drawRoom(rooms[0]);

  rooms[1] = createRoom(2, 40, 6, 8);
  drawRoom(rooms[1]);

  rooms[2] = createRoom(10, 40, 6, 12);
  drawRoom(rooms[2]);

  return rooms;
}

int drawRoom(Room * room) {
  int x, y;

  // top and bottom
  for (x = room->position.x; x < room->position.x + room->width; x++) {
    // top
    mvprintw(room->position.y, x, "-");
    // bottom
    mvprintw(room->position.y + room->height -1, x, "-");
  }

  // floor & side walls
  for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++) {
    // draw side walls
    mvprintw(y, room->position.x, "|");
    mvprintw(y, room->position.x + room->width - 1, "|");

    // draw floors
    for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++) {
      mvprintw(y, x, ".");
    }
  }

  return 1;
}

Player * playerSetup() {
  Player * newPlayer;
  newPlayer = malloc(sizeof(Player));

  newPlayer->position.x = 14;
  newPlayer->position.y = 14;
  newPlayer->health = 20;

  playerMove(14, 14, newPlayer);

  return newPlayer;
}

int handleInput(int input, Player * player) {
  int newY; // new y position
  int newX; // new x position

  switch (input) {
    // move up
    case 'k':
      newY = player->position.y - 1;
      newX = player->position.x;
      break;

    // move down
    case 'j':
      newY = player->position.y + 1;
      newX = player->position.x;
      break;

    // move left
    case 'h':
      newY = player->position.y;
      newX = player->position.x - 1;
      break;

    // move right
    case 'l':
      newY = player->position.y;
      newX = player->position.x + 1;
      break;

    default:
      break;
  }

  checkPlayerPosition(newY, newX, player);
  return 1;
}

// checks what is at next position
int checkPlayerPosition(int newY, int newX, Player * player) {
  switch (mvinch(newY, newX)) {
    case '.':
      playerMove(newY, newX, player);
      break;
    default:
      move(player->position.y, player->position.x);
      break;
  }

  return 1;
}

int playerMove(int y, int x, Player * player) {
  mvprintw(player->position.y, player->position.x, ".");

  player->position.y = y;
  player->position.x = x;

  mvprintw(player->position.y, player->position.x, "@");
  move(player->position.y, player->position.x);

  return 1;
}
