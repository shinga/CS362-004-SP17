/****************************
 *  randomtestcardaventurer.c
 *  Random test for the p_adventurer function
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
#include "interface.h"



int checkAdventurer(int p, struct gameState *post) {
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r, expectedCardsDrawn;
  int secondTreasPos = -1;
  int handTreasures = 0;
  int deckTreasures = 0;


  r = p_adventurer(post, p);
  ASSERTTRUE(r == 0);

    int x;
    //Get number of treasures in pre hand
    for(x = 0; x < pre.handCount[p]; x++){
        if (pre.hand[p][x] == copper || pre.hand[p][x] == silver || pre.hand[p][x] == gold){
            handTreasures++;
        }
    }
    //Get number of treasures in deck
    if (pre.deckCount[p] > 0){
        for(x = pre.deckCount[p]-1; x >= 0; x--){
            if (pre.deck[p][x] == copper || pre.deck[p][x] == silver || pre.deck[p][x] == gold){
                deckTreasures++;
                if(deckTreasures == 2){
                    secondTreasPos = x;
                }
            }
        }
    }
    int y;
    //If not enough treasures in deck, get treasures in discard pile
    if(deckTreasures < 2){
        for(y = pre.discardCount[p]-1; y >= 0; y--){
            if (pre.discard[p][y] == copper || pre.discard[p][y] == silver || pre.discard[p][y] == gold){
                deckTreasures++;
                secondTreasPos = -1;
            }
        }
    }
    //If there are enough treasures, get how many cards will be drawn
    else{
        expectedCardsDrawn = pre.deckCount[p] - secondTreasPos - 2;
    }

    // Now we have the number of treasures in hand
    // Now we have, if there are 2 treasures in deck, the position of the second treasure
        // Check expectedCardsDrawn with discard pile.

    // Now we have, if there is only 0 or 1 treasure in deck/discard, the fact thereof.
        // Check if there are no cards in deck (has yet to shuffle)
        // Check if hand gained treasures
        // Check if deck/discard has lost treasures

    // If
        // Check if deck has 2 less treasures
        // Check if hand has 2 more treasures
          //



    //IF TWO TREASURES:
        // Check if deck has 2 less treasures
        // check if hand gained 2 treasures
        // check if discard gained expected amount of cards
    if (deckTreasures > 2){
        // printf("post->deckCount[p] == (pre.deckCount[p] + 2) \n %d == %d\n",post->deckCount[p], (pre.deckCount[p] - expectedCardsDrawn));
        // ASSERTTRUE(post->deckCount[p] == (pre.deckCount[p] + 2));
        int it = 0;
        int numtreas = 0;
        for (it = 0; it < post->deckCount[p]; it++) {
            if (post->deck[p][it] == copper || post->deck[p][it] == silver || post->deck[p][it] == gold)
            numtreas++;
        }
        ASSERTTRUE(numtreas == (deckTreasures - 2));
        numtreas = 0;
        for (it = 0; it < post->handCount[p]; it++) {
            if (post->hand[p][it] == copper || post->hand[p][it] == silver || post->hand[p][it] == gold)
            numtreas++;
        }
        ASSERTTRUE(numtreas == (handTreasures + 2));
        ASSERTTRUE(post->discardCount[p] == (pre.discardCount[p] + expectedCardsDrawn));

    }

    // If deck only had 1 treasure, check if deck is shuffled
    // If discard had +1 treasure, check if hand has 2 more treasures
    // Otherwise check if hand has 1 more treasure
    if (deckTreasures < 2) {
        int it = 0;
        int numtreas = 0;
        for (it = 0; it < post->deckCount[p]; it++) {
            if (post->deck[p][it] == copper || post->deck[p][it] == silver || post->deck[p][it] == gold)
            numtreas++;
        }
        for (it = 0; it < post->discardCount[p]; it++) {
            if (post->discard[p][it] == copper || post->discard[p][it] == silver || post->discard[p][it] == gold)
            numtreas++;
        }
        ASSERTTRUE(numtreas == 0);
        numtreas = 0;
        for (it = 0; it < post->handCount[p]; it++) {
            if (post->hand[p][it] == copper || post->hand[p][it] == silver || post->hand[p][it] == gold)
            numtreas++;
        }
        ASSERTTRUE(numtreas == (handTreasures + deckTreasures));
    }

    return 0;
}

int main () {

  int i, n, m, p;

  struct gameState G;

  printf ("Testing p_adventurer.\n");

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
    for(m = 0; m < G.handCount[p]; m++){
        G.hand[p][m] = floor(Random() * 26);
    }
    for(m = 0; m < G.deckCount[p]; m++){
        G.deck[p][m] = floor(Random() * 26);
    }
    for(m = 0; m < G.discardCount[p]; m++){
        G.discard[p][m] = floor(Random() * 26);
    }
    checkAdventurer(p, &G);
  }


  exit(0);
  return 0;
}
