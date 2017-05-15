/****************************
 *  randomtestcard2.c
 *  Random test for the p_village function
 *  Arthur Shing CS362 SP2017
 ***************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "myassert.h"
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int checkVillage(int p, struct gameState *post) {
  struct gameState pre;

  int r;
  //  printf ("Village PRE: p %d HC %d DeC %d DiC %d\n",
  //	  p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);
  int handPos = floor(Random() * post->handCount[p]);
  post->hand[p][handPos] = village;

  memcpy (&pre, post, sizeof(struct gameState));
  r = p_village (post, p, handPos);

  //printf ("Village POST: p %d HC %d DeC %d DiC %d\n",
  //      p, post->handCount[p], post->deckCount[p], post->discardCount[p]);

    if (pre.deckCount[p] > 0) {
      pre.handCount[p]++;
      pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1]; //Set hand to as if it drew a card
      pre.deckCount[p]--;
    } else if (pre.discardCount[p] > 0) {
      memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]); //
      memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
      pre.hand[p][post->handCount[p]-1] = post->hand[p][post->handCount[p]-1]; // set pre hand to what post hand has
      pre.handCount[p]++;
      pre.deckCount[p] = pre.discardCount[p]-1;
      pre.discardCount[p] = 0;
    }

  pre.numActions++;
  pre.numActions++;

  pre.hand[p][handPos] = pre.hand[p][pre.handCount[p]-1];
  pre.hand[p][pre.handCount[p]-1] = -1;
  pre.playedCards[pre.playedCardCount] = village;
  pre.playedCardCount++;
  pre.handCount[p]--;


  assert (r == 0);
  // printf("Handcount: %5d | %-10d \n", pre.handCount[p], post->handCount[p]);
  // printf("Deckcount: %5d | %-10d \n", pre.deckCount[p], post->deckCount[p]);
  // printf("discardCount: %5d | %-10d \n", pre.discardCount[p], post->discardCount[p]);
  ASSERTTRUE(memcmp(&pre, post, sizeof(struct gameState)) == 0);
  return 0;
}

int main () {

  int i, n, p;

  struct gameState G;

  printf ("Testing Village.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);
  printf("TESTING 2000 TIMES\n");
  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    G.playedCardCount = 0;
    G.numActions = 0;
    checkVillage(p, &G);
  }

  printf ("IF NO FAILURES, ALL TESTS OK\n");

  exit(0);

  return 0;
}
