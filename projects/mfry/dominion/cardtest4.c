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

  printf("TESTING great hall\n");
  printf("-----------------------------------------\n");

  // ----------- TEST 1 -----------------------------------------------
  printf("TEST 1: 1 card is drawn\n");
  G.handCount[thisPlayer] = 5;
  G.hand[thisPlayer][0] = great_hall;
  memcpy(&testG, &G, sizeof(struct gameState));

  greatHallEffect(thisPlayer, &testG, 0);

  printf("expected: %d \tactual: %d\n", G.handCount[thisPlayer], testG.handCount[thisPlayer]);
  assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);

  // ----------- TEST 1 -----------------------------------------------
  printf("TEST 2: Actions increase by 1\n");
  printf("expected: %d \tactual: %d\n", G.numActions + 1, testG.numActions);
  assert(G.numActions+1 == testG.numActions);
  return 0;
}
