#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

typedef struct Position {
  int x, y;
} Position;

typedef struct Room {
  Position position;
  int height;
  int width;

  Position ** doors;

  // Monster ** monsters;
  // Item ** items;
} Room;

typedef struct Player {
  Position position;
  int health;
} Player;

int screenSetup();

// room functions
Room ** mapSetup();
Room * createRoom(int y, int x, int height, int width);
int drawRoom(Room * room);
int connectDoors(Position * doorOne, Position * doorTwo);

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
  srand(time(NULL));

  printw("Hey!");
  noecho();
  refresh();

  return 1;
}

// room functions
Room * createRoom(int y, int x, int height, int width) {
  Room * newRoom;
  newRoom = malloc(sizeof(Room));

  newRoom->position.x = x;
  newRoom->position.y = y;

  newRoom->height = height;
  newRoom->width = width;

  newRoom->doors = malloc(sizeof(Position) * 4);

  // top door
  newRoom->doors[0] = malloc(sizeof(Position));
  newRoom->doors[0]->x = rand() % (width - 2) + newRoom->position.x + 1;
  newRoom->doors[0]->y = newRoom->position.y;

  // left door
  newRoom->doors[1] = malloc(sizeof(Position));
  newRoom->doors[1]->x = newRoom->position.x;
  newRoom->doors[1]->y = rand() % (height - 2) + newRoom->position.y + 1;

  // bottom door
  newRoom->doors[2] = malloc(sizeof(Position));
  newRoom->doors[2]->x = rand() % (width - 2) + newRoom->position.x + 1;
  newRoom->doors[2]->y = newRoom->position.y + (newRoom->height - 1);

  // right door
  newRoom->doors[3] = malloc(sizeof(Position));
  newRoom->doors[3]->x = newRoom->position.x + (width - 1);
  newRoom->doors[3]->y = rand() % (height - 2) + newRoom->position.y + 1;

  return newRoom;
}

Room ** mapSetup() {
  Room ** rooms;
  rooms = malloc(sizeof(Room) * 6);

  rooms[0] = createRoom(13, 13, 6, 8);
  drawRoom(rooms[0]);

  rooms[1] = createRoom(2, 40, 6, 8);
  drawRoom(rooms[1]);

  rooms[2] = createRoom(10, 40, 6, 12);
  drawRoom(rooms[2]);

  connectDoors(rooms[0]->doors[3], rooms[2]->doors[1]);
  connectDoors(rooms[1]->doors[2], rooms[0]->doors[0]);

  return rooms;
}

int drawRoom(Room * room) {
  int x, y;

  // top and bottom
  for (x = room->position.x; x < room->position.x + room->width; x++) {
    // top
    mvprintw(room->position.y, x, "-");
    // bottom
    mvprintw(room->position.y + room->height -1, x, "-");
  }

  // floor & side walls
  for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++) {
    // draw side walls
    mvprintw(y, room->position.x, "|");
    mvprintw(y, room->position.x + room->width - 1, "|");

    // draw floors
    for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++) {
      mvprintw(y, x, ".");
    }
  }

  // draw doors
  mvprintw(room->doors[0]->y, room->doors[0]->x, "+");
  mvprintw(room->doors[1]->y, room->doors[1]->x, "+");
  mvprintw(room->doors[2]->y, room->doors[2]->x, "+");
  mvprintw(room->doors[3]->y, room->doors[3]->x, "+");

  return 1;
}


int connectDoors(Position * doorOne, Position * doorTwo) {
  Position temp;
  Position previous;

  int count = 0;

  temp.x = doorOne->x;
  temp.y = doorOne->y;

  previous = temp;

  while (1) {
    // step left
    if ((abs((temp.x - 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && (mvinch(temp.y, temp.x - 1) == ' ')) {
      previous.x = temp.x;
      temp.x = temp.x - 1;
    }
    // step right
    else if ((abs((temp.x + 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && (mvinch(temp.y, temp.x + 1) == ' '))
    {
      previous.x = temp.x;
      temp.x = temp.x + 1;
    }
    // step down
    else if ((abs((temp.y + 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && (mvinch(temp.y + 1, temp.x) == ' '))
    {
      previous.y = temp.y;
      temp.y = temp.y + 1;
    }
    // step up
    else if ((abs((temp.y - 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && (mvinch(temp.y - 1, temp.x) == ' '))
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

    mvprintw(temp.y, temp.x, "#");

    getch();
  }

  return 1;
}

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
