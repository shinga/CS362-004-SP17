#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
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
  int discTreasures = 0;


  r = p_adventurer(post, p);


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
        // If deck only had 1 treasure, check if deck is shuffled
          // If discard had +1 treasure, check if hand has 2 more treasures
          // Otherwise check if hand has 1 more treasure
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
        // printf("numtreas == (deckTreasures - 2) \n %d == %d\n", numtreas, deckTreasures-2 );
        ASSERTTRUE(numtreas == (deckTreasures - 2));
        numtreas = 0;
        for (it = 0; it < post->handCount[p]; it++) {
            if (post->hand[p][it] == copper || post->hand[p][it] == silver || post->hand[p][it] == gold)
            numtreas++;
        }
        ASSERTTRUE(numtreas == (handTreasures + 2));
        ASSERTTRUE(post->discardCount[p] == (pre.discardCount[p] + expectedCardsDrawn));
        //
        // if(post->discardCount[p] != (pre.discardCount[p] + expectedCardsDrawn)){
        //     printf("post->discardCount[p] == (pre.discardCount[p] + expectedCardsDrawn)\n %5d == %-23d\n", post->discardCount[p], pre.discardCount[p] + expectedCardsDrawn);
        // }
    }





  //
  // if (pre.deckCount[p] > 0) {
  //   pre.handCount[p]++;
  //   pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1];
  //   pre.deckCount[p]--;
  // } else if (pre.discardCount[p] > 0) {
  //   memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
  //   memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
  //   pre.hand[p][post->handCount[p]-1] = post->hand[p][post->handCount[p]-1];
  //   pre.handCount[p]++;
  //   pre.deckCount[p] = pre.discardCount[p]-1;
  //   pre.discardCount[p] = 0;
  // }
  //
  // assert (r == 0);
  //
  // assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
}

int main () {

  int i, n, m, r, p, deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing drawCard.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

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

  printf ("ALL TESTS OK\n");

  exit(0);

  printf ("SIMPLE FIXED TESTS.\n");
  for (p = 0; p < 2; p++) {
    for (deckCount = 0; deckCount < 5; deckCount++) {
      for (discardCount = 0; discardCount < 5; discardCount++) {
	for (handCount = 0; handCount < 5; handCount++) {
	  memset(&G, 23, sizeof(struct gameState));
	  r = initializeGame(2, k, 1, &G);
	  G.deckCount[p] = deckCount;
	  memset(G.deck[p], 0, sizeof(int) * deckCount);
	  G.discardCount[p] = discardCount;
	  memset(G.discard[p], 0, sizeof(int) * discardCount);
	  G.handCount[p] = handCount;
	  memset(G.hand[p], 0, sizeof(int) * handCount);
	  checkDrawCard(p, &G);
	}
      }
    }
  }

  return 0;
}
