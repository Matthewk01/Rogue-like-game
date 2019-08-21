#pragma once

#include <stdbool.h>

#define MAX_BAR_COUNT 20

typedef struct Monster {
    int hp;
    int level;
    int defense;
    int HP_MAX;
    int damage;
} Monster;

Monster *monsterInit();

bool monsterIsAlive(Monster *monster);

void monsterPrintOverview(Monster *monster);

void monsterGraphicPrintHP(Monster *monster);

