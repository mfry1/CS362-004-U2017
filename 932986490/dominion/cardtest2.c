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

  printf("TESTING adventurer\n");
  printf("-----------------------------------------\n");

  // ----------- TEST 1 -----------------------------------------------
  printf("TEST 1: Hand has 2 more treasure cards\n");
  G.handCount[thisPlayer] = 5;
  for(int i = 0; i < G.handCount[thisPlayer]; i++){
    G.hand[thisPlayer][i] = smithy;
  }
  memcpy(&testG, &G, sizeof(struct gameState));

  adventurerEffect(thisPlayer, &testG);

  int treasureCount = 0;
  for(int i = 0; i < testG.handCount[thisPlayer]; i++){
      if(testG.hand[thisPlayer][i] == copper ||
           testG.hand[thisPlayer][i] == silver ||
           testG.hand[thisPlayer][i] == gold){
        treasureCount++;
       }
  }

  printf("expected: %d \tactual: %d\n", 3, treasureCount);
  assert(treasureCount == 3);

  return 0;
}
