#pragma once

#include <stdbool.h>

#define MAX_BAR_COUNT 20

typedef enum PlayerType {
    KNIGHT,
    RANGER,
    ROGUE,
    MAGE
} PlayerType;

typedef struct {
    PlayerType role;
    char *name;
    int hp;
    int HP_MAX;
    int damage;
    int defense;
    bool isAI;
    int level;
    int experiences;
    //Inventory
} Player;

const char *printPlayerType(PlayerType type);

Player *initPlayer(const char *name, PlayerType role);

void freePlayer(Player *player);

bool isAlive(Player *player);

void attackPlayer(Player *from, Player *to);

void checkLevelUp(Player *player);

void showGraphicHP(Player *player);

void printPlayer(Player *playerPtr);
