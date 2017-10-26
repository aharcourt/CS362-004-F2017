/*
 * randomtestadventurer.c
 */

/*
 * Include the following lines in your makefile:
     *
     * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
     *      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
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
#define TESTCARD "adventurer"

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

// Returns true if card input is Copper, Silver, or Gold. Returns false otherwise
bool isTreasure(int card){
    return (card == copper || card == silver || card == gold);
}

int main() {
    int i, j;
    int totalFailures = 0;
    int newCards = 2, discarded = 1;
    int deckSize = -1;
    int randCard;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int numPlayers = 2;
    int thisPlayer = 0;
    int gameSeed;
    int treasureCards = 0;
    int otherPlayer = 1;
	struct gameState G, testG;
	int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
            
    // Seed random number generator with static value (for replicability)       
    srand(10);

    printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
    
    for (i = 0; i < TEST_CASES; i++) {
        FAILURES = 0;
        treasureCards = 0;
        
        // Get random game seed
        gameSeed = generateRand(0, INT_MAX);
 
        // Initialize a game
        initializeGame(numPlayers, kingdomCards, gameSeed, &G);
        
        // Generate random deck size
        deckSize = generateRand(10, MAX_DECK);
       
        // Fill hand with random cards
        for (j = 0; j < deckSize; j++) {
            randCard = generateRand(0, treasure_map);
            G.deck[thisPlayer][j] = randCard;
            
            // Count number of treasure cards added to deck
            if (isTreasure(randCard)){
                treasureCards++;
            }
        }
        
        // Set deck size and place adventurer card in hand
        G.deckCount[thisPlayer] = deckSize;
        G.hand[thisPlayer][0] = adventurer;
        
        // Copy game to test state
        memcpy(&testG, &G, sizeof(struct gameState));
        
        // Play card
        cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
        
        // Check that the player 1 hand count is correct, depending on how many treasure cards are available to draw from deck
        if (treasureCards >= 2) {
            assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded, i + 1, "Player 1 hand count is incorrect.");
        }
        else if (treasureCards >= 1) {
            assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer] + (newCards - 1) - discarded, i + 1, "Player 1 hand count is incorrect.");
        }
        else{
            assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded, i + 1, "Player 1 hand count is incorrect.");
        }
        
        // Assert that last two drawn cards are treasure cards (if they were available to draw)
        if (treasureCards >= 1) {
            assertEqual(isTreasure(testG.hand[thisPlayer][testG.handCount[thisPlayer]-1]), true, i + 1, "Last card drawn was not a treasure card.");
        }
        if (treasureCards >= 2) {
            assertEqual(isTreasure(testG.hand[thisPlayer][testG.handCount[thisPlayer]-2]), true, i + 1, "Second to last card drawn was not a treasure card.");
        }
           
        // Assert that no treasure cards were discarded
        for (j = 0; j < testG.discardCount[thisPlayer]; j++) {
            assertEqual(isTreasure(testG.discard[thisPlayer][j]), false, i + 1, "A treasure card was discarded instead of kept in hand.");
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


