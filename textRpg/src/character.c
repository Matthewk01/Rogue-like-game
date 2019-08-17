#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "character.h"

const char *printPlayerType(CharacterClass type) {
    const char *typeStr;
    switch (type) {
        case KNIGHT:
            typeStr = "Knight";
            break;
        case RANGER:
            typeStr = "Ranger";
            break;
        case ROGUE:
            typeStr = "Rogue";
            break;
        case MAGE:
            typeStr = "Mage";
            break;
        default:
            typeStr = "?";
    }
    return typeStr;
}

Character *initPlayer(const char *name, CharacterClass role) {
    static int playerCount = 0;
    Character *tmpPlayer = (Character *) malloc(sizeof(Character));
    playerCount += 1;

    if (playerCount > 1) {
        tmpPlayer->isAI = true;
    } else {
        tmpPlayer->isAI = false;
    }

    tmpPlayer->name = strdup(name);
    tmpPlayer->level = 1;
    tmpPlayer->experiences = 0;
    switch (role) {
        case KNIGHT:
            tmpPlayer->role = KNIGHT;
            tmpPlayer->hp = 100;
            tmpPlayer->HP_MAX = 100;
            tmpPlayer->damage = 25;
            tmpPlayer->defense = 25;
            break;
        case RANGER:
            tmpPlayer->role = RANGER;
            tmpPlayer->hp = 80;
            tmpPlayer->HP_MAX = 80;
            tmpPlayer->damage = 40;
            tmpPlayer->defense = 12;
            break;
        case ROGUE:
            tmpPlayer->role = ROGUE;
            tmpPlayer->hp = 90;
            tmpPlayer->HP_MAX = 90;
            tmpPlayer->damage = 40;
            tmpPlayer->defense = 10;
            break;
        case MAGE:
            tmpPlayer->role = MAGE;
            tmpPlayer->hp = 50;
            tmpPlayer->HP_MAX = 50;
            tmpPlayer->damage = 50;
            tmpPlayer->defense = 5;
            break;
        default:
            free(tmpPlayer);
            return NULL;
    }
    return tmpPlayer;
}

void freePlayer(Character *player) {
    free(player->name);
    free(player);
}

bool isAlive(Character *player) {
    return player->hp > 0;
}

void attackPlayer(Character *from, Character *to) {
    int damage = from->damage - to->defense;
    if (!isAlive(to)) {
        printf("The target is already dead!\n");
    } else {
        if (damage <= 0) {
            printf("Player %s managed to block the player's %s attack!", to->name, from->name);
        } else {
            to->hp -= (damage);
            if (to->hp < 0) to->hp = 0;
            printf("Player '%s' dealed '%d' damage to player '%s'. Player's '%s' hp: %d\n", from->name, damage,
                   to->name, to->name, to->hp);
        }
    }
}

void checkLevelUp(Character *player) {
    if (player->experiences > 99) {
        player->experiences = 0;
        player->level += 1;
        printf("Player '%s' leveled  up! (%d)\n", player->name, player->level);
    }
}

void showGraphicHP(Character *player) {
    int barCount = ceil((1.0 * player->hp / player->HP_MAX) * MAX_BAR_COUNT);
    printf("HP_BAR(%d/%d): <", barCount, MAX_BAR_COUNT);
    int i;
    for (i = 0; i < barCount; ++i) {
        putchar('#');
    }
    for (; i < MAX_BAR_COUNT; ++i) {
        putchar('-');
    }
    putchar('>');
    putchar('\n');
}

void printPlayer(Character *playerPtr) {
    printf("<%s> %s: damage: %d, defense: %d, level: %d, experiences: %d.\n",
           printPlayerType(playerPtr->role), playerPtr->name, playerPtr->damage, playerPtr->defense, playerPtr->level,
           playerPtr->experiences);
    showGraphicHP(playerPtr);
}
