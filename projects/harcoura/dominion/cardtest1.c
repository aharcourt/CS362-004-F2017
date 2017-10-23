/*
 * cardtest1.c
 */

/*
 * Include the following lines in your makefile:
     *
     * cardtest1: cardtest1.c dominion.o rngs.o
     *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
     */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int TOTAL_FAILURES = 0;

void assertEqual(int actual, int expected){
    if (expected != actual) {
        printf(" >>> TEST FAILED <<<\n");
        TOTAL_FAILURES++;
    }
}
int main() {
    int i;
    int newCards = 2;
    int discarded = 1;
    int copperVal = 1, silverVal = 2, goldVal = 3;
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

	// ----------- TEST SET 1: +2 cards --------------
	printf("\nTEST SET 1: +2 CARDS\n");
    
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("Hand count (Player 1) = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    
    printf("Deck count (Player 1) = %d, Expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
    assertEqual(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
    
    updateCoins(thisPlayer, &testG, bonus);
    
	printf("Coins (Player 1) = %d, Expected = %d\n", testG.coins, G.coins + copperVal * 2);
	assertEqual(testG.coins, G.coins + copperVal * 2);
    
    // ----------- TEST SET 2: Ensure only treasure cards are kept --------------
	printf("\nTEST SET 2: ENSURE ONLY TREASURE CARDS ARE KEPT\n");
    
    // Initialize a game
	initializeGame(numPlayers, kingdomCards, seed, &G);
   
    // Set player decks 
    G.deckCount[thisPlayer] = 0;
    
    for (i = 0; i < treasure_map; i++) {
      G.deck[thisPlayer][i] = i;
      G.deckCount[thisPlayer]++;
    }
    
    //Set deck
    G.deck[thisPlayer][copper] = curse;
    G.deck[thisPlayer][silver] = estate;
    G.deck[thisPlayer][gold] = duchy;
    
    G.deck[thisPlayer][curse] = copper;
    G.deck[thisPlayer][estate] = silver;
    G.deck[thisPlayer][duchy] = gold;
    
    // Copy the game state to a test game
	memcpy(&testG, &G, sizeof(struct gameState));
    
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    printf("Hand count (Player 1) = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    
    printf("Deck count (Player 1) = %d, Expected = %d\n", testG.deckCount[thisPlayer], 1);
    assertEqual(testG.deckCount[thisPlayer], 1);
    
    updateCoins(thisPlayer, &testG, bonus);
    
	printf("Coins (Player 1) = %d, Expected = %d\n", testG.coins, G.coins + silverVal + goldVal);
	assertEqual(testG.coins, G.coins + silverVal + goldVal);
    
    // ----------- TEST SET 3: Ensure all treasure card types are kept --------------
	printf("\nTEST SET 3: ENSURE ALL TREASURE CARD TYPES ARE KEPT\n");
    
    // Initialize a game
	initializeGame(numPlayers, kingdomCards, seed, &G);
   
    // Set player decks 
    G.deckCount[thisPlayer] = 0;
    
    for (i = 0; i < treasure_map; i++) {
      G.deck[thisPlayer][i] = i;
      G.deckCount[thisPlayer]++;
    }
    
    //Set deck
    G.deck[thisPlayer][copper] = curse;
    G.deck[thisPlayer][silver] = estate;
    G.deck[thisPlayer][gold] = duchy;
    
    G.deck[thisPlayer][curse] = gold;
    G.deck[thisPlayer][estate] = silver;
    G.deck[thisPlayer][duchy] = copper;
    
    // Copy the game state to a test game
	memcpy(&testG, &G, sizeof(struct gameState));
    
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    printf("Hand count (Player 1) = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    
    printf("Deck count (Player 1) = %d, Expected = %d\n", testG.deckCount[thisPlayer], 1);
    assertEqual(testG.deckCount[thisPlayer], 1);
    
    updateCoins(thisPlayer, &testG, bonus);
    
	printf("Coins (Player 1) = %d, Expected = %d\n", testG.coins, G.coins + silverVal + copperVal);
	assertEqual(testG.coins, G.coins + silverVal + copperVal);
    
    
    // ----------- TEST SET 4: No state changes for other player --------------
	printf("\nTEST SET 4: NO STATE CHANGES FOR OTHER PLAYER\n");

	printf("Hand count (Player 2) = %d, Expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
    assertEqual(testG.handCount[otherPlayer], G.handCount[otherPlayer]);
    
    printf("Deck count (Player 2) = %d, Expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
    assertEqual(testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);

    printf("Discard count (Player 2) = %d, Expected = %d\n", testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
    assertEqual(testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);

	// ----------- TEST SET 5: No state changes in card piles --------------
	printf("\nTEST SET 5: NO STATE CHANGES IN CARD PILES\n");

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


