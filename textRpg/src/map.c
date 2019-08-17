#include "map.h"

void mapPrint(Map *map) {
    printf("World: ");
    for (int i = 0; i < ROOM_COUNT; ++i) {
        if (i != 0) {
            printf("---");

        }
        if (map->player->positionX == i) {
            printf(">P<");
        } else {
            putchar('O');
        }
    }
    putchar('\n');
    for (int i = 0; i < 90; ++i) putchar('*');
    putchar('\n');
}

void mapRoomsInit(Map *map) {
    for (int i = 0; i < ROOM_COUNT; ++i) {
        map->rooms[i].monster.level = i + 1;
        map->rooms[i].monster.hp = 50 + i * 10;
        map->rooms[i].monster.HP_MAX = 50 + i * 10;
        map->rooms[i].monster.defense = 10 + i * 5;
        map->rooms[i].monster.damage = 5 + i * 3;
    }
}

bool mapPlayerMove(Player *player, int dir) {
    int newPosX = player->positionX + dir;
    // Check for collisions
    if (newPosX >= 0 && newPosX < ROOM_COUNT) {
        playerMoveTo(player, newPosX);
        return true;
    }
    return false;
}
