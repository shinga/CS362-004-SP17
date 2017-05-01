/* -----------------------------------------------------------------------
 * Unit Test 1, Based off of testUpdateCoins.c
 * Testing the function buyCard()
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
    int tempNumBuys = 0;
    int tempCoins = 0;
    int tempPlayer = 0;
    int tempDeckCount = 0;
    int tempDiscardCount = 0;
    char name[MAX_STRING_LENGTH];
    printf("Unit Test 1\n");
    printf ("TESTING buyCards():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (cardNo = 0; cardNo < maxcardNo; cardNo++)
        {

#if (NOISY_TEST == 1)
            cardNumToName(k[cardNo], name);
            printf("Test player %d to buy card %s .\n", p, name);
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
        * Test if buy does not work when no buy actions
        *
        *
        **/

            G.coins = 10;
            tempCoins = G.coins;
            G.numBuys = 0;
            tempNumBuys = G.numBuys;
            tempPlayer = G.whoseTurn;

            tempSupp = supplyCount(k[cardNo], &G);
            tempHandCount = G.handCount[p];
            tempDeckCount = G.deckCount[p];
            tempDiscardCount = G.discardCount[p];

            buyCard(k[cardNo], &G);

            // Check if supply has not changed (it should not have)
            ASSERTTRUE(tempSupp == supplyCount(k[cardNo], &G));
            // Check if hand has not added cards (it should not have)
            ASSERTTRUE(tempHandCount == G.handCount[p]);
            // Check if deck has not added cardsd (it should not have)
            ASSERTTRUE(tempDeckCount == G.deckCount[p]);
            // Check if discard pile has not added cards
            ASSERTTRUE(tempDiscardCount == G.discardCount[p]);
            // printf("Card %d is not %d at hand index %d and former index %d\n", G.hand[p][G.handCount[p]-1], tempHand[x], G.handCount[p]-1, x);
            // Check if coins has not changed ("")
            ASSERTTRUE(tempCoins == G.coins);
            // Check if number of buys has not changed ("")
            ASSERTTRUE(tempNumBuys == G.numBuys);
            // Check if it's still the player's turn
            ASSERTTRUE(tempPlayer == G.whoseTurn);

        /***
        * Test if buy does not work when no cards in supply
        *
        *
        ***/


            G.coins = 10;
            tempCoins = G.coins;
            G.numBuys = 5;
            tempNumBuys = G.numBuys;
            tempPlayer = G.whoseTurn;
            G.supplyCount[k[cardNo]] = 0;

            tempSupp = supplyCount(k[cardNo], &G);
            tempHandCount = G.handCount[p];
            tempDeckCount = G.deckCount[p];
            tempDiscardCount = G.discardCount[p];

            buyCard(k[cardNo], &G);

            // Check if supply has not changed (it should not have)
            ASSERTTRUE(tempSupp == supplyCount(k[cardNo], &G));
            // Check if hand has not added cards (it should not have)
            ASSERTTRUE(tempHandCount == G.handCount[p]);
            // Check if deck has not added cardsd (it should not have)
            ASSERTTRUE(tempDeckCount == G.deckCount[p]);
            // Check if discard pile has not added cards
            ASSERTTRUE(tempDiscardCount == G.discardCount[p]);
            // Check if coins has not changed ("")
            ASSERTTRUE(tempCoins == G.coins);
            // Check if number of buys has not changed ("")
            ASSERTTRUE(tempNumBuys == G.numBuys);
            // Check if it's still the player's turn
            ASSERTTRUE(tempPlayer == G.whoseTurn);

        /****
        * Test if buy does not work when not enough coins
        *
        *
        **/

            G.coins = getCost(k[cardNo]) - 1;
            tempCoins = G.coins;
            G.numBuys = 5;
            tempNumBuys = G.numBuys;
            tempPlayer = G.whoseTurn;
            G.supplyCount[k[cardNo]] = 5;

            tempSupp = supplyCount(k[cardNo], &G);
            tempHandCount = G.handCount[p];
            tempDeckCount = G.deckCount[p];
            tempDiscardCount = G.discardCount[p];

            buyCard(k[cardNo], &G);

            // Check if supply has not changed (it should not have)
            ASSERTTRUE(tempSupp == supplyCount(k[cardNo], &G));
            // Check if hand has not added cards (it should not have)
            ASSERTTRUE(tempHandCount == G.handCount[p]);
            // Check if deck has not added cardsd (it should not have)
            ASSERTTRUE(tempDeckCount == G.deckCount[p]);
            // Check if discard pile has not added cards
            ASSERTTRUE(tempDiscardCount == G.discardCount[p]);
            // Check if coins has not changed ("")
            ASSERTTRUE(tempCoins == G.coins);
            // Check if number of buys has not changed ("")
            ASSERTTRUE(tempNumBuys == G.numBuys);
            // Check if it's still the player's turn
            ASSERTTRUE(tempPlayer == G.whoseTurn);

        /****
        * Test if buy does work
        *
        *
        **/
            G.coins = getCost(k[cardNo]) + 1;
            tempCoins = G.coins;
            G.numBuys = 5;
            tempNumBuys = G.numBuys;
            tempPlayer = G.whoseTurn;
            G.supplyCount[k[cardNo]] = 5;

            tempSupp = supplyCount(k[cardNo], &G);
            tempHandCount = G.handCount[p];
            tempDeckCount = G.deckCount[p];
            tempDiscardCount = G.discardCount[p];

            buyCard(k[cardNo], &G);

            // Check if supply has changed (it should have)
            ASSERTTRUE(supplyCount(k[cardNo], &G) == tempSupp - 1);
            // Check if hand has not added cards (it should not have)
            ASSERTTRUE(tempHandCount == G.handCount[p]);
            // Check if deck has not added cardsd (it should not have)
            ASSERTTRUE(tempDeckCount == G.deckCount[p]);
            // Check if discard pile has added cards
            ASSERTTRUE(G.discardCount[p] == tempDiscardCount + 1);
            // printf("Disc. before: %d, Disc now: %d\n", tempDiscardCount, G.discardCount[p]);
            // Check if coins were taken
            ASSERTTRUE(G.coins == 1);
            // Check if number of buys decremented
            ASSERTTRUE(G.numBuys == tempNumBuys - 1);
            // Check if it's still the player's turn
            ASSERTTRUE(tempPlayer == G.whoseTurn);





        }
    }

    printf("All tests passed!\n");

    return 0;
}
