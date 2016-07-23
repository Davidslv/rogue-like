#include "rogue.h"

int main() {
  Player * player;
  int ch;
  Position * newPosition;

  char ** level;

  screenSetup();

  mapSetup();

  level = saveLevelPositions();

  player = playerSetup();

  // main game loop
  // until user presses 'q' key
  while((ch = getch()) != 'q') {
    newPosition = handleInput(ch, player);
    checkPlayerPosition(newPosition, player, level);
  }
  endwin();

  return 0;
}

int screenSetup() {
  initscr();
  srand(time(NULL));

  printw("Hey!");
  noecho();
  refresh();

  return 1;
}

