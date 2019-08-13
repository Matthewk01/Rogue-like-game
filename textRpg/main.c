#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <windows.h>

#define MAX_BAR_COUNT 20

enum PlayerType {
  KNIGHT,
  RANGER,
  ROGUE,
  MAGE
};

typedef struct {
  PlayerType role;
  char *name;
  int hp;
  int HP_MAX;
  int damage;
  int defense;
  bool isAI;
  int level;
  int experiences;
  //Inventory
} Player;

const char* printPlayerType(PlayerType type) {
  const char *typeStr;
  switch(type){
    case KNIGHT: typeStr = "Knight";
                 break;
    case RANGER: typeStr = "Ranger";
                 break;
    case ROGUE:  typeStr = "Rogue";
                 break;
    case MAGE:   typeStr = "Mage";
                 break;
    default: typeStr = "?";
  }
  return typeStr;
}

Player* initPlayer(const char *name, PlayerType role){
  static int playerCount = 0;
  Player *tmpPlayer = (Player*) malloc(sizeof(Player));
  playerCount += 1;

  if(playerCount > 1){
    tmpPlayer->isAI = true;
  } else {
    tmpPlayer->isAI = false;
  }

  tmpPlayer->name = strdup(name);
  tmpPlayer->level = 1;
  tmpPlayer->experiences = 0;
  switch(role) {
    case KNIGHT: tmpPlayer->role = KNIGHT;
                 tmpPlayer->hp = 100;
                 tmpPlayer->HP_MAX = 100;
                 tmpPlayer->damage = 25;
                 tmpPlayer->defense = 25;
                 break;
    case RANGER: tmpPlayer->role = RANGER;
                 tmpPlayer->hp = 80;
                 tmpPlayer->HP_MAX = 80;
                 tmpPlayer->damage = 40;
                 tmpPlayer->defense = 12;
                 break;
    case ROGUE: tmpPlayer->role = ROGUE;
                 tmpPlayer->hp = 90;
                 tmpPlayer->HP_MAX = 90;
                 tmpPlayer->damage = 40;
                 tmpPlayer->defense = 10;
                 break;
    case MAGE: tmpPlayer->role = MAGE;
                 tmpPlayer->hp = 50;
                 tmpPlayer->HP_MAX = 50;
                 tmpPlayer->damage = 50;
                 tmpPlayer->defense = 5;
                 break;
    default: free(tmpPlayer); return NULL;
  }
  return tmpPlayer;
}

void freePlayer(Player *player) {
  free(player->name);
  free(player);
}

bool isAlive(Player *player){
  return player->hp > 0;
}

void attackPlayer(Player *from, Player *to){
  int damage = from->damage - to->defense;
  if(!isAlive(to)){
    printf("The target is already dead!\n");
  } else {
    if(damage <= 0){
      printf("Player %s managed to block the player's %s attack!", to->name, from->name);
    } else {
      to->hp -= (damage);
      if(to->hp < 0) to->hp = 0;
      printf("Player '%s' dealed '%d' damage to player '%s'. Player's '%s' hp: %d\n", from->name, damage, to->name, to->name, to->hp);
    }
  }
}

enum enemyInteractionChoice {
  ATTACK,
  RUN,
};

enemyInteractionChoice interactionMenu() {
  int input;
  do{
    printf("1) Attack enemy 2) Run away!\n");
    printf(">> ");
    if(scanf(" %d", &input) != 1){
      while(getchar() != '\n'){}
    }
  } while(input != 1 && input != 2);
  return (input == 1 ? ATTACK : RUN);
}

void checkLevelUp(Player *player) {
  if(player->experiences > 99) {
    player->experiences = 0;
    player->level += 1;
    printf("Player '%s' leveled  up! (%d)\n", player->name, player->level);
  }
}

void showGraphicHP(Player *player) {
  int barCount = ceil((1.0 * player->hp/player->HP_MAX) * MAX_BAR_COUNT);
  printf("HP_BAR(%d/%d): <", barCount, MAX_BAR_COUNT);
  int i;
  for(i = 0; i < barCount; ++i) {
    putchar('#');
  }
  for(; i < MAX_BAR_COUNT; ++i){
    putchar(' ');
  }
  putchar('>');
  putchar('\n');
}

void printPlayer(Player *playerPtr) {
  printf("<%s> %s: damage: %d, defense: %d, level: %d, experiences: %d.\n",
         printPlayerType(playerPtr->role), playerPtr->name, playerPtr->damage, playerPtr->defense, playerPtr->level, playerPtr->experiences);
  showGraphicHP(playerPtr);
}

void startFight(Player *player1, Player *player2){
  Player *from = player1, *to = player2, *tmp;
  putchar('\n');
  printf("Fight initiated between '%s' and '%s'\n", from->name, to->name);
  while(isAlive(from) && isAlive(to)) {
    // Print player overview
    putchar('\n');
    printPlayer(player1);
    printPlayer(player2);

    // Menu
    enemyInteractionChoice choice;
    if(!from->isAI){
      choice = interactionMenu();
    } else {
      printf("Enemy attacks!\n");
      choice = ATTACK;
    }
    // Handle choice
    switch(choice) {
      case ATTACK: attackPlayer(from, to);
                   break;
      case RUN: printf("Player %s decides to run away!\n", from->name);
                return;
                break;
      default: printf("Error: Undefined choice.");
               break;
    }
    // Swap players
    if(isAlive(to)){
      tmp = from;
      from = to;
      to = tmp;
    } else {
      printf("'%s' wins the fight!\n", from->name);
      if(!from->isAI) {
        int exp = to->level * 100;
        from->experiences += exp;
        printf("You've gained %d experiences!\n", exp);
        checkLevelUp(from);
      }
    }

    // Wait for 250ms
    Sleep(250);
  }
  // Check for level and experiences

}

int main(){
  Player *player1 = initPlayer("Bob", KNIGHT);
  Player *player2 = initPlayer("Saruman", RANGER);
  // printPlayer(player1);
  // printPlayer(player2);

  while(1){
    Sleep(500);
    startFight(player1, player2);
    if(!isAlive(player2)){
      freePlayer(player2);
      player2 = initPlayer("Saruman2", RANGER);
    }
    if(!isAlive(player1)){
      break;
    }
  }
  freePlayer(player1);
  return 0;
}
