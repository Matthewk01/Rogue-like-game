#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "monster.h"
#include "character.h"

Monster *monsterInit() {
    Monster *monster = (Monster *) malloc(sizeof(*monster));

    monster->damage = 3;
    monster->hp = 150;
    monster->HP_MAX = 150;
    monster->defense = 10;
    monster->level = 5;

    return monster;
}

void monsterGraphicPrintHP(Monster *monster) {
    int barCount = ceil((1.0 * monster->hp / monster->HP_MAX) * MAX_BAR_COUNT);
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

void monsterPrintOverview(Monster *monster) {
    for (int i = 0; i < BORDER_STAR_COUNT; ++i) putchar('*');
    putchar('\n');
    printf("Monster: damage: %d, defense: %d, level: %d.\n",
           monster->damage, monster->defense, monster->level);
    monsterGraphicPrintHP(monster);
    for (int i = 0; i < BORDER_STAR_COUNT; ++i) putchar('*');
    putchar('\n');
}

bool monsterIsAlive(Monster *monster) {
    return monster->hp > 0;
}

void monsterAttackPlayer(Monster *from, Character *to) {
    int damage = from->damage - to->defense;
    if (!characterIsAlive(to)) {
        printf("The target is already dead!\n");
    } else {
        if (damage <= 0) {
            printf("Player managed to block the monster's attack!\n");
        } else {
            to->hp -= (damage);
            if (to->hp < 0) to->hp = 0;
            printf("Monster dealed '%d' damage. Enemy's hp: %d\n", damage,
                   to->hp);
        }
    }
}

