#include "rogue.h"

int connectDoors(Position * doorOne, Position * doorTwo) {
  Position temp;
  Position previous;

  int count = 0;

  temp.x = doorOne->x;
  temp.y = doorOne->y;

  previous = temp;

  while(1) {
  // while (!doorOne->connected && !doorTwo->connected) {
    // We are looking into connecting doorOne with doorTwo
    // We know the current position of doorOne and doorTwo
    // from doorOne position we will be moving the cursor into a temporary position (temp)
    // while we keep the record of the position just used (previous)
    // if point north of current position is a door
    // connect doors
    // if point south of current position is a door
    // connect doors
    // if point right of current position is a door
    // coonect doors
    // if point left of current position is a door
    // connect doors

    // if (doorTwo->x)
    // We know doorTwo-x position
    // so the passage shouldn't be going further than that.


    bool moveLeft  = (abs((temp.x - 1) - doorTwo->x) < abs(temp.x - doorTwo->x));
    bool moveRight = (abs((temp.x + 1) - doorTwo->x) < abs(temp.x - doorTwo->x));
    bool moveDown  = (abs((temp.y + 1) - doorTwo->y) < abs(temp.y - doorTwo->y));
    bool moveUp    = (abs((temp.y - 1) - doorTwo->y) < abs(temp.y - doorTwo->y));

    bool leftEmptyCell  = mvinch(temp.y, temp.x - 1) == ' ';
    bool rightEmptyCell = mvinch(temp.y, temp.x + 1) == ' ';
    bool downEmptyCell  = mvinch(temp.y + 1, temp.x) == ' ';
    bool upEmptyCell    = mvinch(temp.y - 1, temp.x) == ' ';

    bool leftDoorCell  = mvinch(temp.y, temp.x - 1) == '+';
    bool rightDoorCell = mvinch(temp.y, temp.x + 1) == '+';
    bool downDoorCell  = mvinch(temp.y + 1, temp.x) == '+';
    bool upDoorCell    = mvinch(temp.y - 1, temp.x) == '+';

    // step left
    if (moveLeft && leftEmptyCell) {
      previous.x = temp.x;
      temp.x = temp.x - 1;
    }
    else if (moveRight && rightEmptyCell)
    {
      previous.x = temp.x;
      temp.x = temp.x + 1;
    }
    // step down
    else if (moveDown && downEmptyCell)
    {
      previous.y = temp.y;
      temp.y = temp.y + 1;
    }
    // step up
    else if (moveUp && upEmptyCell)
    {
      previous.y = temp.y;
      temp.y = temp.y - 1;
    }
    else {
      if (count != 0)
        return 0;

      temp = previous;
      count++;
      continue;
    }

    // getch();
    mvprintw(temp.y, temp.x, "#");
  }

  return 1;
}
