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
  struct gameState G;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;

  initializeGame(numPlayers, k, seed, &G);

  printf("TESTING numHandCard\n");
  printf("-----------------------------------------\n");

  // ----------- TEST 1: player 1 has 5 cards in hand --------------
  printf("TEST 1: player 1 has 5 cards in hand\n");
  G.whoseTurn = 0;
  G.handCount[0] = 5;

  int testCount = numHandCards(&G);

  printf("hand count = %d, expected = %d\n", testCount, 5);
  assert(testCount == 5);

  return 0;
}
