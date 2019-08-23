#include "game.h"

int main(int argc, char *argv[]) {
//    Character *player1 = playerInit("Bob", KNIGHT);
//    Character *player2 = playerInit("Saruman", RANGER);
//
//    while (1) {
//        Sleep(500);
//        startFight(player1, player2);
//        if (!playerIsAlive(player2)) {
//            playerFree(player2);
//            player2 = playerInit("Saruman2", RANGER);
//        }
//        if (!playerIsAlive(player1)) {
//            break;
//        }
//    }
//    playerFree(player1);
    GameState game;
    gameStart(&game);
    return 0;
}
