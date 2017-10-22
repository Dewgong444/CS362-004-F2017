#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//#define TESTCARD "adventurer"

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
    printf("--------------------Testing playAdventurer(): -------------------\n");
    //put card in hand.
    printf("We'll introduce adventurer as a card the player has in hand position 0 in order to test it.\n");
    thisPlayer = whoseTurn(&game);
    game.hand[thisPlayer][0] = adventurer;
    memcpy(&testGame, &game, sizeof(struct gameState));
    printf("We've copied the game state to a test copy to compare between them.\n");
    playAdventurer(&testGame);
    //test that it expended an action
    printf("We've now played the adventurer card. We will check to confirm that the player got -1 actions.\n");
    printf("Since adventurer takes 1 action to play, the base game play should have 1 more action than the test game player.\n");
    int baseActions = game.numActions;
    int testActions = testGame.numActions;
    printf("Base player should have 1 action and we have: %d and test player should have 0 and we have: %d. \n", baseActions, testActions);
    assert(testActions == baseActions - 1);
    //test that the adventurer card was played
    printf("We also need to confirm that the adventurer card is properly placed in the played pile.\n");
    printf("Since smithy was only played in the test game and only 1 copy exists in the hand for sure, we just need to make sure the hand position between the players isn't the same.\n");
    if(game.hand[thisPlayer][0] != testGame.hand[thisPlayer][0])
    {
        printf("We've confirmed that adventurer is played.\n");
    }
    else
    {
	i += 1;
	printf("Adventurer card wasn't moved to played pile.\n");
    }
    printf("We can also check the size of the played piles to confirm adventurer ended in the right place.\n");
    int baseDiscard = game.playedCardCount;
    int testDiscard = testGame.playedCardCount;
    printf("We expect the base played to be 0 and get: %d and we expect the test played to be 1 and get: %d \n", baseDiscard, testDiscard);
    if(testDiscard != baseDiscard + 1)
    {
	i += 1;
	printf("The played pile is 0.\n");	
    }
    else
    {
	printf("The played pile is correct. \n");
    }
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
    //test that it drew properly (cards will be the last 2)
    printf("Since the player must have 2 treasure in the deck at the start of the game, adventurer will draw 2 copper. \n");
    assert(testGame.hand[thisPlayer][testGame.handCount[thisPlayer] - 1] == copper);
    assert(testGame.hand[thisPlayer][testGame.handCount[thisPlayer] - 2] == copper);
    //make sure they came from player's deck
    printf("We need to confirm the drawn cards come from the player's deck, compare deck sizes bewtween states.\n");
    int gameDeck = game.deckCount[thisPlayer];
    int testDeck = testGame.deckCount[thisPlayer];
    printf("We expect test deck to be more than 1 card fewer than the base deck. Base deck is: %d. Test deck is: %d. \n", gameDeck, testDeck);
    assert(gameDeck >= testDeck + 2);
    if(i == 0)
    {
    	printf("If we didn't get an error, SUCCESS\n");
    }
    else
    {
	printf("We had some errors :(\n");
    }
    printf("------------------THIS CONCLUDES TESTING FOR playAdventurer() ---------------- \n");
    return 0;
}
