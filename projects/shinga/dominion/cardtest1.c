/* -----------------------------------------------------------------------
 * Card Test 1, Based off of testUpdateCoins.c
 * Testing the function p_smithy()
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
    int numPlayers = 4;
    int tPlayerHand[numPlayers];
    int tPlayerDeck[numPlayers];
    int tempSupply[25];
    int tempHandCount, tempDeckCount;//, tempLastPlayedCard, tempPlayedCount;
    int i, y;

    printf("Card Test 1\n");
    printf ("TESTING p_smithy():\n");

    for (p = 0; p < numPlayers; p++)
    {
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayers, k, seed, &G); // initialize a new game
        G.whoseTurn = p; // Set correct turn
        if(p != 0){
            for (y = 0; y < 5; y++){
                drawCard(p, &G);//Draw a card
            }
        }
        addCardToHand(p, smithy, &G);

        tempHandCount = G.handCount[p];
        tempDeckCount = G.deckCount[p];
        for(i = 0; i < 25; i++){
            if(i != smithy){
                tempSupply[i] = G.supplyCount[i];
            }
        }
        int pl;
        for(pl = 0; pl < numPlayers; pl++){
            tPlayerHand[pl] = G.handCount[pl];
            tPlayerDeck[pl] = G.deckCount[pl];
        }
        p_smithy(&G, p, G.handCount[p]-1);

        // Test if 3 cards are drawn, and one discarded (smithy)
        ASSERTTRUE(G.handCount[p] == tempHandCount + 2);
        // Test if correct card (smithy) was discarded
        ASSERTTRUE(G.playedCards[G.playedCardCount-1] == smithy);
        // Test if deck lost 3
        ASSERTTRUE(G.deckCount[p] == tempDeckCount - 3);
        // Test if other player's state is unchanged (deck, hand, discard)
        for (pl = 0; pl < numPlayers; pl++){
            if(pl != p){
                ASSERTTRUE(G.handCount[pl] == tPlayerHand[pl]);
                ASSERTTRUE(G.deckCount[pl] == tPlayerDeck[pl]);
                }
        }

        // Test if victory/kingdom piles are unchanged
        for(i = 0; i < 25; i++){
            if(i != smithy){
                ASSERTTRUE(G.supplyCount[i] == tempSupply[i]);
            }
        }


    }

    printf("If no assert errors, all tests passed!\n");

    return 0;
}
