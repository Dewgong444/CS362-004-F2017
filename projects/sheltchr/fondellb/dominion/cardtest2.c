#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//#define TESTCARD "smithy"

int main() {
    int i = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState game, testGame;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		 sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &game);
    printf("--------------------Testing smithyCard(): -------------------\n");
    //put card in hand
    printf("We'll introduce smithy as a card the player has in hand position 0 in order to test it.\n");
    thisPlayer = whoseTurn(&game);
    game.hand[thisPlayer][0] = smithy;
    memcpy(&testGame, &game, sizeof(struct gameState));
    printf("We've copied the game state to a test copy to compare between them.\n");
    cardEffect(smithy, 0, 0, 0, &testGame, 0, 0);
    //test that it spent an action
    printf("We've now played the smithy card. We will check to confirm that the player got -1 actions.\n");
    printf("Since smithy takes 1 action to play, the base game play should have 1 more action than the test game player.\n");
    int baseActions = game.numActions;
    int testActions = testGame.numActions;
    printf("Base player should have 1 action and we have: %d and test player should have 0 and we have: %d. \n", baseActions, testActions);
    if(testActions != baseActions - 1)
    {
	printf("We should have 0 actions left in the test game and we have %d \n", testActions);
	i += 1;
    }
    else
    {
	printf("Number of actions left after playing Smithy is correct.\n");
    }
    //test that card played.
    printf("We also need to confirm that the smithy card is properly placed in the played pile.\n");
    printf("Since smithy was only played in the test game and only 1 copy exists in the hand for sure, we just need to make sure the hand position between the players isn't the same.\n");
    if(game.hand[thisPlayer][0] != testGame.hand[thisPlayer][0])
    {
        printf("We've confirmed that smithy is played.\n");
    }
    assert(game.hand[thisPlayer][0] != testGame.hand[thisPlayer][0]);
    printf("We can also check the size of the played piles to confirm smithy ended in the right place.\n");
    int baseDiscard = game.playedCardCount;
    int testDiscard = testGame.playedCardCount;
    printf("We expect the base played to be 0 and get: %d and we expect the test played to be 1 and get: %d \n", baseDiscard, testDiscard);
    assert(testDiscard == baseDiscard + 1);
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
    //test that it drew the right amount of cards. This will error since I introduced a bug here.
    printf("We also need to confirm that smithy drew 3 cards, which should replace it. Now, test game should have 2 more cards than the base player.\n");
    int baseCount = numHandCards(&game);
    int testCount = numHandCards(&testGame);
    printf("We expect base hand to be 5 and base is: %d. We expect test hand to be 7 and test is: %d. \n", baseCount, testCount);
    if(baseCount != testCount - 2)
    {
	i += 1;
    	printf("We didn't draw the right number of cards!\n");
    }
    //check that drawn cards come from the deck.
    printf("We need to confirm the drawn cards came out of the deck.\n");
    printf("As such, we need to compare deck counts and ensure test deck has 3 cards less than base deck.\n");
    int baseDeck = game.deckCount[thisPlayer];
    int testDeck = testGame.deckCount[thisPlayer];
    printf("We expect test game to have 3 less than base. Base is: %d. Test is: %d. \n", baseDeck, testDeck);
    if(baseDeck != testDeck + 3)
    {
	i += 1;
	printf("We have the wrong number of cards left in the deck!\n");
    }
    //assert(baseDeck == testDeck + 3);
    if(i ==0)
    {
    	printf("If we didn't get an error, SUCCESS\n");
    }
    else
    {
	printf("We got some errors, :( \n");
    }
    printf("------------------THIS CONCLUDES TESTING FOR playSmithy() ---------------- \n");
    return 0;
}
