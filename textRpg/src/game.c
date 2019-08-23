#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"

void gameInteractionEnumPrint() {
    printf("Decide what to do:\n");
    for (int i = 0; i < GAME_INTERACTION_CHOICE_COUNT; ++i) {
        if (i) putchar(' ');
        printf("%d) %s", i + 1, gameInteractionEnumGetString(i));
    }
    putchar('\n');
}

const char *gameInteractionEnumGetString(GameInteractionChoice choice) {
    const char *choiceStr;
    switch (choice) {
        case MOVE_LEFT:
            choiceStr = "Move left!";
            break;
        case MOVE_RIGHT:
            choiceStr = "Move right!";
            break;
        case USE_ITEM:
            choiceStr = "Use item!";
            break;
        case GO_TO_ROOM:
            choiceStr = "Go to the room!";
            break;
        case SAVE_LEAVE:
            choiceStr = "Leave and save the game!";
            break;
        default:
            choiceStr = "Error!";
            break;
    }
    return choiceStr;
}

Character *gameCreateCharacter() {
    // Get name
    const int MAX_LENGTH = 20;
    printf("Choose name:\n");
    char name[MAX_LENGTH];
    bool leaveRequested;
    do {
        printf(">> ");
        if (scanf("%20s", name) != 1) {
            printf("Wrong input!");
            leaveRequested = false;
            while (getchar() != '\n') {}
        } else {
            leaveRequested = true;
        }
        putchar('\n');
    } while (!leaveRequested);

    // Get class
    characterClassEnumPrint();
    CharacterClass class = (CharacterClass) gameGetInputIdx("", 1, CLASS_COUNT);
    return characterInit(name, class);
}

void gameStartFightBetween(Character *player, Monster *monster) {
    putchar('\n');
    printf("Fight initiated!\n");
    while (characterIsAlive(player) && monsterIsAlive(monster)) {
        // Print player overview
        putchar('\n');
        characterPrintOverview(player);
        printf("VS\n");
        monsterPrintOverview(monster);

        // Print choices
        gameFightInteractionEnumPrint();

        // Handle choice
        switch ((FightInteractionChoice) gameGetInputIdx("", 1, FIGHT_COUNT)) {
            case FIGHT_ATTACK:
                characterAttackMonster(player, monster);
                break;
            case FIGHT_RUN:
                printf("Player %s decides to run away!\n", player->name);
                return;
            default:
                printf("Error: Undefined choice.\n");
                break;
        }

        // Monster attack
        monsterAttackPlayer(monster, player);

        // Check whether someone died
        if (!monsterIsAlive(monster)) {
            printf("'%s' wins the fight!\n", player->name);
            int exp = monster->level * 60;
            player->experiences += exp;
            printf("You've gained %d experiences!\n", exp);
            characterCheckLevelUp(player);
            return;
        } else if (!characterIsAlive(player)) {
            printf("Monster managed to defeat you!\n");
            return;
        }

        // Wait for 250ms
        Sleep(250);
    }
}

void gameInteractionMenu(GameState *game) {
    gameInteractionEnumPrint();
    switch (gameGetInputIdx("", 1, GAME_INTERACTION_CHOICE_COUNT)) {
        case MOVE_LEFT:
            if (mapPlayerMove(game->map.player, -1)) {
                printf("You've moved to the left!\n");
            } else {
                printf("You can't go this way!\n");
            }
            break;
        case MOVE_RIGHT:
            if (mapPlayerMove(game->map.player, 1)) {
                printf("You've moved to the right!\n");
            } else {
                printf("You can't go this way!\n");
            }
            break;
        case USE_ITEM:
            printf("Which one?\n");
            inventoryUseItem(game->map.player, gameGetInputIdx("", 0, 5));
            break;
        case GO_TO_ROOM:
            printf("You've gone to the room!\n");
            gameStartFightBetween(game->map.player, &game->map.rooms[game->map.player->positionX].monster);
            break;
        case SAVE_LEAVE:
            game->gameIsRunning = false;
            break;
        default:
            printf("Wrong input!\n");
            break;
    }
}

// ******************************************************************************************************
void gameLoop(GameState *game) {
    while (game->gameIsRunning) {
        // render playerOverview
        characterPrintOverview(game->map.player);
        // render map
        mapPrint(&game->map);
        // render choiceMenu
        gameInteractionMenu(game);
    }
    characterFree(game->map.player);

}
// ******************************************************************************************************

void gameStart(GameState *game) {
    // load save file, otherwise create new Character
    game->gameIsRunning = true;
    game->map.player = gameCreateCharacter();
    game->map.player->inventory[0] = ITEM_HP_POTION;
    mapRoomsInit(&game->map);
    // Start game loop
    gameLoop(game);
}

int gameGetInputIdx(const char *str, int from, int to) {
    bool leaveRequested;
    int input;
    if (strcmp(str, "") != 0) {
        printf("%s\n", str);
    }
    do {
        printf(">> ");
        if (scanf("%d", &input) != 1 || input < from || input > to) {
            printf("Wrong input!");
            leaveRequested = false;
            while (getchar() != '\n') {}
        } else {
            leaveRequested = true;
        }
        putchar('\n');
    } while (!leaveRequested);
    return input - 1;
}

const char *gameFightInteractionEnumGetString(FightInteractionChoice choice) {
    const char *choiceStr;
    switch (choice) {
        case FIGHT_ATTACK:
            choiceStr = "Attack!";
            break;
        case FIGHT_RUN:
            choiceStr = "Run away!";
            break;
        case FIGHT_COUNT:
        default:
            choiceStr = "Error!";
            break;
    }
    return choiceStr;
}

void gameFightInteractionEnumPrint() {
    printf("Decide what to do:\n");
    for (int i = 0; i < FIGHT_COUNT; ++i) {
        if (i) putchar(' ');
        printf("%d) %s", i + 1, gameFightInteractionEnumGetString(i));
    }
    putchar('\n');
}

