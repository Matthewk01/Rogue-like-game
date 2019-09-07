#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "inventory.h"

const Item ITEM_EMPTY_ITEM = {
        ITEM_TYPE_EMPTY,
        EQUIP_NULL,
        "Empty_slot",
        false,
        0,
        0,
        0,
        0,
        0
};

const Item ITEM_HP_POTION = {
        ITEM_TYPE_HP_POTION,
        EQUIP_NULL,
        "HP Potion",
        false,
        0,
        0,
        25,
        1,
        10
};

const Item ITEM_WEAPON_BRONZE = {
        ITEM_TYPE_WEAPON,
        EQUIP_WEAPON,
        "Bronze Sword",
        true,
        0,
        20,
        0,
        1,
        30
};

const Item ITEM_SHIELD_BRONZE = {
        ITEM_TYPE_SHIELD,
        EQUIP_SHIELD,
        "Bronze Shield",
        true,
        20,
        0,
        0,
        1,
        30
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

void inventoryInit(Inventory *inv) {
    for (int i = 0; i < INVENTORY_SLOTS; ++i) {
        inv->items[i] = ITEM_EMPTY_ITEM;
    }
}

void inventoryPushBackItem(Inventory *inv, const Item *item) {
    // Does he own him already?
    for (int i = 0; i < INVENTORY_SLOTS; ++i) {
        if (strcmp(inv->items[i].name, item->name) == 0) {
            inv->items[i].quantity++;
            return;
        }
    }

    // Find empty slot
    for (int i = 0; i < INVENTORY_SLOTS; ++i) {
        if (inv->items[i].type == ITEM_TYPE_EMPTY) {
            inv->items[i] = *item;
            return;
        }
    }
}

void inventoryRemoveItem(Inventory *inv, int positionIdx) {
    for (int i = 0; i < INVENTORY_SLOTS; ++i) {
        if (i == positionIdx) {
            inv->items[i] = ITEM_EMPTY_ITEM;
        }
    }
}

void inventoryPrint(Inventory *inv) {
    printf("Inventory: ");
    for (int i = 0; i < INVENTORY_SLOTS; ++i) {
        const Item *item = &inv->items[i];
        if (i) printf(" | ");
        if (item->type == ITEM_TYPE_EMPTY) {
            printf("%d) %s", i + 1, item->name);
        } else {
            printf("%d) %s (%dx)", i + 1, item->name, item->quantity);
        }
    }
    putchar('\n');
}

bool inventoryEquipItem(Equip *equip, Inventory *inventory, int positionIdx) {
    Item *itemToEquip = &inventory->items[positionIdx];
    if(itemToEquip->type == ITEM_TYPE_EMPTY || !itemToEquip->wearable)
        return false;
    if(equip->items[itemToEquip->idx].type == ITEM_TYPE_EMPTY){
        equip->items[itemToEquip->idx] = *itemToEquip;
        itemToEquip->quantity -= 1;
        if(itemToEquip->quantity <= 0) *itemToEquip = ITEM_EMPTY_ITEM;
    } else {
        Item itemTmp = equip->items[itemToEquip->idx];
        itemToEquip->quantity -= 1;
        equip->items[itemToEquip->idx] = *itemToEquip;
        inventoryPushBackItem(inventory, &itemTmp);
    }
    return true;
}

void inventoryEquipInit(Equip *equip) {
    for(size_t i = 0; i < EQUIP_COUNT; ++i) {
        equip->items[i] = ITEM_EMPTY_ITEM;
    }
}

void inventoryEquipPrint(Equip *equip) {
    printf("Equipment: ");
    const char *equipNames[] = {"Weapon", "Shield"};
    for (int i = 0; i < EQUIP_COUNT; ++i) {
        const Item *item = &equip->items[i];
        if (i) printf(" | ");
        if(item->type == ITEM_TYPE_WEAPON) {
            printf("%s) %s (+%d to dmg)", equipNames[i], item->name, item->bonusDamage);
        } else {
            printf("%s) %s (+%d to def)", equipNames[i], item->name, item->bonusDefense);
        }

    }
    putchar('\n');
}

bool inventoryHasEmptySlot(Inventory *inv) {
    for (int i = 0; i < INVENTORY_SLOTS; ++i) {
        if (inv->items[i].type == ITEM_TYPE_EMPTY) {
            return true;
        }
    }
    return false;
}
