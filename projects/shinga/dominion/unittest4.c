/* -----------------------------------------------------------------------
 * Unit Test 4, Based off of testUpdateCoins.c
 * Testing the function numHandCards()
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
    int p;
    int numPlayer = 4;
    printf("Unit Test 4\n");

    printf ("TESTING numHandCards():\n");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    for (p = 0; p < numPlayer; p++)
    {
        G.handCount[p] = p + 5;
#if (NOISY_TEST == 1)
        printf("Testing hand count of player %d\n", p);
#endif
        ASSERTTRUE(numHandCards(&G) == p + 5);
        ++G.whoseTurn;
    }

    printf("All tests passed!\n");

    return 0;
}
