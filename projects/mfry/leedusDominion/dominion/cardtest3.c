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

  printf("TESTING embargo\n");
  printf("-----------------------------------------\n");

  // ----------- TEST 1 -----------------------------------------------
  printf("TEST 1: 2 coins are added\n");
  G.handCount[thisPlayer] = 5;
  G.coins = 0;
  G.hand[thisPlayer][0] = embargo;
  memcpy(&testG, &G, sizeof(struct gameState));

  newEmbargo(&testG, 0, 0);

  printf("expected: %d \tactual: %d\n", G.coins + 2, testG.coins);
  assert(G.coins + 2 == testG.coins);

  return 0;
}
