/*
 * unittest4.c
 */

/*
 * Include the following lines in your makefile:
     *
     * unittest4: unittest4.c dominion.o rngs.o
     *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
     */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "fullDeckCount"

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
    int deckSize = 10;
    int numPlayers = 2, thisPlayer = 0, otherPlayer = 1;
	struct gameState testG;
	int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
            
	printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	// ----------- TEST SET 1: Count full deck --------------
	printf("\nTEST SET 1: COUNT FULL DECK - BASE\n");

    // Initialize and copy game state
    initializeGame(numPlayers, kingdomCards, seed, &testG);

    // Check deck size Player 1
    returnVal = fullDeckCount(thisPlayer, 0, &testG);
    printf("Full deck count (Player 1) = %d, Expected = %d\n", returnVal, deckSize);
    assertEqual(returnVal, deckSize);
    
    // Check deck size Player 2
    returnVal = fullDeckCount(otherPlayer, 0, &testG);
    printf("Full deck count (Player 2) = %d, Expected = %d\n", returnVal, deckSize);
    assertEqual(returnVal, deckSize);
    
    // ----------- TEST SET 2: Count full deck after manipulation --------------
	printf("\nTEST SET 2: COUNT FULL DECK AFTER MANIPULATION\n");

    
    // Manipulate Player 1 values
    testG.deckCount[thisPlayer] = 7;
    for (i = 0; i < 7; i++) {
        testG.deck[thisPlayer][i] = (rand() % (treasure_map - curse)) + curse;
    }
    
    testG.discardCount[thisPlayer] = 12;
    for (i = 0; i < 12; i++) {
        testG.discard[thisPlayer][i] = (rand() % (treasure_map - curse)) + curse;
    }
    
    testG.handCount[thisPlayer] = 2;
    for (i = 0; i < 2; i++) {
        testG.hand[thisPlayer][i] = (rand() % (treasure_map - curse)) + curse;
    }
    
    deckSize = 21;
    
     // Check deck size Player 1
    returnVal = fullDeckCount(thisPlayer, 0, &testG);
    printf("Full deck count (Player 1) = %d, Expected = %d\n", returnVal, deckSize);
    assertEqual(returnVal, deckSize);
    
    deckSize = 10;
    
    // Check deck size Player 2
    returnVal = fullDeckCount(otherPlayer, 0, &testG);
    printf("Full deck count (Player 2) = %d, Expected = %d\n", returnVal, deckSize);
    assertEqual(returnVal, deckSize);

    
    // ----------- TEST SET 3: Count full deck of size zero --------------
	printf("\nTEST SET 3: COUNT FULL DECK OF SIZE ZERO\n");

    // Manipulate Player 1 values
    testG.deckCount[thisPlayer] = 0;
    testG.discardCount[thisPlayer] = 0;
    testG.handCount[thisPlayer] = 0;
    
    deckSize = 0;
    
     // Check deck size Player 1
    returnVal = fullDeckCount(thisPlayer, 0, &testG);
    printf("Full deck count (Player 1) = %d, Expected = %d\n", returnVal, deckSize);
    assertEqual(returnVal, deckSize);
    
    deckSize = 10;
    
    // Check deck size Player 2
    returnVal = fullDeckCount(otherPlayer, 0, &testG);
    printf("Full deck count (Player 2) = %d, Expected = %d\n", returnVal, deckSize);
    assertEqual(returnVal, deckSize);
    
    // ----------- TEST SET 3: Count full deck of max size --------------
	printf("\nTEST SET 3: COUNT FULL DECK OF MAX SIZE\n");

    // Manipulate Player 1 values
    testG.deckCount[thisPlayer] = 250;
    for (i = 0; i < 250; i++) {
        testG.deck[thisPlayer][i] = (rand() % (treasure_map - curse)) + curse;
    }
    
    testG.discardCount[thisPlayer] = 100;
    for (i = 0; i < 100; i++) {
        testG.discard[thisPlayer][i] = (rand() % (treasure_map - curse)) + curse;
    }
    
    testG.handCount[thisPlayer] = 150;
    for (i = 0; i < 150; i++) {
        testG.hand[thisPlayer][i] = (rand() % (treasure_map - curse)) + curse;
    }
    
    deckSize = 500;
    
     // Check deck size Player 1
    returnVal = fullDeckCount(thisPlayer, 0, &testG);
    printf("Full deck count (Player 1) = %d, Expected = %d\n", returnVal, deckSize);
    assertEqual(returnVal, deckSize);
    
    deckSize = 10;
    
    // Check deck size Player 2
    returnVal = fullDeckCount(otherPlayer, 0, &testG);
    printf("Full deck count (Player 2) = %d, Expected = %d\n", returnVal, deckSize);
    assertEqual(returnVal, deckSize);
    
    if (TOTAL_FAILURES) {
        printf("\n >>>>> TESTING FAILED: %s testing complete with %d failures. <<<<<\n\n", TESTFUNCTION, TOTAL_FAILURES);
    }
    else {
        printf("\n >>>>> SUCCESS: %s testing complete. <<<<<\n\n", TESTFUNCTION);
    }

	return 0;
}


