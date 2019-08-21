#pragma once

#include <stdbool.h>
#include "inventory.h"

#define MAX_BAR_COUNT 20
#define INVENTORY_SLOTS 5
typedef enum PlayerClass{
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
    Item inventory[INVENTORY_SLOTS];
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

typedef struct Monster Monster;
void playerAttackMonster(Player *from, Monster *to);