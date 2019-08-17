#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define MAX_BAR_COUNT 20

typedef enum {
    KNIGHT,
    RANGER,
    ROGUE,
    MAGE,
    ERR
} PlayerClass;

typedef struct Player {
    PlayerClass charClass;
    char *name;
    int hp;
    int HP_MAX;
    int damage;
    int defense;
    bool isAI;
    int level;
    int experiences;
    int positionX;
    //Inventory
} Player;

const char *playerPrintType(PlayerClass type);

Player *playerInit(const char *name, PlayerClass role);

void playerFree(Player *player);

bool playerIsAlive(Player *player);

void playerCheckLevelUp(Player *player);

void playerGraphicPrintHP(Player *player);

void playerPrintOverview(Player *playerPtr);

PlayerClass playerParseClass(const char *cls);

void playerMoveTo(Player *player, int xPosition);