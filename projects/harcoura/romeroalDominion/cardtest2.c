/*
 * cardtest2.c
 */

/*
 * Include the following lines in your makefile:
     *
     * cardtest2: cardtest2.c dominion.o rngs.o
     *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
     */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int TOTAL_FAILURES = 0;

void assertEqual(int actual, int expected){
    if (expected != actual) {
        printf(" >>> TEST FAILED <<<\n");
        TOTAL_FAILURES++;
    }
}
int main() {
    int i;
    int newCards = 3;
    int discarded = 1;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 11;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer = 1;
	struct gameState G, testG;
	int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
            

	// Initialize a game
	initializeGame(numPlayers, kingdomCards, seed, &G);
    
    // Copy the game state to a test game
	memcpy(&testG, &G, sizeof(struct gameState));
    
	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST SET 1: +3 cards --------------
	printf("\nTEST SET 1: +3 CARDS\n");
    
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("Hand count (Player 1) = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    
    printf("Deck count (Player 1) = %d, Expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
    assertEqual(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
        
	printf("Coins (Player 1) = %d, Expected = %d\n", testG.coins, G.coins);
	assertEqual(testG.coins, G.coins);
    
    
    // ----------- TEST SET 2: No state changes for other player --------------
	printf("\nTEST SET 2: NO STATE CHANGES FOR OTHER PLAYER\n");

	printf("Hand count (Player 2) = %d, Expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
    assertEqual(testG.handCount[otherPlayer], G.handCount[otherPlayer]);
    
    printf("Deck count (Player 2) = %d, Expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
    assertEqual(testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);

    printf("Discard count (Player 2) = %d, Expected = %d\n", testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
    assertEqual(testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);

	// ----------- TEST SET 3: No state changes in card piles --------------
	printf("\nTEST SET 3: NO STATE CHANGES IN CARD PILES\n");

    // Test that Treasure card states did not change.
    printf("Treasure cards: Copper = %d, Silver = %d, Gold = %d\nExpected: Copper = %d, Silver = %d, Gold = %d\n", 
        testG.supplyCount[copper], testG.supplyCount[silver], testG.supplyCount[gold], G.supplyCount[copper], G.supplyCount[silver], G.supplyCount[gold]);
    assertEqual(testG.supplyCount[copper], G.supplyCount[copper]);
    assertEqual(testG.supplyCount[silver], G.supplyCount[silver]);
    assertEqual(testG.supplyCount[gold], G.supplyCount[gold]);
    
    // Test that Victory card states did not change.
    printf("Victory cards: Estate = %d, Duchy = %d, Province = %d\nExpected: Estate = %d, Duchy = %d, Province = %d\n", 
        testG.supplyCount[estate], testG.supplyCount[duchy], testG.supplyCount[province], G.supplyCount[estate], G.supplyCount[duchy], G.supplyCount[province]);
    assertEqual(testG.supplyCount[estate], G.supplyCount[estate]);
    assertEqual(testG.supplyCount[duchy], G.supplyCount[duchy]);
    assertEqual(testG.supplyCount[province], G.supplyCount[province]);
    
    
    // Test that Kingdom card states did not change. 
    for (i = 0; i < 10; i++) {  
        printf("Kingdom card %d = %d, Expected = %d\n", i + 1, testG.supplyCount[(kingdomCards[i])], G.supplyCount[kingdomCards[i]]);
        assertEqual(testG.supplyCount[kingdomCards[i]], G.supplyCount[kingdomCards[i]]);      
    }  
    
    if (TOTAL_FAILURES) {
        printf("\n >>>>> TESTING FAILED: %s testing complete with %d failures. <<<<<\n\n", TESTCARD, TOTAL_FAILURES);
    }
    else {
        printf("\n >>>>> SUCCESS: %s testing complete. <<<<<\n\n", TESTCARD);
    }

	return 0;
}


