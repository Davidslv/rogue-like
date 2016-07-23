#include <stdlib.h>
#include <ncurses.h>

typedef struct Player {
  int xPosition;
  int yPosition;
  int health;
} Player;

int screenSetup();
int mapSetup();

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

int mapSetup() {
  // y, x, chars
  mvprintw(13, 13, "--------");
  mvprintw(14, 13, "|......|");
  mvprintw(15, 13, "|......|");
  mvprintw(16, 13, "|......|");
  mvprintw(17, 13, "|......|");
  mvprintw(18, 13, "--------");

  mvprintw(3, 40, "--------");
  mvprintw(4, 40, "|......|");
  mvprintw(5, 40, "|......|");
  mvprintw(6, 40, "|......|");
  mvprintw(7, 40, "|......|");
  mvprintw(8, 40, "--------");

  mvprintw(10, 40, "------------");
  mvprintw(11, 40, "|..........|");
  mvprintw(12, 40, "|..........|");
  mvprintw(13, 40, "|..........|");
  mvprintw(14, 40, "|..........|");
  mvprintw(15, 40, "------------");

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
