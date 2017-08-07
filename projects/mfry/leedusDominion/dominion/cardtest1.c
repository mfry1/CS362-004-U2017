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

  printf("TESTING smithy\n");
  printf("-----------------------------------------\n");

  // ----------- TEST 1 -----------------------------------------------
  printf("TEST 1: 3 cards are added to hand\n");
  G.handCount[thisPlayer] = 5;
  memcpy(&testG, &G, sizeof(struct gameState));
  testG.hand[thisPlayer][0] = smithy;

  newSmithy(&testG, 0);
  printf("expected: %d \tactual: %d\n", G.handCount[thisPlayer] + 3 - 1, testG.handCount[thisPlayer]);
  assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 3 - 1);

  return 0;
}
