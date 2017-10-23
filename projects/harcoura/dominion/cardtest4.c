/*
 * cardtest4.c
 */

/*
 * Include the following lines in your makefile:
     *
     * cardtest4: cardtest4.c dominion.o rngs.o
     *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
     */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "baron"

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
    int buysIncrease = 1;
    int coinIncreaseC1 = 4, coinIncreaseC2 = 0;
    int newCardsC1 = 0, newCardsC2 = 1;
    int playedCards = 1;
    int discardedC1 = 1, discardedC2 = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer = 1;
	struct gameState G, testG;
	int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
            
	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST SET 1: Buys +1 and deck doesn't change --------------
	printf("\nTEST SET 1: BUYS +1 and DECK DOESN'T CHANGE\n");
    
    // Initialize a game
	initializeGame(numPlayers, kingdomCards, seed, &G);
    
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
    printf("Return value = %d, Expected = %d\n", returnVal, 0);
    assertEqual(returnVal, 0);
    
    // Check that 2 cards were discarded
    printf("Discarded card count (Player 1) = %d, Expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + playedCards + discardedC1);
    assertEqual(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + playedCards + discardedC1);
    
    // Check that deck is unaltered
    printf("Deck count (Player 1) = %d, Expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    assertEqual(testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    
    // Check that buys increased by one
    printf("Buys (Player 1) = %d, Expected = %d\n", testG.numBuys, G.numBuys + buysIncrease);
    assertEqual(testG.numBuys, G.numBuys + buysIncrease);
    
    // ----------- TEST SET 2: Discarding Estate +4  --------------
	printf("\nTEST SET 2: DISCARDING ESTATE +4\n");
    
    // Check that hand count descreased by two
    printf("Hand count (Player 1) = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discardedC1 + newCardsC1 - playedCards);
    assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer] - discardedC1 + newCardsC1 - playedCards);
    
    // Check that an estate was discarded
    printf("Spot in hand where estate was (Player 1) = %d, Expected = %d\n", testG.hand[thisPlayer][1], copper);
    assertEqual(testG.hand[thisPlayer][1], copper);
    
    // Check that estate pile is unaltered
    printf("Estate pile count (Player 1) = %d, Expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
    assertEqual(testG.supplyCount[estate], G.supplyCount[estate]);
      
    // Check that coins increased by four
	printf("Coins (Player 1) = %d, Expected = %d\n", testG.coins, G.coins + coinIncreaseC1);
	assertEqual(testG.coins, G.coins + coinIncreaseC1);
    
    // ----------- TEST SET 3: Not discarding Estate +Estate --------------
	printf("\nTEST SET 3: NOT DISCARDING ESTATE +ESTATE\n");  
    
     // Initialize a game
	initializeGame(numPlayers, kingdomCards, seed, &G);
    
    G.hand[thisPlayer][0] = baron;
    G.hand[thisPlayer][1] = estate;
    G.hand[thisPlayer][2] = copper;
    G.hand[thisPlayer][3] = copper;
    G.hand[thisPlayer][4] = copper;
    
    choice1 = 0;
   
    // Copy the game state to a test game
	memcpy(&testG, &G, sizeof(struct gameState));
    
    // Check return value
	returnVal = cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);
    printf("Return value = %d, Expected = %d\n", returnVal, 0);
    assertEqual(returnVal, 0);
   
    // Check that deck is unaltered
    printf("Deck count (Player 1) = %d, Expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    assertEqual(testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    
    // Check that buys increased by one
    printf("Buys (Player 1) = %d, Expected = %d\n", testG.numBuys, G.numBuys + buysIncrease);
    assertEqual(testG.numBuys, G.numBuys + buysIncrease);
   
    // Check that hand count remained the same
    printf("Hand count (Player 1) = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discardedC2 + newCardsC2 - playedCards);
    assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer] - discardedC2 + newCardsC2 - playedCards);
    
    // Check that 1 card is discarded
    printf("Discard count (Player 1) = %d, Expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + playedCards);
    assertEqual(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + playedCards);
    
    // Check that estate pile is -1
    printf("Estate pile count (Player 1) = %d, Expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate] - newCardsC2);
    assertEqual(testG.supplyCount[estate], G.supplyCount[estate] - newCardsC2);
       
    // Check that coins did not increase by four
	printf("Coins (Player 1) = %d, Expected = %d\n", testG.coins, G.coins + coinIncreaseC2);
	assertEqual(testG.coins, G.coins + coinIncreaseC2);
   
    // Check that an estate was not discarded
    printf("Spot in hand where estate was (Player 1) = %d, Expected = %d\n", testG.hand[thisPlayer][1], G.hand[thisPlayer][1]);
    assertEqual(testG.hand[thisPlayer][1], G.hand[thisPlayer][1]);
   
    
    // ----------- TEST SET 4: Cannot discard estate if not in hand --------------
	printf("\nTEST SET 4: CANNOT DISCARD ESTATE IF NOT IN HAND\n");
    
    // Initialize a game
	initializeGame(numPlayers, kingdomCards, seed, &G); 
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
    printf("Deck count (Player 1) = %d, Expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    assertEqual(testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    
    // Check that buys increased by one
    printf("Buys (Player 1) = %d, Expected = %d\n", testG.numBuys, G.numBuys + buysIncrease);
    assertEqual(testG.numBuys, G.numBuys + buysIncrease);
   
    // Check that hand count remained the same
    printf("Hand count (Player 1) = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discardedC2 + newCardsC2 - playedCards);
    assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer] - discardedC2 + newCardsC2 - playedCards);
    
    
    // Check that estate pile is -1
    printf("Estate pile count (Player 1) = %d, Expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate] - newCardsC2);
    assertEqual(testG.supplyCount[estate], G.supplyCount[estate] - newCardsC2);
        
    // Check that coins did not increase by four
	printf("Coins (Player 1) = %d, Expected = %d\n", testG.coins, G.coins + coinIncreaseC2);
	assertEqual(testG.coins, G.coins + coinIncreaseC2);
   

    // ----------- TEST SET 5: Cannot gain estate if pile is empty --------------
	printf("\nTEST SET 5: CANNOT GAIN ESTATE IF PILE IS EMPTY \n");

    // Initialize a game
	initializeGame(numPlayers, kingdomCards, seed, &G); 
    G.supplyCount[estate] = 0;
	memcpy(&testG, &G, sizeof(struct gameState));
    
    choice1 = 0;
    
    cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);
   
     // Check that deck is -1
    printf("Deck count (Player 1) = %d, Expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - playedCards);
    assertEqual(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - playedCards);
    
    // Check that estate pile is unaltered
    printf("Estate pile count (Player 1) = %d, Expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
    assertEqual(testG.supplyCount[estate], G.supplyCount[estate]);


    // ----------- TEST SET 6: No state changes for other player --------------
	printf("\nTEST SET 6: NO STATE CHANGES FOR OTHER PLAYER\n");

	printf("Hand count (Player 2) = %d, Expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
    assertEqual(testG.handCount[otherPlayer], G.handCount[otherPlayer]);
    
    printf("Deck count (Player 2) = %d, Expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
    assertEqual(testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
    
    printf("Discard count (Player 2) = %d, Expected = %d\n", testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
    assertEqual(testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
    
    
	// ----------- TEST SET 7: No state changes in incorrect card piles --------------
	printf("\nTEST SET 5: NO STATE CHANGES IN INCORRECT CARD PILES\n");
    
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


