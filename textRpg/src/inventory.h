#ifndef TEXTRPG_INVENTORY_H
#define TEXTRPG_INVENTORY_H

#include <stdbool.h>

#define ITEM_NAME_LENGTH 20
#define INVENTORY_SLOTS 5

typedef enum ItemType {
    ITEM_TYPE_EMPTY,
    ITEM_TYPE_HP_POTION,
    ITEM_TYPE_WEAPON,
    ITEM_TYPE_SHIELD,
} ItemType;

typedef enum EquipType {
    EQUIP_WEAPON,
    EQUIP_SHIELD,
    EQUIP_COUNT,
    EQUIP_NULL
} EquipType;



typedef struct Item {
    ItemType type;
    EquipType idx;
    char name[ITEM_NAME_LENGTH];
    bool wearable;
    int bonusDefense;
    int bonusDamage;
    int hpAmount;
    int quantity;
    int price;
} Item;

typedef struct Inventory {
    Item items[INVENTORY_SLOTS];
} Inventory;

typedef struct Equip {
    Item items[EQUIP_COUNT];
} Equip;

bool inventoryEquipItem(Equip *equip, Inventory *inventory, int positionIdx);
void inventoryEquipInit(Equip *equip);
void inventoryEquipPrint(Equip *equip);

// Predefined items
const Item ITEM_EMPTY_ITEM;
const Item ITEM_HP_POTION;
const Item ITEM_WEAPON_BRONZE;
const Item ITEM_SHIELD_BRONZE;


Item *inventoryCreateItem(ItemType type);

void inventoryInit(Inventory *inv);

void inventoryPushBackItem(Inventory *inv, const Item *item);

void inventoryRemoveItem(Inventory *inv, int positionIdx);

void inventoryPrint(Inventory *inv);

bool inventoryHasEmptySlot(Inventory *inv);


#endif //TEXTRPG_INVENTORY_H
