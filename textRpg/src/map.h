#pragma  once

#include "monster.h"
#include "character.h"

#define ROOM_COUNT 5


typedef struct Room {
    Monster monster;
} Room;

typedef struct Map {
    int playerPosition;
    Player *player;
    Room rooms[ROOM_COUNT];
} Map;

void mapRoomsInit(Map *map);

void mapPrint(Map *map);

bool mapPlayerMove(Player *player, int dir);