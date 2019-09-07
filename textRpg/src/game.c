#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "logger.h"

void gameInteractionEnumPrint() {
    loggerPrint("Decide what to do:\n");
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
            choiceStr = "Go to the dungeon!";
            break;
        case BUY_ITEMS:
            choiceStr = "Buy items!";
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
    loggerPrint("Fight initiated!\n");
    while (characterIsAlive(player) && monsterIsAlive(monster)) {
        // Print player overview
        putchar('\n');
        characterPrintOverview(player);
        loggerPrint("VS\n");
        monsterPrintOverview(monster);

        // Print choices
        gameFightInteractionEnumPrint();

        // Handle choice
        switch ((FightInteractionChoice) gameGetInputIdx("", 1, FIGHT_COUNT)) {
            case FIGHT_ATTACK:
                characterAttackMonster(player, monster);
                break;
            case FIGHT_RUN:
                snprintf(buffer, sizeof(buffer), "Player %s decides to run away!\n", player->name);
                loggerPrint(buffer);
                return;
            default:
                printf("Error: Undefined choice.\n");
                break;
        }

        // Monster attack
        monsterAttackPlayer(monster, player);

        // Check whether someone died
        if (!monsterIsAlive(monster)) {
            snprintf(buffer, sizeof(buffer), "'%s' wins the fight!\n", player->name);
            loggerPrint(buffer);
            int exp = monster->level * 60;
            player->experiences += exp;
            snprintf(buffer, sizeof(buffer), "You've gained %d experiences!\n", exp);
            loggerPrint(buffer);
            characterCheckLevelUp(player);
            return;
        } else if (!characterIsAlive(player)) {
            loggerPrint("Monster managed to defeat you!\n");
            return;
        }

        // Wait
        Sleep(250);
    }
}

void gameInteractionMenu(GameState *game) {
    gameInteractionEnumPrint();
    switch (gameGetInputIdx("", 1, GAME_INTERACTION_CHOICE_COUNT)) {
        case MOVE_LEFT:
            if (mapPlayerMove(game->map.player, -1)) {
                loggerPrint("You've moved to the left!\n");
            } else {
                loggerPrint("You can't go this way!\n");
            }
            break;
        case MOVE_RIGHT:
            if (mapPlayerMove(game->map.player, 1)) {
                loggerPrint("You've moved to the right!\n");
            } else {
                loggerPrint("You can't go this way!\n");
            }
            break;
        case USE_ITEM:
            loggerPrint("Which one?\n");
            characterUseItem(game->map.player, gameGetInputIdx("", 1, 5));
            break;
        case GO_TO_ROOM:
            loggerPrint("You've gone to the room!\n");
            gameStartFightBetween(game->map.player, &game->map.rooms[game->map.player->positionX].monster);
            break;
        case BUY_ITEMS:
            // NPC menu
            gameBuyMenu(game);
            break;
        case SAVE_LEAVE:
            game->gameIsRunning = false;
            break;
        default:
            loggerPrint("Wrong input!\n");
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
        // Wait
        Sleep(250);
    }
    characterFree(game->map.player);

}
// ******************************************************************************************************

void gameStart(GameState *game) {
    // load save file, otherwise create new Character
    game->gameIsRunning = true;
    game->map.player = gameCreateCharacter();
    mapRoomsInit(&game->map);

    // Test items
    inventoryPushBackItem(&game->map.player->inventory, &ITEM_HP_POTION);
    inventoryPushBackItem(&game->map.player->inventory, &ITEM_HP_POTION);
    inventoryPushBackItem(&game->map.player->inventory, &ITEM_HP_POTION);
    inventoryPushBackItem(&game->map.player->inventory, &ITEM_HP_POTION);
    inventoryPushBackItem(&game->map.player->inventory, &ITEM_SHIELD_BRONZE);
    inventoryPushBackItem(&game->map.player->inventory, &ITEM_WEAPON_BRONZE);
    inventoryPushBackItem(&game->map.player->inventory, &ITEM_SHIELD_BRONZE);
    inventoryPushBackItem(&game->map.player->inventory, &ITEM_WEAPON_BRONZE);

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
            loggerPrint("Wrong input!");
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
    loggerPrint("Decide what to do:\n");
    for (int i = 0; i < FIGHT_COUNT; ++i) {
        if (i) putchar(' ');
        printf("%d) %s", i + 1, gameFightInteractionEnumGetString(i));
    }
    putchar('\n');
}

void gameBuyMenu(GameState *game) {
    loggerPrint("What item would you like to buy ?\n");
    loggerPrint("1) Bronze Sword (30g) 2) Bronze Shield (30g) 3) Health Potion (10g)\n");
    const Item *itemToBuy;
    switch (gameGetInputIdx("", 1, 3)) {
        case 0:
            itemToBuy = &ITEM_WEAPON_BRONZE;
            break;
        case 1:
            itemToBuy = &ITEM_SHIELD_BRONZE;
            break;
        case 2:
            itemToBuy = &ITEM_HP_POTION;
            break;
        default:
            itemToBuy = NULL;
            break;
    }
    characterBuyItem(game->map.player, itemToBuy);
}



