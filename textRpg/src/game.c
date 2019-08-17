#include "game.h"

enemyInteractionChoice interactionMenu() {
    int input;
    do {
        printf("1) Attack enemy 2) Run away!\n");
        printf(">> ");
        if (scanf(" %d", &input) != 1) {
            while (getchar() != '\n') {}
        }
    } while (input != 1 && input != 2);
    return (input == 1 ? ATTACK : RUN);
}

void startFight(Character *player1, Character *player2) {
    Character *from = player1, *to = player2, *tmp;
    putchar('\n');
    printf("Fight initiated between '%s' and '%s'\n", from->name, to->name);
    while (isAlive(from) && isAlive(to)) {
        // Print player overview
        putchar('\n');
        printPlayer(player1);
        printPlayer(player2);

        // Menu
        enemyInteractionChoice choice;
        if (!from->isAI) {
            choice = interactionMenu();
        } else {
            printf("Enemy attacks!\n");
            choice = ATTACK;
        }
        // Handle choice
        switch (choice) {
            case ATTACK:
                attackPlayer(from, to);
                break;
            case RUN:
                printf("Player %s decides to run away!\n", from->name);
                return;
            default:
                printf("Error: Undefined choice.");
                break;
        }
        // Swap players
        if (isAlive(to)) {
            tmp = from;
            from = to;
            to = tmp;
        } else {
            printf("'%s' wins the fight!\n", from->name);
            if (!from->isAI) {
                int exp = to->level * 100;
                from->experiences += exp;
                printf("You've gained %d experiences!\n", exp);
                checkLevelUp(from);
            }
        }

        // Wait for 250ms
        Sleep(250);
    }
}