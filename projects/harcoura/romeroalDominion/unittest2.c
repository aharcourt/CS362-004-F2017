/*
 * unittest2.c
 */

/*
 * Include the following lines in your makefile:
     *
     * unittest2: unittest2.c dominion.o rngs.o
     *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
     */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "gainCard"

int TOTAL_FAILURES = 0;

void assertEqual(int actual, int expected){
    if (expected != actual) {
        printf(" >>> TEST FAILED <<<\n");
        TOTAL_FAILURES++;
    }
}
int main() {
    int i;
    int returnVal = -999;
    int seed = 11;
    int newCards = 1;
    int toDiscard = 0, toDeck = 1, toHand = 2;
    int numPlayers = 2, thisPlayer = 0, otherPlayer = 1;
    int success = 0, failure = -1;
	struct gameState G, testG;
	int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
            
	printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	// ----------- TEST SET 1: Adding card to discard --------------
	printf("\nTEST SET 1: ADDING CARD TO DISCARD\n");

    // Initialize and copy game state
    initializeGame(numPlayers, kingdomCards, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

    // Check return 0
    returnVal = gainCard(adventurer, &testG, toDiscard, thisPlayer);
    printf("Return value = %d, Expected = %d\n", returnVal, success);
    assertEqual(returnVal, success);
    
    // Check that discard pile gained a card
    printf("Discarded card count (Player 1) = %d, Expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + newCards);
    assertEqual(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + newCards);
    
    // Check that hand did not change
    printf("Hand card count (Player 1) = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    
    // Check that deck did not change
    printf("Deck card count (Player 1) = %d, Expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    assertEqual(testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    
    // Check that only the adventure card pile changed
    for (i = 0; i <= treasure_map; i++) {
        if (i == adventurer) {
            printf("Card pile %d count = %d, Expected = %d\n", i, testG.supplyCount[i], G.supplyCount[i] - newCards);
            assertEqual(testG.supplyCount[i], G.supplyCount[i] - newCards);
        }
        else{
             printf("Card pile %d count = %d, Expected = %d\n", i, testG.supplyCount[i], G.supplyCount[i]);
            assertEqual(testG.supplyCount[i], G.supplyCount[i]);
        }
    }
    
    
    // Check that other player's state remained the same
    printf("Hand count (Player 2) = %d, Expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
    assertEqual(testG.handCount[otherPlayer], G.handCount[otherPlayer]);
    
    printf("Deck count (Player 2) = %d, Expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
    assertEqual(testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
    
    printf("Discard count (Player 2) = %d, Expected = %d\n", testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
    assertEqual(testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
    
    
    // ----------- TEST SET 2: Adding card to deck --------------
	printf("\nTEST SET 2: ADDING CARD TO DECK\n");

    // Initialize and copy game state
    initializeGame(numPlayers, kingdomCards, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

    // Check return 0
    returnVal = gainCard(adventurer, &testG, toDeck, thisPlayer);
    printf("Return value = %d, Expected = %d\n", returnVal, success);
    assertEqual(returnVal, success);
    
    // Check that discard pile did not change
    printf("Discarded card count (Player 1) = %d, Expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
    assertEqual(testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
    
    // Check that hand did not change
    printf("Hand card count (Player 1) = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    
    // Check that deck gained a card
    printf("Deck card count (Player 1) = %d, Expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] + newCards);
    assertEqual(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] + newCards);
    
    // Check that only the adventure card pile changed
    for (i = 0; i <= treasure_map; i++) {
        if (i == adventurer) {
            printf("Card pile %d count = %d, Expected = %d\n", i, testG.supplyCount[i], G.supplyCount[i] - newCards);
            assertEqual(testG.supplyCount[i], G.supplyCount[i] - newCards);
        }
        else{
             printf("Card pile %d count = %d, Expected = %d\n", i, testG.supplyCount[i], G.supplyCount[i]);
            assertEqual(testG.supplyCount[i], G.supplyCount[i]);
        }
    }
    
    
    // Check that other player's state remained the same
    printf("Hand count (Player 2) = %d, Expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
    assertEqual(testG.handCount[otherPlayer], G.handCount[otherPlayer]);
    
    printf("Deck count (Player 2) = %d, Expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
    assertEqual(testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
    
    printf("Discard count (Player 2) = %d, Expected = %d\n", testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
    assertEqual(testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
    
    // ----------- TEST SET 3: Adding card to hand --------------
	printf("\nTEST SET 3: ADDING CARD TO HAND\n");

    // Initialize and copy game state
    initializeGame(numPlayers, kingdomCards, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

    // Check return 0
    returnVal = gainCard(adventurer, &testG, toHand, thisPlayer);
    printf("Return value = %d, Expected = %d\n", returnVal, success);
    assertEqual(returnVal, success);
    
    // Check that discard pile did not change
    printf("Discarded card count (Player 1) = %d, Expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
    assertEqual(testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
    
    // Check that hand gained a card
    printf("Hand card count (Player 1) = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);
    assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);
    
    // Check that deck gained a card
    printf("Deck card count (Player 1) = %d, Expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    assertEqual(testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    
    // Check that only the adventure card pile changed
    for (i = 0; i <= treasure_map; i++) {
        if (i == adventurer) {
            printf("Card pile %d count = %d, Expected = %d\n", i, testG.supplyCount[i], G.supplyCount[i] - newCards);
            assertEqual(testG.supplyCount[i], G.supplyCount[i] - newCards);
        }
        else{
             printf("Card pile %d count = %d, Expected = %d\n", i, testG.supplyCount[i], G.supplyCount[i]);
            assertEqual(testG.supplyCount[i], G.supplyCount[i]);
        }
    }
    
    
    // Check that other player's state remained the same
    printf("Hand count (Player 2) = %d, Expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
    assertEqual(testG.handCount[otherPlayer], G.handCount[otherPlayer]);
    
    printf("Deck count (Player 2) = %d, Expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
    assertEqual(testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
    
    printf("Discard count (Player 2) = %d, Expected = %d\n", testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
    assertEqual(testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
    
    
    // ----------- TEST SET 4: Empty pile --------------
	printf("\nTEST SET 4: ADDING CARD FROM EMPTY PILE\n");

    // Initialize and copy game state
    initializeGame(numPlayers, kingdomCards, seed, &G);
    G.supplyCount[adventurer] = 0;
	memcpy(&testG, &G, sizeof(struct gameState));

    // Check return -1
    returnVal = gainCard(adventurer, &testG, toHand, thisPlayer);
    printf("Return value = %d, Expected = %d\n", returnVal, failure);
    assertEqual(returnVal, failure);
    
    // Check that hand did not gain a card
    printf("Hand card count (Player 1) = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    
    
    // ----------- TEST SET 4: Card not in game --------------
	printf("\nTEST SET 4: ADDING CARD NOT USED IN GAME\n");

    // Initialize and copy game state
    initializeGame(numPlayers, kingdomCards, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

    // Check return -1
    returnVal = gainCard(treasure_map, &testG, toHand, thisPlayer);
    printf("Return value = %d, Expected = %d\n", returnVal, failure);
    assertEqual(returnVal, failure);
    
    // Check that hand did not gain a card
    printf("Hand card count (Player 1) = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    

    
    if (TOTAL_FAILURES) {
        printf("\n >>>>> TESTING FAILED: %s testing complete with %d failures. <<<<<\n\n", TESTFUNCTION, TOTAL_FAILURES);
    }
    else {
        printf("\n >>>>> SUCCESS: %s testing complete. <<<<<\n\n", TESTFUNCTION);
    }

	return 0;
}


