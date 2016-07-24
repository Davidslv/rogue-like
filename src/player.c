#include "rogue.h"

Player * playerSetup() {
  Player * newPlayer;
  newPlayer = malloc(sizeof(Player));
  newPlayer->position = malloc(sizeof(Position));

  newPlayer->position->x = 14;
  newPlayer->position->y = 14;
  newPlayer->health = 20;

  mvprintw(newPlayer->position->y, newPlayer->position->x, "@");
  move(newPlayer->position->y, newPlayer->position->x);

  return newPlayer;
}

Position * handleInput(int input, Player * player) {
  Position * newPosition;
  newPosition = malloc(sizeof(Position));

  switch (input) {
    // move up
    case 'k':
      newPosition->y = player->position->y - 1;
      newPosition->x = player->position->x;
      break;

    // move down
    case 'j':
      newPosition->y = player->position->y + 1;
      newPosition->x = player->position->x;
      break;

    // move left
    case 'h':
      newPosition->y = player->position->y;
      newPosition->x = player->position->x - 1;
      break;

    // move right
    case 'l':
      newPosition->y = player->position->y;
      newPosition->x = player->position->x + 1;
      break;

    default:
      break;
  }

  return newPosition;
}

// checks what is at next position
int checkPlayerPosition(Position * newPosition, Player * player, char ** level) {
  switch (mvinch(newPosition->y, newPosition->x)) {
    case '.':
    case '+':
    case '#':
      playerMove(newPosition, player, level);
      break;
    default:
      move(player->position->y, player->position->x);
      break;
  }

  return 1;
}

int playerMove(Position * newPosition, Player * player, char ** level) {
  char buffer[8];

  sprintf(buffer, "%c", level[player->position->y][player->position->x]);

  mvprintw(player->position->y, player->position->x, buffer);

  player->position->y = newPosition->y;
  player->position->x = newPosition->x;

  mvprintw(player->position->y, player->position->x, "@");
  move(player->position->y, player->position->x);

  return 1;
}
