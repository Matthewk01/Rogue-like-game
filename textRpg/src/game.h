#pragma once

#include "character.h"
#include "map.h"
#include "monster.h"
#include "map.h"

typedef enum GameInteractionChoice {
    MOVE_LEFT,
    MOVE_RIGHT,
    USE_ITEM,
    GO_TO_ROOM,
    BUY_ITEMS,
    SAVE_LEAVE,
    GAME_INTERACTION_CHOICE_COUNT
} GameInteractionChoice;

void gameInteractionEnumPrint();

const char *gameInteractionEnumGetString(GameInteractionChoice choice);

typedef enum FightInteractionChoice{
    FIGHT_ATTACK,
    FIGHT_RUN,
    FIGHT_COUNT
} FightInteractionChoice;

void gameFightInteractionEnumPrint();

const char *gameFightInteractionEnumGetString(FightInteractionChoice choice);

typedef struct GameState {
    Map map;
    bool gameIsRunning;
} GameState;

void gameStartFightBetween(Character *player, Monster *monster);

void gameLoop(GameState *game);

void gameInteractionMenu(GameState *game);

Character *gameCreateCharacter();

void gameStart(GameState *game);

int gameGetInputIdx(const char *str, int from, int to);

