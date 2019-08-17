#pragma once

#include <stdbool.h>

#define MAX_BAR_COUNT 20

typedef enum {
    KNIGHT,
    RANGER,
    ROGUE,
    MAGE
} CharacterClass;

typedef struct {
    CharacterClass role;
    char *name;
    int hp;
    int HP_MAX;
    int damage;
    int defense;
    bool isAI;
    int level;
    int experiences;
    //Inventory
} Character;

const char *printPlayerType(CharacterClass type);

Character *initPlayer(const char *name, CharacterClass role);

void freePlayer(Character *player);

bool isAlive(Character *player);

void attackPlayer(Character *from, Character *to);

void checkLevelUp(Character *player);

void showGraphicHP(Character *player);

void printPlayer(Character *playerPtr);
