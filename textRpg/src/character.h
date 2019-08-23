#pragma once

#include <stdbool.h>
#include "inventory.h"

#define MAX_BAR_COUNT 20
#define EXP_MAX 100
#define BORDER_STAR_COUNT 105
typedef enum CharacterClass {
    CLASS_KNIGHT,
    CLASS_RANGER,
    CLASS_ROGUE,
    CLASS_MAGE,
    CLASS_COUNT,
} CharacterClass;

void characterClassEnumPrint();

const char *characterClassEnumGetString(CharacterClass choice);

typedef struct Character {
    CharacterClass charClass;
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
    int currency;
    Inventory inventory;
} Character;

Character *characterInit(const char *name, CharacterClass role);

void characterFree(Character *player);

bool characterIsAlive(Character *player);

void characterCheckLevelUp(Character *player);

void characterGraphicPrintHP(Character *player);

void characterGraphicPrintExpBar(Character *player);

void characterPrintOverview(Character *playerPtr);

void characterMoveTo(Character *player, int xPosition);

typedef struct Monster Monster;

void characterAttackMonster(Character *from, Monster *to);

void playerUseItem(Character *player, int positionIdx);