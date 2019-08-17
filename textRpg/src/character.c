#include "character.h"

const char *playerPrintType(PlayerClass type) {
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

Player *playerInit(const char *name, PlayerClass role) {
    static int playerCount = 0;
    Player *tmpPlayer = (Player *) malloc(sizeof(Player));
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
            tmpPlayer->charClass = KNIGHT;
            tmpPlayer->hp = 100;
            tmpPlayer->HP_MAX = 100;
            tmpPlayer->damage = 6;
            tmpPlayer->defense = 12;
            break;
        case RANGER:
            tmpPlayer->charClass = RANGER;
            tmpPlayer->hp = 80;
            tmpPlayer->HP_MAX = 80;
            tmpPlayer->damage = 9;
            tmpPlayer->defense = 6;
            break;
        case ROGUE:
            tmpPlayer->charClass = ROGUE;
            tmpPlayer->hp = 90;
            tmpPlayer->HP_MAX = 90;
            tmpPlayer->damage = 14;
            tmpPlayer->defense = 5;
            break;
        case MAGE:
            tmpPlayer->charClass = MAGE;
            tmpPlayer->hp = 50;
            tmpPlayer->HP_MAX = 50;
            tmpPlayer->damage = 18;
            tmpPlayer->defense = 3;
            break;
        default:
            free(tmpPlayer);
            return NULL;
    }
    return tmpPlayer;
}

void playerFree(Player *player) {
    free(player->name);
    free(player);
}

bool playerIsAlive(Player *player) {
    return player->hp > 0;
}

void playerCheckLevelUp(Player *player) {
    if (player->experiences > 99) {
        player->experiences = 0;
        player->level += 1;
        printf("Player '%s' leveled  up! (%d)\n", player->name, player->level);
    }
}

void playerGraphicPrintHP(Player *player) {
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

void playerPrintOverview(Player *playerPtr) {
    printf("<%s> %s: damage: %d, defense: %d, level: %d, experiences: %d.\n",
           playerPrintType(playerPtr->charClass), playerPtr->name, playerPtr->damage, playerPtr->defense, playerPtr->level,
           playerPtr->experiences);
    playerGraphicPrintHP(playerPtr);
}

void playerAttack(Player *from, Monster *to) {
    int damage = from->damage - to->defense;
    if (!monsterIsAlive(to)) {
        printf("The target is already dead!\n");
    } else {
        if (damage <= 0) {
            printf("Monster managed to block the player's %s attack!", from->name);
        } else {
            to->hp -= (damage);
            if (to->hp < 0) to->hp = 0;
            printf("Player '%s' dealed '%d' damage. Enemy's hp: %d\n", from->name, damage,
                   to->hp);
        }
    }
}

PlayerClass playerParseClass(const char *cls) {
    PlayerClass playClass;
    if(strncmp("KNIGHT", cls, 20) == 0)
        playClass = KNIGHT;
    else if(strncmp("RANGER", cls, 20) == 0)
        playClass = RANGER;
    else if(strncmp("ROGUE", cls, 20) == 0)
        playClass = ROGUE;
    else if(strncmp("MAGE", cls, 20) == 0)
        playClass = MAGE;
    else
        playClass = KNIGHT;
    return playClass;
}


