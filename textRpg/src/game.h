#pragma  once

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "character.h"
#include "map.h"

bool gameIsRunning = true;

typedef enum enemyInteractionChoice {
    ATTACK,
    RUN,
} enemyInteractionChoice;

void startFight(Player *player, Monster *monster);

enemyInteractionChoice interactionMenu();

void gameLoop();
