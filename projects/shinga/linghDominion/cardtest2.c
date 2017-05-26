/* -----------------------------------------------------------------------
 * Card Test 2, Based off of testUpdateCoins.c
 * Testing the function p_adventurer()
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
    struct gameState G, testG;
    int p;
    int numPlayers = 4;
    int i, y;
    int money = copper;
    int drawnone, drawntwo;

    printf("Card Test 2\n");

    printf ("TESTING playAdventurer():\n");

    for (p = 0; p < numPlayers; p++)
    {
        for(money = 4; money < 7; money++){ // Test copper, silver, gold

            memset(&G, 23, sizeof(struct gameState));   // clear the game state
            initializeGame(numPlayers, k, seed, &G); // initialize a new game
            G.whoseTurn = p; // Set correct turn


            addCardToHand(p, adventurer, &G);



            // Test if newly drawn card(s) are treasures

            // Test if drawn cards are discarded

            G.deckCount[p] = 5;
            for(y = 0; y < G.deckCount[p]; y++){
                G.deck[p][y] = smithy;
            }
            G.deck[p][0] = money;
            G.deck[p][1] = money;
            G.deckCount[p]++;
            memcpy(&testG, &G, sizeof(struct gameState));

            int treas = 0;
            for(y = 4; y >= 0; y--){
                if(testG.deck[p][y] != money){
                    testG.discard[p][testG.discardCount[p]] = testG.deck[p][y];
                    testG.discardCount[p]++;
                    testG.deckCount[p]--;
                } else if(testG.deck[p][y] == money) {
                    treas++;
                    testG.deckCount[p]--;
                    if(treas == 2) break;
                }
            }




            playAdventurer(&G);

            int j;
            // Test if cards were discarded
            for(j = 0; j < G.discardCount[p]; j++){
                ASSERTTRUE(G.discard[p][j] == testG.discard[p][j]);
            }

            // Test if victory/kingdom supply was untouched
            for(i = 0; i < 25; i++){
                ASSERTTRUE(G.supplyCount[i] == testG.supplyCount[i]);
            }

            // Test if new drawn cards are treasures
            drawnone = G.hand[p][G.handCount[p]-1];
            drawntwo = G.hand[p][G.handCount[p]-2];
            ASSERTTRUE(drawnone == copper || drawnone == silver || drawnone == gold);
            ASSERTTRUE(drawntwo == copper || drawntwo == silver || drawntwo == gold);



            // Test if resolves when there is only one treasure left in deck
            printf("Testing if p_adventurer works when there is only one treasure in deck...\n");
            G.deckCount[p] = 4;
            for(y = 0; y < G.deckCount[p]; y++){
                G.deck[p][y] = curse;
            }
            G.deck[p][2] = money;
            // printHand(p,&G);
            // printDeck(p,&G);

            playAdventurer(&G);

            // Test if victory/kingdom supply was untouched
            for(i = 0; i < 25; i++){
                ASSERTTRUE(G.supplyCount[i] == testG.supplyCount[i]);
            }

            // Test if new drawn cards are treasures
            drawnone = G.hand[p][G.handCount[p]-1];
            drawntwo = G.hand[p][G.handCount[p]-2];
            ASSERTTRUE(drawnone == copper || drawnone == silver || drawnone == gold);
            ASSERTTRUE(drawntwo == copper || drawntwo == silver || drawntwo == gold);
            // printHand(p,&G);
            // printDeck(p,&G);


        }


    }

    printf("All tests passed!\n");

    return 0;
}
