#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

void assert(int equal) {
  if(equal) {
    printf("TEST PASSED\n\n");
  }
  else {
    printf("TEST FAILED\n\n");
  }
}

int main() {
  struct gameState G, testG;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
  int testResult;
  initializeGame(numPlayers, k, seed, &G);

  printf("TESTING isGameOver\n");
  printf("-----------------------------------------\n");

  // ----------- TEST 1 -----------------------------------------------
  printf("TEST 1: Game is over because province pile is empty\n");
  memcpy(&testG, &G, sizeof(struct gameState));
  testG.supplyCount[province] = 0;
  testResult = isGameOver(&testG);

  assert(testResult == 1);

  // ----------- TEST 2 -----------------------------------------------
  printf("TEST 2: Game is over because 3 supply piles are empty\n");
  memcpy(&testG, &G, sizeof(struct gameState));
  testG.supplyCount[smithy] = 0;
  testG.supplyCount[tribute] = 0;
  testG.supplyCount[embargo] = 0;
  testResult = isGameOver(&testG);

  assert(testResult == 1);

  // ----------- TEST 3 -----------------------------------------------
  printf("TEST 3: Game isn't over\n");
  memcpy(&testG, &G, sizeof(struct gameState));
  testResult = isGameOver(&testG);

  assert(testResult == 0);
  return 0;
}
