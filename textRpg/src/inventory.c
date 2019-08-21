#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "inventory.h"
#include "character.h"

const Item ITEM_EMPTY_ITEM = {
        ITEM_TYPE_EMPTY,
        "Empty_slot",
        0,
        0,
        0,
        0
};

const Item ITEM_HP_POTION = {
        ITEM_TYPE_HP_POTION,
        "HP Potion",
        0,
        0,
        25,
        1
};

Item *inventoryCreateItem(ItemType type) {
    Item *itemTmp = (Item *) malloc(sizeof(*itemTmp));
    itemTmp->quantity = 1;
    switch (type) {
        case ITEM_TYPE_HP_POTION:
            itemTmp->hpAmount = 20;
            strcpy(itemTmp->name, "HP Potion");
            break;
        case ITEM_TYPE_SHIELD:
            itemTmp->bonusDefense = 15;
            strcpy(itemTmp->name, "Shield");
            break;
        case ITEM_TYPE_WEAPON:
            itemTmp->bonusDamage = 15;
            strcpy(itemTmp->name, "Weapon");
            break;
        case ITEM_TYPE_EMPTY:
        default:
            itemTmp->type = ITEM_TYPE_EMPTY;
            break;
    }
    return itemTmp;
}

void inventoryInit(Player *player) {
    for (int i = 0; i < INVENTORY_SLOTS; ++i) {
        player->inventory[i] = ITEM_EMPTY_ITEM;
    }
}

void inventoryPushBackItem(Player *player, const Item *item) {
    for (int i = 0; i < INVENTORY_SLOTS; ++i) {
        if (strcmp(player->inventory[i].name, item->name) == 0) {
            player->inventory[i].quantity++;
            return;
        }
    }

    for (int i = 0; i < INVENTORY_SLOTS; ++i) {
        if (player->inventory[i].type == ITEM_TYPE_EMPTY) {
            player->inventory[i] = *item;
        }
    }
}

void inventoryRemoveItem(Player *player, int positionIdx) {
    for (int i = 0; i < INVENTORY_SLOTS; ++i) {
        if (i == positionIdx) {
            player->inventory[i] = ITEM_EMPTY_ITEM;
        }
    }
}

void inventoryUseItem(Player *player, int positionIdx) {
    for (int i = 0; i < INVENTORY_SLOTS; ++i) {
        if (i == positionIdx) {
            Item *item = &player->inventory[i];
            switch (player->inventory[i].type) {
                case ITEM_TYPE_EMPTY:
                    break;
                case ITEM_TYPE_HP_POTION:
                    player->hp += item->hpAmount;
                    if (item->quantity <= 0) {
                        *item = ITEM_EMPTY_ITEM;
                    }
                    break;
                case ITEM_TYPE_WEAPON:
                    break;
                case ITEM_TYPE_SHIELD:
                    break;
            }
        }
    }
}

void inventoryPrint(Player *player) {
    printf("Inventory: ");
    for (int i = 0; i < INVENTORY_SLOTS; ++i) {
        const Item *item = &player->inventory[i];
        if (i) printf(" | ");
        if (item->type != ITEM_TYPE_EMPTY) {
            putchar(' ');
        } else {
            printf("%d) %s", i, item->name);
        }
    }
    putchar('\n');
}
