#ifndef TEXTRPG_INVENTORY_H
#define TEXTRPG_INVENTORY_H

#define ITEM_NAME_LENGTH 20

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

const Item ITEM_EMPTY_ITEM;

const Item ITEM_HP_POTION;

typedef struct Character Character;

Item *inventoryCreateItem(ItemType type);

void inventoryInit(Character *player);

void inventoryPushBackItem(Character *player, const Item *item);

void inventoryRemoveItem(Character *player, int positionIdx);

void inventoryUseItem(Character *player, int positionIdx);

void inventoryPrint(Character *player);


#endif //TEXTRPG_INVENTORY_H
