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

typedef struct Player Player;

Item* inventoryCreateItem(ItemType type);

void inventoryInit(Player *player);

void inventoryPushBackItem(Player *player, const Item *item);

void inventoryRemoveItem(Player *player, int positionIdx);

void inventoryUseItem(Player *player, int positionIdx);

void inventoryPrint(Player *player);



#endif //TEXTRPG_INVENTORY_H
