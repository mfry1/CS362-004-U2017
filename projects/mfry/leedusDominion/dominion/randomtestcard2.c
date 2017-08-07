#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define NUM_TESTS 100

int main() {
  int i, j, player_count, player, seed, hand_size, actions_before, pass, fail;

  pass = 0;
  fail = 0;

  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
  struct gameState G;

  printf("Start Great Hall Test\n");

  for (i = 0; i < NUM_TESTS; i++) {
    srand(time(NULL));
    player_count = rand() %2 + 2;
    seed = rand() % 100;

    if (initializeGame(player_count, k, seed, &G) == -1) {
      printf("Failed to start a random game\n");
      fail++;
      continue;
    }

    player = rand() % player_count;
    G.whoseTurn = player;
    G.numActions = 1;
    G.handCount[player] = 5;
    G.deckCount[player] = floor(rand() % MAX_DECK) + 1;
    G.discardCount[player] = 0;

    // generate the deck
    for (j = 0; j < G.deckCount[player]; j++) {
      G.deck[player][j] = rand() % treasure_map;
    }

    // generate player's hand
    for (j = 0; j < G.handCount[player]; j++) {
      G.hand[player][j] = rand() % treasure_map;
    }

    // add great hall to player's hand
    G.hand[player][0] = great_hall;
    hand_size = G.handCount[player];
    actions_before = G.numActions;

    playCard(0, 0, 0, 0, &G);

    // 1 card should be added to the player's hand
    if (G.handCount[player] != hand_size) {
      fail++;
      continue;
    }

    // 1 action should be added
    if (G.numActions != actions_before) {
      fail++;
      continue;
    }

    pass++;
  }

  printf("Number Passed: %d\n", pass);
  printf("Number Failed: %d\n", fail);
  printf("End Great Hall Test");
}
