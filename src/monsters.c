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
    case 1: // gobling
      return createMonster('G', 4, 2, 1, 3, 2);
    case 2: // orc
      return createMonster('O', 12, 5, 1, 4, 1);
  }
}

Monster * createMonster(char symbol, int health, int attack,
                        int speed, int defence, int pathfinding) {
  Monster * newMonster;
  newMonster = malloc(sizeof(Monster));

  newMonster->symbol = symbol;
  newMonster->health = health;
  newMonster->attack = attack;
  newMonster->speed = speed;
  newMonster->defence = defence;
  newMonster->pathfinding = pathfinding;

  return newMonster;
}

int setStartingPosition(Monster * monster, Room * room) {
  char buffer[8];

  monster->position.x = (rand() % (room->width - 2)) + room->position.x + 1;
  monster->position.y = (rand() % (room->height - 2)) + room->position.y + 1;

  sprintf(buffer, "%c", monster->symbol);

  mvprintw(monster->position.y, monster->position.x, buffer);
  return 1;
}
