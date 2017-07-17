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

  initializeGame(numPlayers, k, seed, &G);

  printf("TESTING handCard\n");
  printf("-----------------------------------------\n");

  // ----------- TEST 1: Card in hand is correct --------------
  printf("TEST 1: Correct card is in hand position\n");
  G.whoseTurn = 0;
  G.hand[thisPlayer][0] = steward;
  G.hand[thisPlayer][1] = copper;
  G.hand[thisPlayer][2] = duchy;
  G.hand[thisPlayer][3] = estate;
  G.hand[thisPlayer][4] = feast;

  int testResult = handCard(2, &G);

  assert(testResult == duchy);

  return 0;
}
