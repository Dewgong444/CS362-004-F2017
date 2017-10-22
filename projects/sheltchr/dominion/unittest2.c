#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//tests that numHandCards(struct gameState *state) works

int main() {
    int handpos = 0;
    int seed = 1000;
    int numPlayers = 2;
    struct gameState game, testGame;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &game);
    printf("--------------------Testing numHandCards(): -------------------\n");
    //copy the state to another "test" state.
    memcpy(&testGame, &game, sizeof(struct gameState));
    int thisPlayer = whoseTurn(&testGame);
    int testHandCount = testGame.handCount[thisPlayer];
    int realPlayer = whoseTurn(&game);    
    int realHandCount = game.handCount[realPlayer];
    printf("Confirm base hand count is the same between game states.\n");
    printf("Hand count is base game is: %d and hand count in test game is: %d. \n", realHandCount, testHandCount);
    assert(testHandCount == realHandCount);
    int functionHandCount = numHandCards(&testGame);
    printf("Confirm the function returns the right number of cards by comparing it to a direct call.\n");
    printf("Direct call of hand count is: %d and function call of hand count is: %d. \n", testHandCount, functionHandCount);
    assert(testHandCount == functionHandCount);
    int drawn = drawCard(whoseTurn(&testGame), &testGame);
    assert(drawn == 0);
    testHandCount = numHandCards(&testGame);
    printf("We've drawn a card to the player in test game, we'll confirm his hand is 1 more than the hand in the base game.\n");
    printf("Hand count is base game is: %d and hand count in test game is: %d. \n", realHandCount, testHandCount);
    assert(testHandCount == realHandCount + 1);
    printf("If we didn't get an error, SUCCESS\n");
    printf("------------------THIS CONCLUDES TESTING FOR numHandCards() ---------------- \n");
    return 0;
}
