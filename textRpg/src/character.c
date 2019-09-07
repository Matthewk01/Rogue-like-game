#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "character.h"
#include "monster.h"
#include "logger.h"

Character *characterInit(const char *name, CharacterClass role) {
    static int playerCount = 0;
    Character *tmpPlayer = (Character *) malloc(sizeof(Character));
    playerCount += 1;

    if (playerCount > 1) {
        tmpPlayer->isAI = true;
    } else {
        tmpPlayer->isAI = false;
    }

    // Init inventory and Equip
    inventoryInit(&tmpPlayer->inventory);
    inventoryEquipInit(&tmpPlayer->equip);

    // Init attributes
    tmpPlayer->name = strdup(name);
    tmpPlayer->level = 1;
    tmpPlayer->experiences = 0;
    tmpPlayer->positionX = 0;
    tmpPlayer->currency = 100;

    // Role specific attributes
    switch (role) {
        case CLASS_KNIGHT:
            tmpPlayer->charClass = CLASS_KNIGHT;
            tmpPlayer->hp = 100;
            tmpPlayer->HP_MAX = 100;
            tmpPlayer->damage = 15;
            tmpPlayer->defense = 9;
            break;
        case CLASS_RANGER:
            tmpPlayer->charClass = CLASS_RANGER;
            tmpPlayer->hp = 80;
            tmpPlayer->HP_MAX = 80;
            tmpPlayer->damage = 14;
            tmpPlayer->defense = 6;
            break;
        case CLASS_ROGUE:
            tmpPlayer->charClass = CLASS_ROGUE;
            tmpPlayer->hp = 90;
            tmpPlayer->HP_MAX = 90;
            tmpPlayer->damage = 13;
            tmpPlayer->defense = 5;
            break;
        case CLASS_MAGE:
            tmpPlayer->charClass = CLASS_MAGE;
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

void characterFree(Character *player) {
    free(player->name);
    free(player);
}

bool characterIsAlive(Character *player) {
    return player->hp > 0;
}

void characterCheckLevelUp(Character *player) {
    if (player->experiences > 99) {
        player->experiences = 0;
        player->level += 1;
        snprintf(buffer, sizeof(buffer), "Player '%s' leveled  up! (%d)\n", player->name, player->level);
        loggerPrint(buffer);
    }
}

void characterGraphicPrintHP(Character *player) {
    int barCount = ceil((1.0 * player->hp / player->HP_MAX) * MAX_BAR_COUNT);
    printf("HP_BAR: <");
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

void characterPrintOverview(Character *playerPtr) {
    for (int i = 0; i < BORDER_STAR_COUNT; ++i) putchar('*');
    putchar('\n');
    printf("<%s> %s: HP:%d/%d, damage: %d, defense: %d, level: %d, experiences: %d, currency: %dg.\n",
           characterClassEnumGetString(playerPtr->charClass),
           playerPtr->name,
           playerPtr->hp,
           playerPtr->HP_MAX,
           playerPtr->damage,
           playerPtr->defense,
           playerPtr->level,
           playerPtr->experiences,
           playerPtr->currency);
    characterGraphicPrintHP(playerPtr);
    characterGraphicPrintExpBar(playerPtr);
    inventoryPrint(&playerPtr->inventory);
    inventoryEquipPrint(&playerPtr->equip);
    for (int i = 0; i < BORDER_STAR_COUNT; ++i) putchar('*');
    putchar('\n');
}

void characterMoveTo(Character *player, int xPosition) {
    player->positionX = xPosition;
}

void characterAttackMonster(Character *from, Monster *to) {
    int damage = from->damage - to->defense;
    if (!monsterIsAlive(to)) {
        loggerPrint("The target is already dead!\n");
    } else {
        if (damage <= 0) {
            snprintf(buffer, sizeof(buffer), "Monster managed to block the player's %s attack!\n", from->name);
            loggerPrint(buffer);
        } else {
            to->hp -= (damage);
            if (to->hp < 0) to->hp = 0;
            snprintf(buffer, sizeof(buffer), "Player '%s' dealed '%d' damage. Enemy's hp: %d\n", from->name, damage,
                     to->hp);
            loggerPrint(buffer);
        }
    }
}

void characterClassEnumPrint() {
    loggerPrint("Choose class:\n");
    for (int i = 0; i < CLASS_COUNT; ++i) {
        if (i) putchar(' ');
        printf("%d) %s", i + 1, characterClassEnumGetString(i));
    }
    putchar('\n');
}

const char *characterClassEnumGetString(CharacterClass choice) {
    const char *choiceStr;
    switch (choice) {
        case CLASS_KNIGHT:
            choiceStr = "Knight";
            break;
        case CLASS_RANGER:
            choiceStr = "Ranger";
            break;
        case CLASS_ROGUE:
            choiceStr = "Rogue";
            break;
        case CLASS_MAGE:
            choiceStr = "Mage";
            break;
        default:
            choiceStr = "Error!";
            break;
    }
    return choiceStr;
}

void characterGraphicPrintExpBar(Character *player) {
    int barCount = ceil((1.0 * player->experiences / EXP_MAX) * MAX_BAR_COUNT);
    printf("LEVEL_BAR: <");
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

void characterUseItem(Character *player, int positionIdx) {
    for (int i = 0; i < INVENTORY_SLOTS; ++i) {
        if (i == positionIdx) {
            Item *item = &player->inventory.items[i];
            switch (player->inventory.items[i].type) {
                case ITEM_TYPE_HP_POTION:
                    player->hp += item->hpAmount;
                    if (player->hp > player->HP_MAX) player->hp = player->HP_MAX;
                    --item->quantity;
                    if (item->quantity <= 0) {
                        *item = ITEM_EMPTY_ITEM;
                    }
                    break;
                case ITEM_TYPE_WEAPON:
                    if (player->equip.items[item->idx].type == ITEM_TYPE_WEAPON) {
                        player->damage -= player->equip.items[item->idx].bonusDamage;
                    }
                    if (inventoryEquipItem(&player->equip, &player->inventory, positionIdx)) {
                        player->damage += item->bonusDamage;
                    }
                    break;
                case ITEM_TYPE_SHIELD:
                    if (player->equip.items[item->idx].type == ITEM_TYPE_SHIELD) {
                        player->defense -= player->equip.items[item->idx].bonusDefense;
                    }
                    if (inventoryEquipItem(&player->equip, &player->inventory, positionIdx)) {
                        player->defense += item->bonusDefense;
                    }
                    break;
                case ITEM_TYPE_EMPTY:
                default:
                    loggerPrint("Nothing happened!\n");
                    break;
            }
            return;
        }
    }
}

bool characterBuyItem(Character *player, const Item *item) {
    if (player->currency < item->price)
        return false;
    if (!inventoryHasEmptySlot(&player->inventory))
        return false;
    player->currency -= item->price;
    inventoryPushBackItem(&player->inventory, item);
    return true;
}




