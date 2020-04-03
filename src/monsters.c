#include "rogue.h"

// maximum number of monsters is 6
// one monster per room, and maximum number of rooms is 6
// that's where the number comes from
int addMonsters(Level * level) {
  int x;
  level->monsters = malloc(sizeof(Monster *) * 6);
  level->numberOfMonsters = 0;

  for (int x = 0; x < level->numberOfRooms; x++) {
    if ((rand() % 2) == 0) {

      level->monsters[level->numberOfMonsters] = selectMonster(level->level);
      setStartingPosition(level->monsters[level->numberOfMonsters], level->rooms[x]);

      level->numberOfMonsters++;
    }
  }
  return 1;
}

Monster * selectMonster(int level) {
  int monster;

  switch (level) {
    case 1:
    case 2:
    case 3:
      monster = rand() % 2;
      break;
    case 4:
    case 5:
      monster = rand() % 2 + 1;
      break;
    case 6:
      // Orc
      monster = 2;
      break;
  }

  switch (monster) {
    case 0: // snake
    default:
      return createMonster('S', 2, 1, 1, 1, 1);
    // case 1: // gobling
      // return createMonster('G', 4, 2, 1, 3, 2);
    case 2: // orc
      return createMonster('O', 12, 5, 1, 4, 1);
  }
}

Monster * createMonster(char symbol, int health, int attack,
                        int speed, int defence, int pathfinding) {
  Monster * newMonster;
  newMonster = malloc(sizeof(Monster));
  newMonster->position = malloc(sizeof(Position));

  newMonster->symbol = symbol;
  newMonster->health = health;
  newMonster->attack = attack;
  newMonster->speed = speed;
  newMonster->defence = defence;
  newMonster->pathfinding = pathfinding;

  sprintf(newMonster->string, "%c", symbol);

  return newMonster;
}

int setStartingPosition(Monster * monster, Room * room) {
  monster->position->x = (rand() % (room->width - 2)) + room->position.x + 1;
  monster->position->y = (rand() % (room->height - 2)) + room->position.y + 1;

  mvprintw(monster->position->y, monster->position->x, monster->string);
  return 1;
}

int moveMonsters(Level * level) {

  for (int x = 0; x < level->numberOfMonsters ; x++) {

    if (level->monsters[x]->pathfinding == 1) {
      // random
    }
    else {
      Monster * monster = level->monsters[x];

      pathfindingSeek(monster->position, level->player->position);
      mvprintw(monster->position->y, monster->position->y, monster->string);
    }

  }

  return 1;
}

// TODO: Refactor for DRY
int pathfindingSeek(Position * start, Position * destination) {
  // step left
  if ((abs((start->x - 1) - destination->x) < abs(start->x - destination->x)) && (mvinch(start->y, start->x - 1) == '.')) {
    start->x = start->x - 1;
  }
  // step right
  else if ((abs((start->x + 1) - destination->x) < abs(start->x - destination->x)) && (mvinch(start->y, start->x + 1) == '.'))
  {
    start->x = start->x + 1;
  }
  // step down
  else if ((abs((start->y + 1) - destination->y) < abs(start->y - destination->y)) && (mvinch(start->y + 1, start->x) == '.'))
  {
    start->y = start->y + 1;
  }
  // step up
  else if ((abs((start->y - 1) - destination->y) < abs(start->y - destination->y)) && (mvinch(start->y - 1, start->x) == '.'))
  {
    start->y = start->y - 1;
  }
  else {
    // do nothing
  }

  return 1;
}
