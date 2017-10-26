/*
 * randomtestcard2.c
 */

/*
 * Include the following lines in your makefile:
     *
     * randomtestcard2: rrandomtestcard2.c dominion.o rngs.o
     *      gcc -o randomtestcard2 -g  randomtestcard2 dominion.o rngs.o $(CFLAGS)
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

#define TESTCARD "baron"

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
    int buysIncrease = 1;
    int playedCards = 1;
    int coinIncreaseC1 = 4, coinIncreaseC2 = 0;
    int newCardsC1 = 0, newCardsC2 = 1;
    int discardedC1 = 1, discardedC2 = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int numPlayers = 2, thisPlayer = 0, otherPlayer = 1;
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
        
        G.hand[thisPlayer][0] = baron;
        G.hand[thisPlayer][1] = estate;
        G.hand[thisPlayer][2] = copper;
        G.hand[thisPlayer][3] = copper;
        G.hand[thisPlayer][4] = copper;
        
        // Copy the game state to a test game
        memcpy(&testG, &G, sizeof(struct gameState));
        
        choice1 = 1;
        
        // Check return value
        returnVal = cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);
        assertEqual(returnVal, 0, i + 1, "Return value was not 0 for valid function call.");
  
        // Check that 2 cards were discarded
        assertEqual(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + playedCards + discardedC1, i + 1, "Player 1 discard count is incorrect.");
        
        // Check that deck is unaltered
        assertEqual(testG.deckCount[thisPlayer], G.deckCount[thisPlayer], i + 1, "Player 1 deck count is incorrect.");
        
        // Check that buys increased by one
        assertEqual(testG.numBuys, G.numBuys + buysIncrease, i + 1, "Player 1 buys did not increase by 1.");
       
        // Check that hand count descreased by two
        assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer] - discardedC1 + newCardsC1 - playedCards, i + 1, "Player 1 hand count is incorrect.");
        
        // Check that an estate was discarded
        assertEqual(testG.hand[thisPlayer][1], copper, i + 1, "Estate was not discarded from hand.");
        
        // Check that estate pile is unaltered
        assertEqual(testG.supplyCount[estate], G.supplyCount[estate], i + 1, "Estate card pile was altered inappropriately.");
          
        // Check that coins increased by four
        assertEqual(testG.coins, G.coins + coinIncreaseC1, i + 1, "Coins did not increase by four.");
        
        // TEST FOR NOT DISCARDING AN ESTATE CHOICE
        // Initialize a game
        initializeGame(numPlayers, kingdomCards, gameSeed, &G);
        
        G.hand[thisPlayer][0] = baron;
        G.hand[thisPlayer][1] = estate;
        G.hand[thisPlayer][2] = copper;
        G.hand[thisPlayer][3] = copper;
        G.hand[thisPlayer][4] = copper;
        
        choice1 = 0;
       
        // Copy the game state to a test game
        memcpy(&testG, &G, sizeof(struct gameState));
        
        // Check return value
        assertEqual(returnVal, 0, i + 1, "Return value was not 0 for valid function call.");
       
        // Check that deck is unaltered
        assertEqual(testG.deckCount[thisPlayer], G.deckCount[thisPlayer], i + 1, "Player 1 deck count is incorrect.");
        
        // Check that buys increased by one
        assertEqual(testG.numBuys, G.numBuys + buysIncrease, i + 1, "Player 1 buys did not increase by 1.");
       
        // Check that hand count remained the same
        assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer] - discardedC2 + newCardsC2 - playedCards, i + 1, "Player 1 hand count is incorrect.");
        
        // Check that 1 card is discarded
        assertEqual(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + playedCards, i + 1, "Player 1 discard count is incorrect.");
        
        // Check that estate pile is -1
        assertEqual(testG.supplyCount[estate], G.supplyCount[estate] - newCardsC2, i + 1, "Estate card pile did not decrease by 1.");
           
        // Check that coins did not increase by four
        assertEqual(testG.coins, G.coins + coinIncreaseC2, i + 1, "Player 1 coin count is incorrect.");
       
        // Check that an estate was not discarded
        assertEqual(testG.hand[thisPlayer][1], G.hand[thisPlayer][1], i + 1, "Estate was discarded where inappropriate.");
       
        
        // TEST THAT ESTATE CAN NOT BE DISCARDED WHEN NOT IN HAND
        
        // Initialize a game
        initializeGame(numPlayers, kingdomCards, gameSeed, &G); 
        G.hand[thisPlayer][0] = copper;
        G.hand[thisPlayer][1] = copper;
        G.hand[thisPlayer][2] = copper;
        G.hand[thisPlayer][3] = copper;
        G.hand[thisPlayer][4] = copper;
     
        // Copy the game state to a test game
        memcpy(&testG, &G, sizeof(struct gameState));
        
        choice1 = 1;
        
        cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);
          
        // Check that deck is unaltered
        assertEqual(testG.deckCount[thisPlayer], G.deckCount[thisPlayer], i + 1, "Player 1 deck count is incorrect.");
        
        // Check that buys increased by one
        assertEqual(testG.numBuys, G.numBuys + buysIncrease, i + 1, "Player 1 buys did not increase by 1.");
       
        // Check that hand count remained the same
        assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer] - discardedC2 + newCardsC2 - playedCards, i + 1, "Player 1 hand count is incorrect."); 
        
        // Check that estate pile is -1
        assertEqual(testG.supplyCount[estate], G.supplyCount[estate] - newCardsC2, i + 1, "Estate card pile did not decrease by 1.");
            
        // Check that coins did not increase by four
        assertEqual(testG.coins, G.coins + coinIncreaseC2, i + 1, "Coins did not increase by four.");
       

        // TEST THAT YOU CAN'T GAIN AN ESTATE IF THE PILE IS EMPTY

        // Initialize a game
        initializeGame(numPlayers, kingdomCards, gameSeed, &G); 
        G.supplyCount[estate] = 0;
        memcpy(&testG, &G, sizeof(struct gameState));
        
        choice1 = 0;
        
        cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);
       
         // Check that deck is -1
        assertEqual(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - playedCards, i + 1, "Player 1 deck count is incorrect.");
        
        // Check that estate pile is unaltered
        assertEqual(testG.supplyCount[estate], G.supplyCount[estate], i + 1, "Estate card pile was altered inappropriately.");
      
        // Assert that no state changes occurred for other players
        assertEqual(testG.handCount[otherPlayer], G.handCount[otherPlayer], i + 1, "Player 2 hand count is incorrect.");
        assertEqual(testG.deckCount[otherPlayer], G.deckCount[otherPlayer], i + 1, "Player 2 deck count is incorrect.");
        assertEqual(testG.discardCount[otherPlayer], G.discardCount[otherPlayer], i + 1, "Player 2 discard count is incorrect.");
    
        // Test that all card piles remained the same (except for estate)
        for (j = 0; j <= treasure_map; j++) { 
            if (j != estate) {
                assertEqual(testG.supplyCount[j], G.supplyCount[j], i + 1, "A card pile was altered.");    
            }
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


