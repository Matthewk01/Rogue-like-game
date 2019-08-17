#include "game.h"

int main(int argc, char *argv[]) {
    Character *player1 = initPlayer("Bob", KNIGHT);
    Character *player2 = initPlayer("Saruman", RANGER);

    while (1) {
        Sleep(500);
        startFight(player1, player2);
        if (!isAlive(player2)) {
            freePlayer(player2);
            player2 = initPlayer("Saruman2", RANGER);
        }
        if (!isAlive(player1)) {
            break;
        }
    }
    freePlayer(player1);
    return 0;
}
