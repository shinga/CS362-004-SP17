/* -----------------------------------------------------------------------
 * Unit Test 1, Based off of testUpdateCoins.c
 * Testing the function gainCard()
 *
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "myassert.h"
#include "rngs.h"
#include "interface.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    // int i;
    int seed = 1000;
    int numPlayer = 2;
    int p, cardNo, y;
    // int coins;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxcardNo = 10;
    int tempSupp = 0;
    int tempHandCount;
    int tempDeckCount = 0;
    int tempDiscardCount = 0;
    char name[MAX_STRING_LENGTH];
    int flag;
    // // arrays of all coppers, silvers, and golds
    // int coppers[MAX_HAND];
    // int silvers[MAX_HAND];
    // int golds[MAX_HAND];
    // for (i = 0; i < MAX_HAND; i++)
    // {
    //     coppers[i] = copper;
    //     silvers[i] = silver;
    //     golds[i] = gold;
    // }
    printf("Unit Test 2\n");

    printf ("TESTING gainCards():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (cardNo = 0; cardNo < maxcardNo; cardNo++)
        {
            for(flag = 0; flag < 3; flag++)
            {
#if (NOISY_TEST == 1)
                cardNumToName(k[cardNo], name);
                switch (flag) {
                    case 0:
                        printf("Test player %d to gain card %s to discard.\n", p, name);
                        break;
                    case 1:
                        printf("Test player %d to gain card %s to deck.\n", p, name);
                        break;
                    case 2:
                        printf("Test player %d to gain card %s to hand.\n", p, name);
                        break;
                }
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.whoseTurn = p; // Set correct turn
                if(p != 0){
                    for (y = 0; y < 5; y++){
                        drawCard(p, &G);//Draw a card
                    }
                }

            /***
            * Test if gain does not work when no supply
            *
            *
            **/

                G.supplyCount[k[cardNo]] = 0;

                tempSupp = supplyCount(k[cardNo], &G);
                tempHandCount = G.handCount[p];
                tempDeckCount = G.deckCount[p];
                tempDiscardCount = G.discardCount[p];

                gainCard(k[cardNo], &G, flag, p);

                // Check if supply has not changed (it should not have)
                ASSERTTRUE(tempSupp == supplyCount(k[cardNo], &G));
                // Check if hand has not added cards (it should not have)
                ASSERTTRUE(tempHandCount == G.handCount[p]);
                // Check if deck has not added cardsd (it should not have)
                ASSERTTRUE(tempDeckCount == G.deckCount[p]);
                // Check if discard pile has not added cards
                ASSERTTRUE(tempDiscardCount == G.discardCount[p]);
                // printf("Card %d is not %d at hand index %d and former index %d\n", G.hand[p][G.handCount[p]-1], tempHand[x], G.handCount[p]-1, x);


            /***
            * Test if gain does what it should when adding to [flag] (discard,deck,hand)
            *
            *
            **/

                G.supplyCount[k[cardNo]] = 2;

                tempSupp = supplyCount(k[cardNo], &G);
                tempHandCount = G.handCount[p];
                tempDeckCount = G.deckCount[p];
                tempDiscardCount = G.discardCount[p];

                gainCard(k[cardNo], &G, flag, p);

                // Check if supply has changed (it should have)
                ASSERTTRUE(supplyCount(k[cardNo], &G) == tempSupp - 1);
                switch (flag) {
                    case 0:
                        // Check if discard pile has added cards
                        ASSERTTRUE(G.discardCount[p] == tempDiscardCount + 1);
                        // Check if hand has not added cards (it should not have)
                        ASSERTTRUE(tempHandCount == G.handCount[p]);
                        // Check if deck has not added cardsd (it should not have)
                        ASSERTTRUE(tempDeckCount == G.deckCount[p]);
                        break;
                    case 1:
                        // Check if hand has not added cards (it should not have)
                        ASSERTTRUE(tempHandCount == G.handCount[p]);
                        // Check if deck has not added cardsd (it should not have)
                        ASSERTTRUE(tempDeckCount + 1 == G.deckCount[p]);
                        // Check if discard pile has not added cards
                        ASSERTTRUE(tempDiscardCount == G.discardCount[p]);
                        break;
                    case 2:
                        // Check if hand has not added cards (it should not have)
                        ASSERTTRUE(tempHandCount + 1 == G.handCount[p]);
                        // Check if deck has not added cardsd (it should not have)
                        ASSERTTRUE(tempDeckCount == G.deckCount[p]);
                        // Check if discard pile has not added cards
                        ASSERTTRUE(tempDiscardCount == G.discardCount[p]);
                        break;
                    default: assert(0);
                }



            }
        }
    }

    printf("All tests passed!\n");

    return 0;
}
