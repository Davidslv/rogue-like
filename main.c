#include <stdlib.h>
#include <ncurses.h>

typedef struct Room {
  int xPosition;
  int yPosition;
  int height;
  int width;

  // Monster ** monsters;
  // Item ** items;
} Room;

typedef struct Player {
  int xPosition;
  int yPosition;
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

  newRoom->xPosition = x;
  newRoom->yPosition = y;

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
  for (x = room->xPosition; x < room->xPosition + room->width; x++) {
    // top
    mvprintw(room->yPosition, x, "-");
    // bottom
    mvprintw(room->yPosition + room->height -1, x, "-");
  }

  // floor & side walls
  for (y = room->yPosition + 1; y < room->yPosition + room->height - 1; y++) {
    // draw side walls
    mvprintw(y, room->xPosition, "|");
    mvprintw(y, room->xPosition + room->width - 1, "|");

    // draw floors
    for (x = room->xPosition + 1; x < room->xPosition + room->width - 1; x++) {
      mvprintw(y, x, ".");
    }
  }

  return 1;
}

Player * playerSetup() {
  Player * newPlayer;
  newPlayer = malloc(sizeof(Player));

  newPlayer->xPosition = 14;
  newPlayer->yPosition = 14;
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
      newY = player->yPosition - 1;
      newX = player->xPosition;
      break;

    // move down
    case 'j':
      newY = player->yPosition + 1;
      newX = player->xPosition;
      break;

    // move left
    case 'h':
      newY = player->yPosition;
      newX = player->xPosition - 1;
      break;

    // move right
    case 'l':
      newY = player->yPosition;
      newX = player->xPosition + 1;
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
      move(player->yPosition, player->xPosition);
      break;
  }

  return 1;
}

int playerMove(int y, int x, Player * player) {
  mvprintw(player->yPosition, player->xPosition, ".");

  player->yPosition = y;
  player->xPosition = x;

  mvprintw(player->yPosition, player->xPosition, "@");
  move(player->yPosition, player->xPosition);

  return 1;
}
