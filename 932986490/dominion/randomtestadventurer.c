#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define NUM_OF_TESTS 200

int adventurerValidate(struct gameState *before, struct gameState *after, int player) {
  int expectedHandCount = before->handCount[player] + 2,
      actualHandCount = after->handCount[player],
      expectedDeckAndDiscard = before->deckCount[player] + before->discardCount[player] - 2,
      actualDeckAndDiscard = after->deckCount[player] + after->discardCount[player],
      testPassed = 1,
      befTreasureCount = 0,
      aftTreasureCount = 0,
      i;

  for(i = 0; i < before->handCount[player]; i++) {
    if (before->hand[player][i] == copper || before->hand[player][i] == silver || before->hand[player][i] == gold ) {
      befTreasureCount++;
    }
  }
  for(i = 0; i < after->handCount[player]; i++) {
    if (after->hand[player][i] == copper || after->hand[player][i] == silver || after->hand[player][i] == gold ) {
      aftTreasureCount++;
    }
  }
  // Check that hand count is the same
  if(expectedHandCount != actualHandCount) {
    printf("Test Failed! Hand count: %d, expected: %d\n", actualHandCount, expectedHandCount);
    testPassed = 0;
  }
  // Check that the combined sum of deck and discount is the same (3 drawn to hand and 1 discarded)
  if(expectedDeckAndDiscard != actualDeckAndDiscard) {
    printf("Test Failed! Deck + Discard count: %d, expected: %d\n", actualDeckAndDiscard, expectedDeckAndDiscard);
    testPassed = 0;
  }
  if(befTreasureCount + 2 != aftTreasureCount) {
    printf("Test Failed! Treasures in Hand: %d, expected: %d\n", aftTreasureCount, befTreasureCount+2);
    testPassed = 0;
  }
  return testPassed;
}

int main() {

  struct gameState G, testG;
  int numOfPlayers, i;

  srand(time(NULL));

  printf("TESTING ADVENTURER EFFECT\n");
  printf("---------------------\n");

  for(i = 0; i < NUM_OF_TESTS; i++) {
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room},
        seed = rand(),
        numPlayers = rand() % (MAX_PLAYERS) + 2,
        thisPlayer = rand() % numPlayers;

    initializeGame(numPlayers, k, seed, &G);

    G.handCount[thisPlayer] = rand() % MAX_HAND + 1;
    G.deckCount[thisPlayer] = rand() % MAX_DECK + 2;
    G.discardCount[thisPlayer] = rand() % MAX_DECK;
    G.numActions = rand() % 1000;
    G.deck[thisPlayer][0] = G.deck[thisPlayer][1] = copper ;
    memcpy(&testG, &G, sizeof(struct gameState));

    adventurerEffect(thisPlayer, &testG);

    if(!adventurerValidate(&G, &testG, thisPlayer)){

      printf("SEED: %d, # OF PLAYERS: %d, PLAYER: %d\n\n", seed, numPlayers, thisPlayer);
    };
  }

  return 0;
}
