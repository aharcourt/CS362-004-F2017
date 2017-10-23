/*
 * unittest1.c
 */

/*
 * Include the following lines in your makefile:
     *
     * unittest1: unittest1.c dominion.o rngs.o
     *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
     */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "isGameOver"

int TOTAL_FAILURES = 0;

void assertEqual(int actual, int expected){
    if (expected != actual) {
        printf(" >>> TEST FAILED <<<\n");
        TOTAL_FAILURES++;
    }
}
int main() {
    int i, j;
    int returnVal = -1, expectedVal = -1;
    int seed = 11;
    int numPlayers = 2;
	struct gameState testG;
	int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
            
	printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	// ----------- TEST SET 1: 3 empty kingdom cards --------------
	printf("\nTEST SET 1: 3 EMPTY KINGDOM CARD STACKS\n");

    // Set all card stacks to 0
    for (i = adventurer; i <= treasure_map - 2; i++) {  
        // Initialize a game
        initializeGame(numPlayers, kingdomCards, seed, &testG);
        
        for (j = 0; j <= treasure_map; j++) { 
            testG.supplyCount[i] = 10;
        }
        
        testG.supplyCount[i] = 0;
        testG.supplyCount[i + 1] = 0;
        testG.supplyCount[i + 2] = 0;
        
        
        // Check if all kingdom card stacks trigger game end
        returnVal = isGameOver(&testG);
        printf("Checking kingdom combo %d. Is game over = %d, Expected = %d\n", i + 1 - adventurer, returnVal, 1);
        assertEqual(returnVal, 1);
    }  

    // Initialize a game
    initializeGame(numPlayers, kingdomCards, seed, &testG);
    
    for (j = 0; j <= treasure_map; j++) { 
        testG.supplyCount[i] = 10;
    }
    
    testG.supplyCount[10] = 0;
    testG.supplyCount[11] = 0;

    // Check if game is over
    returnVal = isGameOver(&testG);
    printf("Checking two empty kingdom stacks. Is game over = %d, Expected = %d\n", returnVal, 0);
    assertEqual(returnVal, 0);
 
    
    // ----------- TEST SET 2: Empty province stack --------------
	printf("\nTEST SET 2: EMPTY PROVINCE STACK\n");
    
    // Set all card stacks to 0
    for (i = 0; i <= treasure_map; i++) {  
        // Initialize a game
        initializeGame(numPlayers, kingdomCards, seed, &testG);
        
        for (j = 0; j <= treasure_map; j++) { 
            testG.supplyCount[i] = 10;
        }
        
        testG.supplyCount[i] = 0;
       
        // Check that only empty province stack triggers game over.
        if (i == province) {
            expectedVal = 1;
        }
        else {
            expectedVal = 0;
        }
        returnVal = isGameOver(&testG);
        printf("Checking empty stack %d. Is game over = %d, Expected = %d\n", i + 1, returnVal, expectedVal);
        assertEqual(returnVal, expectedVal);
    }  
    
    
    if (TOTAL_FAILURES) {
        printf("\n >>>>> TESTING FAILED: %s testing complete with %d failures. <<<<<\n\n", TESTFUNCTION, TOTAL_FAILURES);
    }
    else {
        printf("\n >>>>> SUCCESS: %s testing complete. <<<<<\n\n", TESTFUNCTION);
    }

	return 0;
}


