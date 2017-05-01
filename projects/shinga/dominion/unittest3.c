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
    int seed = 1000;
    // int coins;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int cardNo;
    int numPlayer = 2;
    int maxcardNo = 10;
    char name[MAX_STRING_LENGTH];
    printf("Unit Test 3\n");

    printf ("TESTING supplyCount():\n");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    for (cardNo = 0; cardNo < maxcardNo; cardNo++)
    {
        #if (NOISY_TEST == 1)
        cardNumToName(k[cardNo], name);
        printf("Testing supply count of %s\n", name);
        #endif
        ASSERTTRUE(supplyCount(k[cardNo],&G) == G.supplyCount[k[cardNo]]);
    }

    printf("All tests passed!\n");

    return 0;
}
