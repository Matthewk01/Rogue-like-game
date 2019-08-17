#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>


#define MAX_BAR_COUNT 20

typedef struct {
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

