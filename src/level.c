#include "rogue.h"

Level * createLevel(int level) {
  Level * newLevel;
  newLevel = malloc(sizeof(Level));

  newLevel->level = level;
  newLevel->numberOfRooms = 5;
  newLevel->rooms = roomsSetup();
  newLevel->tiles = saveLevelPositions();

  newLevel->player = playerSetup();

  addMonsters(newLevel);

  return newLevel;
}

Room ** roomsSetup() {
  Room ** rooms;
  rooms = malloc(sizeof(Room) * 8);

  // createRoom(y, x, height, width)

  rooms[0] = createRoom(0, 0, 5, 5);
  rooms[1] = createRoom(1, 15, 2, 10);
  rooms[2] = createRoom(7, 8, 3, 13);
  rooms[3] = createRoom(14, 25, 4, 7);
  rooms[4] = createRoom(15, 4, 3, 3);

  drawRoom(rooms[0]);
  drawRoom(rooms[1]);
  drawRoom(rooms[2]);
  drawRoom(rooms[3]);
  drawRoom(rooms[4]);


  // doors
  // 0 -> top
  // 1 -> left
  // 2 -> bottom
  // 3 -> right

  connectDoors(rooms[0]->doors[3], rooms[1]->doors[1]);
  connectDoors(rooms[1]->doors[2], rooms[2]->doors[0]);
  connectDoors(rooms[2]->doors[3], rooms[3]->doors[0]);
  connectDoors(rooms[3]->doors[1], rooms[4]->doors[3]);

  return rooms;
}

char ** saveLevelPositions() {
  int x, y;
  char ** positions;
  positions = malloc(sizeof(char *) * 25);

  for (y = 0; y < 25; y++) {

    positions[y] = malloc(sizeof(char) * 100);
    for (x = 0; x < 100; x++) {
      positions[y][x] = mvinch(y, x);
    }
  }

  return positions;
}
