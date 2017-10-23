/*
 * cardtest3.c
 */

/*
 * Include the following lines in your makefile:
     *
     * cardtest3: cardtest3.c dominion.o rngs.o
     *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
     */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "feast"

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
    int playedCards = 0;
    int newCards = 1;
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

	// ----------- TEST SET 1: Card is trashed and new card is gained --------------
	printf("\nTEST SET 1: CARD IS TRASHED AND NEW CARD IS GAINED\n");
    
    choice1 = cutpurse;
    
	returnVal = cardEffect(feast, choice1, choice2, choice3, &testG, handpos, &bonus);
    printf("Return value = %d, Expected = %d\n", returnVal, 0);
    assertEqual(returnVal, 0);
    
    printf("Played card count (Player 1) = %d, Expected = %d\n", testG.playedCardCount, playedCards);
    assertEqual(testG.playedCardCount, playedCards);

	printf("Hand count (Player 1) = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    assertEqual(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    
    printf("Deck count (Player 1) = %d, Expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    assertEqual(testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    
    updateCoins(thisPlayer, &testG, bonus);
    
	printf("Coins (Player 1) = %d, Expected = %d\n", testG.coins, G.coins);
	assertEqual(testG.coins, G.coins);
    
    // ----------- TEST SET 2: Only one card pile state is altered --------------
	printf("\nTEST SET 2: ONLY ONE CARD PILE STATE IS ALTERED\n");
    
    // Test that only the cutpurse card pile changed. 
    for (i = 0; i < treasure_map; i++) {  
        if (i == cutpurse) {
            G.supplyCount[i] -= 1;
        }
        printf("Card pile %d = %d, Expected = %d\n", i + 1, testG.supplyCount[i], G.supplyCount[i]);
        assertEqual(testG.supplyCount[i], G.supplyCount[i]);      
    } 
   
    
    // ----------- TEST SET 3: Cannot buy card that is not available --------------
	printf("\nTEST SET 3: CANNOT BUY CARD THAT IS NOT AVAILABLE\n");
  	printf("\nSEVERAL TESTS COMMENTED OUT DUE TO INFINITE LOOPS\n");  
    
    /* // Initialize a game
	initializeGame(numPlayers, kingdomCards, seed, &G);
   
    // Set player decks 
    G.supplyCount[cutpurse] = 0;
 
    // Copy the game state to a test game
	memcpy(&testG, &G, sizeof(struct gameState));
    
    choice1 = cutpurse;
    
    returnVal = cardEffect(feast, choice1, choice2, choice3, &testG, handpos, &bonus);
    printf("Return value = %d, Expected = %d\n", returnVal, -1);
    assertEqual(returnVal, -1);
    
    printf("Cutpurse supply count = %d, Expected = %d\n", testG.supplyCount[cutpurse], G.supplyCount[cutpurse]);
    assertEqual(testG.supplyCount[cutpurse], G.supplyCount[cutpurse]);
    
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        printf("Card in hand %d (Player 1) = %d, Expected = %d\n", i + 1, testG.hand[thisPlayer][i], G.hand[thisPlayer][i]);
        assertEqual(testG.hand[thisPlayer][i], G.hand[thisPlayer][i]);
    }
    
    // ----------- TEST SET 4: Able to buy a valid card after a rejected attempt --------------
	printf("\nTEST SET 4: ABLE TO BUY A VALID CARD AFTER A REJECTED ATTEMPT \n");

    choice1 = village;
    
    returnVal = cardEffect(feast, choice1, choice2, choice3, &testG, handpos, &bonus);
    printf("Return value = %d, Expected = %d\n", returnVal, 0);
    assertEqual(returnVal, 0);
    
	printf("Village supply count = %d, Expected = %d\n", testG.supplyCount[village], G.supplyCount[village] - newCards);
    assertEqual(testG.supplyCount[village], G.supplyCount[village] - newCards); 


    // ----------- TEST SET 5: Can only buy card that is <=5 coins --------------
	printf("\nTEST SET 5: CAN ONLY BUY CARD THAT IS <=5 COINS\n");
    
    // Check that a card of cost 6 cannot be bought.
	initializeGame(numPlayers, kingdomCards, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));
    
    choice1 = adventurer;
    
    returnVal = cardEffect(feast, choice1, choice2, choice3, &testG, handpos, &bonus);
    printf("Return advalue = %d, Expected = %d\n", returnVal, -1);
    assertEqual(returnVal, -1);
    
    printf("Adventurer supply count = %d, Expected = %d\n", testG.supplyCount[choice1], G.supplyCount[choice1]);
    assertEqual(testG.supplyCount[choice1], G.supplyCount[choice1]); 
   
    
    // Check that a card of cost 5 can be bought.
	initializeGame(numPlayers, kingdomCards, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));
    
    choice1 = mine;
    
    returnVal = cardEffect(feast, choice1, choice2, choice3, &testG, handpos, &bonus);
    printf("Return value = %d, Expected = %d\n", returnVal, 0);
    assertEqual(returnVal, 0);
    
    printf("Mine supply count = %d, Expected = %d\n", testG.supplyCount[choice1], G.supplyCount[choice1] - newCards);
    assertEqual(testG.supplyCount[choice1], G.supplyCount[choice1] - newCards); */
   
    
    // ----------- TEST SET 6: No state changes for other player --------------
	printf("\nTEST SET 6: NO STATE CHANGES FOR OTHER PLAYER\n");

	printf("Hand count (Player 2) = %d, Expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
    assertEqual(testG.handCount[otherPlayer], G.handCount[otherPlayer]);
    
    printf("Deck count (Player 2) = %d, Expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
    assertEqual(testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
    
    printf("Discard count (Player 2) = %d, Expected = %d\n", testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
    assertEqual(testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
    
    
	// ----------- TEST SET 5: No state changes in card piles --------------
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
    
    G.supplyCount[mine]--;
    
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


