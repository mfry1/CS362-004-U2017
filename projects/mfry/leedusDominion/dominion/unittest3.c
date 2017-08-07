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

  printf("TESTING gainCard\n");
  printf("-----------------------------------------\n");

  G.whoseTurn = thisPlayer;
  G.handCount[0] = 5;
  G.hand[thisPlayer][0] = steward;
  G.hand[thisPlayer][1] = copper;
  G.hand[thisPlayer][2] = duchy;
  G.hand[thisPlayer][3] = estate;
  G.hand[thisPlayer][4] = feast;
  G.handCount[thisPlayer];
  memcpy(&testG, &G, sizeof(struct gameState));

  printf("TEST 1: Card is added to hand\n");
  gainCard(smithy, &testG, 2, 0);
  int cardFound = 0;
  for(int i = 0; i < testG.handCount[thisPlayer]; i++){
    if(testG.hand[thisPlayer][i] == smithy){
      cardFound = 1;
    }
  }
  assert(cardFound == 1);

  printf("TEST 2: Card is removed from pile\n");
  assert(testG.supplyCount[smithy] = G.supplyCount[smithy] - 1);
  return 0;
}
