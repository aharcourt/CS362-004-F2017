/*
 * randomtestcard1.c
 */

/*
 * Include the following lines in your makefile:
     *
     * randomtestcard1: rrandomtestcard1.c dominion.o rngs.o
     *      gcc -o randomtestcard1 -g  randomtestcard1 dominion.o rngs.o $(CFLAGS)
     */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>

#define TESTCARD "smithy"

// Number of failures per test case
int FAILURES = 0;
// Number of test cases to run
int TEST_CASES = 1000;

// Checks if two values are equal. If not, failure message is dislayed and failures are incremented
void assertEqual(int actual, int expected, int testCase, const char *message){
    if (expected != actual) {
        printf(" >> Test Failed: Test Case - %d, Details - %s << \n", testCase, message);
        FAILURES++;
    }
}

// Generates a ranom int between two input values
int generateRand(int min, int max){
    return rand() % (max + 1 - min) + min;
}

int main() {
    int i, j;
    int totalFailures = 0;
    int newCards = 3, discarded = 1;
    int deckSize, discardSize;
    int randCard;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int numPlayers = 2, thisPlayer = 0, otherPlayer = 1;;
    int gameSeed;
    int returnVal = -999;
	struct gameState G, testG;
	int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
            
    // Seed random number generator with static value (for replicability)       
    srand(10);

    printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
    
    for (i = 0; i < TEST_CASES; i++) {
        FAILURES = 0;
        
        // Get random game seed
        gameSeed = generateRand(0, INT_MAX);
 
        // Initialize a game
        initializeGame(numPlayers, kingdomCards, gameSeed, &G);
        
        // Generate random deck size
        deckSize = generateRand(1, MAX_DECK / 2);
        // Generate random discard size
        discardSize = generateRand(1, MAX_DECK / 2);
        
        
        // Fill discard with cards (for reshuffle if necessary)
        for (j = 0; j < discardSize; j++) {
            randCard = generateRand(0, treasure_map);
            G.discard[thisPlayer][j] = randCard;
        }
        
        // Set discard size
        G.discardCount[thisPlayer] = discardSize;
        
        // Fill hand with random cards
        for (j = 0; j < deckSize; j++) {
            randCard = generateRand(0, treasure_map);
            G.deck[thisPlayer][j] = randCard;
        }
        
        // Set deck size and place smithy card in hand
        G.deckCount[thisPlayer] = deckSize;
        G.hand[thisPlayer][0] = smithy;
        
        // Copy game to test state
        memcpy(&testG, &G, sizeof(struct gameState));
        
        // Play card
        returnVal = cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
        assertEqual(returnVal, 0, i + 1, "Return value of cardEffect was not 0.");
        
        // Check that the player 1 hand count is correct, depending on how many cards were available to draw.
        if (deckSize + discardSize >= 3) {
            assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded, i + 1, "Player 1 hand count is incorrect.");
        }
        else if (deckSize + discardSize == 2) {
            assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer] + (newCards - 1) - discarded, i + 1, "Player 1 hand count is incorrect.");
        }
       
        
        // Assert that deck is reduced by 3 cards
        if (deckSize >= 3) {
            assertEqual(testG.deckCount[thisPlayer], deckSize - newCards, i + 1, "Player 1 deck count is incorrect.");
        }
        // Chec deck size after reshuffle
        else if (deckSize + discardSize >= 3) {
            assertEqual(testG.deckCount[thisPlayer], deckSize + discardSize - newCards, i + 1, "Player 1 deck count is incorrect after shuffle.");
        }
        else if (deckSize + discardSize < 3) {
            assertEqual(testG.deckCount[thisPlayer], 0, i + 1, "Player 1 deck count is incorrect.");
            assertEqual(testG.discardCount[thisPlayer], discarded, i + 1, "Player 1 discard count is incorrect.");
        }      
      
        // Assert that no state changes occurred for other players
        assertEqual(testG.handCount[otherPlayer], G.handCount[otherPlayer], i + 1, "Player 2 hand count is incorrect.");
        assertEqual(testG.deckCount[otherPlayer], G.deckCount[otherPlayer], i + 1, "Player 2 deck count is incorrect.");
        assertEqual(testG.discardCount[otherPlayer], G.discardCount[otherPlayer], i + 1, "Player 2 discard count is incorrect.");
    
        // Test that all card piles remained the same.
        for (j = 0; j <= treasure_map; j++) {  
            assertEqual(testG.supplyCount[j], G.supplyCount[j], i + 1, "A card pile was altered.");      
        }  
        
        // If this test had any failures, add it to the total failure log
        if (FAILURES) {
            totalFailures++;
        }    
    }

    // Print final random test results
    if (totalFailures) {
        printf("\n >>>>> TESTING FAILED: %s testing complete with %d failures out of %d test cases. <<<<<\n\n", TESTCARD, totalFailures, TEST_CASES);
    }
    else {
        printf("\n >>>>> SUCCESS: %s testing complete. <<<<<\n\n", TESTCARD);
    }

	return 0;
}


