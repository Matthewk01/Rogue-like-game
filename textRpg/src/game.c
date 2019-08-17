#include "game.h"
#include "monster.h"

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

void startFight(Player *player, Monster *monster) {
    putchar('\n');
    printf("Fight initiated!\n");
    while (playerIsAlive(player) && monsterIsAlive(monster)) {
        // Print player overview
        putchar('\n');
        playerPrintOverview(player);
        monsterPrintOverview(monster);

        // Menu
        enemyInteractionChoice choice;
        choice = interactionMenu();

        // Handle choice
        switch (choice) {
            case ATTACK:
                playerAttack(player, monster);
                break;
            case RUN:
                printf("Player %s decides to run away!\n", player->name);
                return;
            default:
                printf("Error: Undefined choice.");
                break;
        }

        // Monster attack
        monsterAttack(monster, player);

        // Check whether someone died
        if(!monsterIsAlive(monster)){
            printf("'%s' wins the fight!\n", player->name);
            int exp = monster->level * 100;
            player->experiences += exp;
            printf("You've gained %d experiences!\n", exp);
            playerCheckLevelUp(player);
            return;
        } else if(!playerIsAlive(player)) {
            printf("Monster managed to defeat you!");
            return;
        }

        // Wait for 250ms
        Sleep(250);
    }
}

void gameLoop() {
    printf("Choose name:\n>> ");
    char name[20];
    scanf("%s", name);
    printf("Choose class: (KNIGHT, RANGER, ROGUE, MAGE)\n>> ");
    char class[20];
    scanf("%s", class);
    Player *hero = playerInit(name, playerParseClass(class));
    Monster *testMonster = monsterInit();
    while(gameIsRunning) {
        // load save file, otherwise create new Character
        // render playerOverview
        // render map
        // render choiceMenu
        startFight(hero, testMonster);

    }
}
