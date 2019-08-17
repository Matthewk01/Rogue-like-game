#include "game.h"

FightInteractionChoice gameFightInteractionMenu() {
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

void gamePlayerAttack(Player *from, Monster *to) {
    int damage = from->damage - to->defense;
    if (!monsterIsAlive(to)) {
        printf("The target is already dead!\n");
    } else {
        if (damage <= 0) {
            printf("Monster managed to block the player's %s attack!\n", from->name);
        } else {
            to->hp -= (damage);
            if (to->hp < 0) to->hp = 0;
            printf("Player '%s' dealed '%d' damage. Enemy's hp: %d\n", from->name, damage,
                   to->hp);
        }
    }
}

void gameMonsterAttack(Monster *from, Player *to) {
    int damage = from->damage - to->defense;
    if (!playerIsAlive(to)) {
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

void gameStartFightBetween(Player *player, Monster *monster) {
    putchar('\n');
    printf("Fight initiated!\n");
    while (playerIsAlive(player) && monsterIsAlive(monster)) {
        // Print player overview
        putchar('\n');
        playerPrintOverview(player);
        monsterPrintOverview(monster);

        // Menu
        FightInteractionChoice choice;
        choice = gameFightInteractionMenu();

        // Handle choice
        switch (choice) {
            case ATTACK:
                gamePlayerAttack(player, monster);
                break;
            case RUN:
                printf("Player %s decides to run away!\n", player->name);
                return;
            default:
                printf("Error: Undefined choice.\n");
                break;
        }

        // Monster attack
        gameMonsterAttack(monster, player);

        // Check whether someone died
        if (!monsterIsAlive(monster)) {
            printf("'%s' wins the fight!\n", player->name);
            int exp = monster->level * 100;
            player->experiences += exp;
            printf("You've gained %d experiences!\n", exp);
            playerCheckLevelUp(player);
            return;
        } else if (!playerIsAlive(player)) {
            printf("Monster managed to defeat you!\n");
            return;
        }

        // Wait for 250ms
        Sleep(250);
    }
}

Player *gameCreateCharacter() {
    const int MAX_LENGTH = 20;
    printf("Choose name:\n");
    char name[MAX_LENGTH];
    bool leaveRequested;

    do {
        printf(">> ");
        if (scanf("%s", name) != 1) {
            printf("Wrong input!");
            leaveRequested = false;
            while (getchar() != '\n') {}
        } else {
            leaveRequested = true;
        }
        putchar('\n');
    } while (!leaveRequested);

    printf("Choose class: (KNIGHT, RANGER, ROGUE, MAGE)\n");
    char class[MAX_LENGTH];
    do {
        printf(">> ");
        if (scanf("%s", class) != 1 || playerParseClass(class) == ERR) {
            printf("Wrong input!");
            leaveRequested = false;
            while (getchar() != '\n') {}
        } else {
            leaveRequested = true;
        }
        putchar('\n');
    } while (!leaveRequested);
    return playerInit(name, playerParseClass(class));
}

void gameMapInteractionMenu() {
    const int choiceCount = 4;
    printf("Decide what to do: 1) Move left! 2) Move right! 3) Go to the room! 4) Save and leave!\n");
    int input;
    bool isCorr;
    do {
        printf(">> ");
        if(scanf("%d", &input) != 1 || input < 1 || input > choiceCount) {
            isCorr = false;
            while(getchar() != '\n');
        } else {
            isCorr = true;
        }
    } while(!isCorr);
    switch (input) {
        case 1:
            if (mapPlayerMove(map.player, -1)) {
                printf("You've moved to the left!\n");
            } else {
                printf("You can't go this way!\n");
            }
            break;
        case 2:
            if (mapPlayerMove(map.player, 1)) {
                printf("You've moved to the right!\n");
            } else {
                printf("You can't go this way!\n");
            }
            break;
        case 3:
            printf("You've gone to the room!\n");
            gameStartFightBetween(map.player, &map.rooms[map.player->positionX].monster);
            break;
        case 4:
            gameIsRunning = false;
            break;
        default:
            printf("Wrong input!\n");
            break;
    }
}

// ******************************************************************************************************
void gameLoop() {
    gameIsRunning = true;
    // load save file, otherwise create new Character
    map.player = gameCreateCharacter();
    mapRoomsInit(&map);

    while (gameIsRunning) {
        // render playerOverview
        playerPrintOverview(map.player);
        // render map
        mapPrint(&map);
        // render choiceMenu
        gameMapInteractionMenu();
        // startFight(map.player, testMonster);

    }
    playerFree(map.player);

}
// ******************************************************************************************************


