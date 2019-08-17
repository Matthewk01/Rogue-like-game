#pragma  once

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "character.h"
#include "map.h"

typedef enum enemyInteractionChoice {
    ATTACK,
    RUN,
} enemyInteractionChoice;

void startFight(Character *player1, Character *player2);

enemyInteractionChoice interactionMenu();
