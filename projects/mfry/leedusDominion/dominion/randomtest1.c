#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define NUM_OF_TESTS 200

int smithyValidate(struct gameState *before, struct gameState *after, int player) {
  int expectedHandCount = before->handCount[player] + 2,
      actualHandCount = after->handCount[player],
      expectedDeckAndDiscard = before->deckCount[player] + before->discardCount[player] - 3,
      actualDeckAndDiscard = after->deckCount[player] + after->discardCount[player],
      testPassed = 1;

  // Check that hand has increased 2 cards (drew 3, discarded 1 smithy)
  if(expectedHandCount != actualHandCount) {
    printf("Test Failed! Hand count: %d, expected: %d\n", actualHandCount, expectedHandCount);
    testPassed = 0;
  }
  // Check that the combined sum of deck and discount has decreased by 2 (3 drawn to hand and 1 discarded)
  if(expectedDeckAndDiscard != actualDeckAndDiscard) {
    printf("Test Failed! Deck + Discard count: %d, expected: %d\n", actualDeckAndDiscard, expectedDeckAndDiscard);
    testPassed = 0;
  }

  return testPassed;
}

int main() {
  struct gameState G, testG;
  int numOfPlayers, i;

  srand(time(NULL));

  printf("TESTING SMITHY EFFECT\n");
  printf("---------------------\n");

  for(i = 0; i < NUM_OF_TESTS; i++) {
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room},
        seed = rand(),
        numPlayers = rand() % (MAX_PLAYERS) + 2,
        thisPlayer = rand() % numPlayers,
        handPos;

    initializeGame(numPlayers, k, seed, &G);

    G.handCount[thisPlayer] = rand() % MAX_HAND + 1;
    G.deckCount[thisPlayer] = rand() % MAX_DECK;
    G.discardCount[thisPlayer] = rand() % MAX_DECK;
    handPos = rand() % G.handCount[thisPlayer];

    memcpy(&testG, &G, sizeof(struct gameState));

    newSmithy(&testG, handPos);

    if(!smithyValidate(&G, &testG, thisPlayer)){

      printf("SEED: %d, # OF PLAYERS: %d, PLAYER: %d\n\n", seed, numPlayers, thisPlayer);
    };
  }

  return 0;
}
