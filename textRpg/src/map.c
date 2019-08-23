#include <stdio.h>
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
    int multiplier = 3;
    for (int i = 0; i < ROOM_COUNT; ++i) {
        map->rooms[i].monster.level = i + 1;
        map->rooms[i].monster.hp = 50 + i * multiplier;
        map->rooms[i].monster.HP_MAX = 50 + i * multiplier;
        map->rooms[i].monster.defense = 5 + i * multiplier;
        map->rooms[i].monster.damage = 8 + i * multiplier;
    }
}

bool mapPlayerMove(Character *player, int dir) {
    int newPosX = player->positionX + dir;
    // Check for collisions
    if (newPosX >= 0 && newPosX < ROOM_COUNT) {
        characterMoveTo(player, newPosX);
        return true;
    }
    return false;
}
