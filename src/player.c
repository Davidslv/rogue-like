#include "rogue.h"

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
    case '+':
    case '#':
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
