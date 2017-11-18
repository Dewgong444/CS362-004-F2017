#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int main() {
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState game, testGame;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		 sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &game);
    printf("--------------------Testing playVillage(): -------------------\n");
    //put card in hand
    printf("We'll introduce village as a card the player has in hand position 0 in order to test it.\n");
    thisPlayer = whoseTurn(&game);
    game.hand[thisPlayer][0] = village;
    memcpy(&testGame, &game, sizeof(struct gameState));
    printf("We've copied the game state to a test copy to compare between them.\n");
    cardEffect(village, 0, 0, 0, &testGame, 0, 0);
    //test for +2 actions
    printf("We've now played the village card. We will check to confirm that the player got +2 actions.\n");
    printf("Since village takes 1 action to play, the test game play should have 1 more action than the base game player.\n");
    int baseActions = game.numActions;
    int testActions = testGame.numActions;
    printf("Base player should have 1 action and we have: %d and test player should have 2 and we have: %d. \n", baseActions, testActions);
    if(testActions != baseActions + 1)
    {
	printf("We should have 2 actions in the test game and we have %d \n", testActions);
    }
    else
    {
	printf("We have the proper number of actions left\n");
    }
    //test for card played
    printf("We also need to confirm that the village card is properly placed in the played pile.\n");
    printf("Since village was only played in the test game and only 1 copy exists in the hand for sure, we just need to make sure the hand position between the players isn't the same.\n");
    if(game.hand[thisPlayer][0] != testGame.hand[thisPlayer][0])
    {
	printf("We've confirmed that village is played.\n");
    }
    assert(game.hand[thisPlayer][0] != testGame.hand[thisPlayer][0]);
    printf("We can also check the size of the played piles to confirm village ended in the right place.\n");
    int baseDiscard = game.playedCardCount;
    int testDiscard = testGame.playedCardCount;
    printf("We expect the base played to be 0 and get: %d and we expect the test played to be 1 and get: %d \n", baseDiscard, testDiscard);
    assert(testDiscard == baseDiscard + 1);
    //test for drawn card.
    printf("We also need to confirm that village drew 1 card, which should replace it. Now, both players should have the same hand size between games.\n");
    int baseCount = numHandCards(&game);
    int testCount = numHandCards(&testGame);
    printf("We expect both hand sizes to be 5. Base is: %d. Test is: %d. \n", baseCount, testCount);
    assert(baseCount == testCount);
    //check that it came from the deck
    printf("We need to confirm the drawn card came out of the deck.\n");
    printf("As such, we need to compare deck counts and ensure test deck has 1 card less than base deck.\n");
    int baseDeck = game.deckCount[thisPlayer];
    int testDeck = testGame.deckCount[thisPlayer];
    printf("We expect test game to have 1 less than base. Base is: %d. Test is: %d. \n", baseDeck, testDeck);
    assert(baseDeck == testDeck + 1);
    //assert kingdom cards didn't change
    int j = 0;
    for(j; j < 10; j++)
    {
        assert(supplyCount(k[j], &game) == supplyCount(k[j], &testGame));
    }
    //assert money didn't change
    assert(supplyCount(copper, &game) == supplyCount(copper, &testGame));
    assert(supplyCount(silver, &game) == supplyCount(silver, &testGame));
    assert(supplyCount(gold, &game) == supplyCount(gold, &testGame));
    //assert victory cards didn't change
    assert(supplyCount(estate, &game) == supplyCount(estate, &testGame));
    assert(supplyCount(duchy, &game) == supplyCount(duchy, &testGame));
    assert(supplyCount(province, &game) == supplyCount(province, &testGame));
    printf("We've confirmed the other card piles didn't change with assert() statements.\n");
    //assert other player stuff didn't change
    assert(game.deckCount[1] == testGame.deckCount[1]);
    assert(game.discardCount[1] == testGame.discardCount[1]);
    assert(game.handCount[1] == testGame.handCount[1]);
    printf("We've asserted the other player's stuff didn't change.\n");
    printf("If we didn't get an error, SUCCESS\n");
    printf("------------------THIS CONCLUDES TESTING FOR playVillage() ---------------- \n");
    return 0;
}
