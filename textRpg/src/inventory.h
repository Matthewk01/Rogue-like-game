#ifndef TEXTRPG_INVENTORY_H
#define TEXTRPG_INVENTORY_H

#define ITEM_NAME_LENGTH 20
#define INVENTORY_SLOTS 5

typedef enum ItemType {
    ITEM_TYPE_EMPTY,
    ITEM_TYPE_HP_POTION,
    ITEM_TYPE_WEAPON,
    ITEM_TYPE_SHIELD,
} ItemType;

typedef struct Item {
    ItemType type;
    char name[ITEM_NAME_LENGTH];
    int bonusDefense;
    int bonusDamage;
    int hpAmount;
    int quantity;
} Item;

typedef struct Inventory {
    Item items[INVENTORY_SLOTS];
} Inventory;

// Predefined items
const Item ITEM_EMPTY_ITEM;
const Item ITEM_HP_POTION;
const Item ITEM_WEAPON;
const Item ITEM_SHIELD;


Item *inventoryCreateItem(ItemType type);

void inventoryInit(Inventory *inv);

void inventoryPushBackItem(Inventory *inv, const Item *item);

void inventoryRemoveItem(Inventory *inv, int positionIdx);

void inventoryPrint(Inventory *inv);


#endif //TEXTRPG_INVENTORY_H
