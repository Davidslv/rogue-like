#include "rogue.h"

int main() {
  Player * player = playerSetup();
  int ch;
  Position * newPosition;

  Level * level;

  screenSetup();

  level = createLevel(1);

  // main game loop
  // until user presses 'q' key
  while((ch = getch()) != 'q') {
    newPosition = handleInput(ch, player);

    checkPlayerPosition(newPosition, player, level->tiles);

    moveMonsters(level);
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
