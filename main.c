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
  mvprintw(14, 13, "|------|");
  mvprintw(15, 13, "|------|");
  mvprintw(16, 13, "|------|");
  mvprintw(17, 13, "|------|");
  mvprintw(18, 13, "--------");

  mvprintw(3, 40, "--------");
  mvprintw(4, 40, "|------|");
  mvprintw(5, 40, "|------|");
  mvprintw(6, 40, "|------|");
  mvprintw(7, 40, "|------|");
  mvprintw(8, 40, "--------");

  mvprintw(10, 40, "------------");
  mvprintw(11, 40, "|----------|");
  mvprintw(12, 40, "|----------|");
  mvprintw(13, 40, "|----------|");
  mvprintw(14, 40, "|----------|");
  mvprintw(15, 40, "------------");

  return 0;
}

Player * playerSetup() {
  Player * newPlayer;
  newPlayer = malloc(sizeof(newPlayer));

  newPlayer->xPosition = 14;
  newPlayer->yPosition = 14;
  newPlayer->health = 20;

  playerMove(14, 14, newPlayer);

  return newPlayer;
}

int handleInput(int input, Player * player) {
  switch (input) {
    // move up
    case 'k':
      playerMove(player->yPosition - 1, player->xPosition, player);
      break;

    // move down
    case 'j':
      playerMove(player->yPosition + 1, player->xPosition, player);
      break;

    // move left
    case 'h':
      playerMove(player->yPosition, player->xPosition - 1, player);
      break;

    // move right
    case 'l':
      playerMove(player->yPosition, player->xPosition + 1, player);
      break;

    default:
      break;
  }

  return 0;
}

int playerMove(int y, int x, Player * player) {
  mvprintw(player->yPosition, player->xPosition, ".");

  player->yPosition = y;
  player->xPosition = x;

  mvprintw(player->yPosition, player->xPosition, "@");
  move(player->yPosition, player->xPosition);

  return 0;
}
