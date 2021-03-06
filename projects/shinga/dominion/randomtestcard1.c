/****************************
 *  randomtestcard1.c
 *  Random test for the p_smithy function
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

int checkSmithy(int p, struct gameState *post) {
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r;
  //  printf ("Smithy PRE: p %d HC %d DeC %d DiC %d\n",
  //	  p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);

  r = p_smithy (post, p, 0);

  //printf ("Smithy POST: p %d HC %d DeC %d DiC %d\n",
  //      p, post->handCount[p], post->deckCount[p], post->discardCount[p]);

  if (pre.deckCount[p] > 3) {
    pre.handCount[p]++;
    pre.handCount[p]++;
    pre.handCount[p]++;
    pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-3]; //Set hand to as if it drew a card
    pre.hand[p][pre.handCount[p]-2] = pre.deck[p][pre.deckCount[p]-2]; //Set hand to as if it drew a card
    pre.hand[p][pre.handCount[p]-3] = pre.deck[p][pre.deckCount[p]-1]; //Set hand to as if it drew a card
    pre.deckCount[p]--;
    pre.deckCount[p]--;
    pre.deckCount[p]--;
  } else if (pre.discardCount[p] > 0) {
    memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]); //
    memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
    pre.hand[p][post->handCount[p]-1] = post->hand[p][post->handCount[p]-1]; // set pre hand to what post hand has
    pre.hand[p][post->handCount[p]-2] = post->hand[p][post->handCount[p]-2]; // set pre hand to what post hand has
    pre.hand[p][post->handCount[p]-3] = post->hand[p][post->handCount[p]-3]; // set pre hand to what post hand has
    pre.handCount[p]++;
    pre.handCount[p]++;
    pre.handCount[p]++;
    pre.deckCount[p] = pre.discardCount[p]-3;
    pre.discardCount[p] = 0;
  }



  pre.playedCards[pre.playedCardCount] = pre.hand[p][0];
  pre.playedCardCount++;
  if (0 == (pre.handCount[p] - 1)){
      pre.handCount[p]--;
  }
  else if ( pre.handCount[p] == 1 ){
      pre.handCount[p]--;
  }
  else{
      pre.hand[p][0] = pre.hand[p][ (pre.handCount[p] - 1)];
      pre.hand[p][pre.handCount[p] - 1] = -1;
      pre.handCount[p]--;
  }


  assert (r == 0);
  // printf("Handcount: %5d | %-10d \n", pre.handCount[p], post->handCount[p]);
  // printf("PlayedCards: %5d | %-10d \n", pre.playedCards[0], post->playedCards[0]);
  // printf("PlayedCardCOunt: %5d | %-10d \n", pre.playedCardCount, post->playedCardCount);
  // printf("Deckcount: %5d | %-10d \n", pre.deckCount[p], post->deckCount[p]);
  // printf("discardCount: %5d | %-10d \n", pre.discardCount[p], post->discardCount[p]);
  // printf("hand0: %5d | %-10d \n", pre.hand[p][0], post->hand[p][0]);
  // printf("hand1: %5d | %-10d \n", pre.hand[p][pre.handCount[p]-1], post->hand[p][post->handCount[p]-1]);
  // printf("hand2: %5d | %-10d \n", pre.hand[p][pre.handCount[p]-2], post->hand[p][post->handCount[p]-2]);
  // printf("hand3: %5d | %-10d \n", pre.hand[p][pre.handCount[p]-3], post->hand[p][post->handCount[p]-3]);
  // struct gameState *d1 = &post;
  // struct gameState *d2 = &pre;
  // int di = (d1 - d2) * sizeof(struct gameState);
  // // printf("%x",di);
  ASSERTTRUE(memcmp(&pre, post, sizeof(struct gameState)) == 0);
  return 0;
}

int main () {

  int i, n, m, p;

  struct gameState G;

  printf ("Testing Smithy.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);
  printf("TESTING 2000 TIMES\n");
  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    for(m = 0; m < 3; m++){
        G.deckCount[m] = floor(Random() * MAX_DECK);
        G.discardCount[m] = floor(Random() * MAX_DECK);
        G.handCount[m] = floor(Random() * MAX_HAND);
    }
    G.whoseTurn = p;
    G.playedCardCount = 0;
    checkSmithy(p, &G);
  }

  printf ("IF NO FAILURES, ALL TESTS OK\n");

  exit(0);

  return 0;
}
