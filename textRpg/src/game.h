#pragma once

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "character.h"
#include "map.h"
#include "monster.h"
#include "map.h"

bool gameIsRunning;

Map map;

typedef enum {
    ATTACK,
    RUN,
} FightInteractionChoice;

void gameStartFightBetween(Player *player, Monster *monster);

FightInteractionChoice gameFightInteractionMenu();

void gameLoop();

void gamePlayerAttack(Player *from, Monster *to);

void gameMonsterAttack(Monster *from, Player *to);

void gameMapInteractionMenu();

Player* gameCreateCharacter();

