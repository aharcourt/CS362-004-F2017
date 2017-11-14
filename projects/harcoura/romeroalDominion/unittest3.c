/*
 * unittest3.c
 */

/*
 * Include the following lines in your makefile:
     *
     * unittest3: unittest3.c dominion.o rngs.o
     *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
     */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "getCost"

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
    int numPlayers = 2;
    int failure = -1;
	struct gameState testG;
	int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
            
    int expectedCost[treasure_map + 1] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};
            
	printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	// ----------- TEST SET 1: Test all card costs --------------
	printf("\nTEST SET 1: TEST ALL CARD COSTS\n");

    // Initialize game state
    initializeGame(numPlayers, kingdomCards, seed, &testG);

    for (i = 0; i <= treasure_map; i++) {
        // Check cost value
        returnVal = getCost(i);
        printf("Card %d cost = %d, Expected = %d\n", i, returnVal, expectedCost[i]);
        assertEqual(returnVal, expectedCost[i]);
    }
    
    
	// ----------- TEST SET 2: Test invalid values --------------
	printf("\nTEST SET 2: TEST INVALID VALUES\n");
    
    // Check below range
    returnVal = getCost(-1);
    printf("Return value of '-1' = %d, Expected = %d\n", returnVal, failure);
    assertEqual(returnVal, failure);
    
    // Check above range
    returnVal = getCost(treasure_map + 1);
    printf("Return value of '27' = %d, Expected = %d\n", returnVal, failure);
    assertEqual(returnVal, failure);
    
    if (TOTAL_FAILURES) {
        printf("\n >>>>> TESTING FAILED: %s testing complete with %d failures. <<<<<\n\n", TESTFUNCTION, TOTAL_FAILURES);
    }
    else {
        printf("\n >>>>> SUCCESS: %s testing complete. <<<<<\n\n", TESTFUNCTION);
    }

	return 0;
}


