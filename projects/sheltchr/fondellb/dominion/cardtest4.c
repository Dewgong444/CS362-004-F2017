#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//#define TESTCARD "council_room"

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
    printf("--------------------Testing playCouncilRoom(): -------------------\n");
    //put card in hand
    printf("We'll introduce council room as a card the player has in hand position 0 in order to test it.\n");
    thisPlayer = whoseTurn(&game);
    assert(thisPlayer == 0);
    game.hand[thisPlayer][0] = council_room;
    memcpy(&testGame, &game, sizeof(struct gameState));
    printf("We've copied the game state to a test copy to compare between them.\n");
    cardEffect(council_room, 0, 0, 0, &testGame, 0, 0);
    //test that we spent an action
    printf("We've now played the council room card. We will check to confirm that the player got -1 actions.\n");
    printf("Since council room takes 1 action to play, the base game play should have 1 more action than the test game player.\n");
    int baseActions = game.numActions;
    int testActions = testGame.numActions;
    printf("Base player should have 1 action and we have: %d and test player should have 0 and we have: %d. \n", baseActions, testActions);
    if(testActions != baseActions - 1)
    {
	printf("Test game doesn't have the correct number of actions left. We should have 0 and we have %d \n", testActions);
	i++;
    }
    else
    {
	printf("We have the correct number of actions left.\n");
    }
    //test that card played.
    printf("We also need to confirm that the council room card is properly placed in the played pile.\n");
    printf("Since council room was only played in the test game and only 1 copy exists in the hand for sure, we just need to make sure the hand position between the players isn't the same.\n");
    if(game.hand[thisPlayer][0] != testGame.hand[thisPlayer][0])
    {
        printf("We've confirmed that council room is played.\n");
    }
    assert(game.hand[thisPlayer][0] != testGame.hand[thisPlayer][0]);
    printf("We can also check the size of the played piles to confirm council room ended in the right place.\n");
    int baseDiscard = game.playedCardCount;
    int testDiscard = testGame.playedCardCount;
    printf("We expect the base played to be 0 and get: %d and we expect the test played to be 1 and get: %d \n", baseDiscard, testDiscard);
    assert(testDiscard == baseDiscard + 1);
    //test that it drew the right amount of cards.
    printf("We also need to confirm that council room drew 4 cards, which should replace it. Now, test game should have 3 more cards than the base player.\n");
    int baseCount = numHandCards(&game);
    int testCount = numHandCards(&testGame);
    printf("We expect base hand to be 5 and base is: %d. We expect test hand to be 8 and test is: %d. \n", baseCount, testCount);
    assert(baseCount == testCount - 3);
    //check that drawn cards came from the deck
    printf("We need to confirm the drawn cards came out of the deck.\n");
    printf("As such, we need to compare deck counts and ensure test deck has 4 cards less than base deck.\n");
    int baseDeck = game.deckCount[thisPlayer];
    int testDeck = testGame.deckCount[thisPlayer];
    printf("We expect test game to have 4 less than base. Base is: %d. Test is: %d. \n", baseDeck, testDeck);
    assert(baseDeck == testDeck + 4);
    //check that buys increase
    printf("We now need to check that the number of buys increased by 1 compared to the base game.\n");
    int baseBuy = game.numBuys;
    int testBuy = testGame.numBuys;
    printf("We expect base buys to be 1 and it's: %d. We expect test buys to be 2 and it's: %d. \n", baseBuy, testBuy);
    assert(baseBuy == testBuy - 1);
    //check other players drew cards.
    printf("We need to check that other players drew 1 card too.\n");
    printf("The other player in the base game should then have 1 less card in hand than the one in test game.\n");
    int baseOther = game.handCount[1];
    int testOther = testGame.handCount[1];
    printf("We expect base hand to be 0 since they haven't drawn and it's: %d. We expect test hand to be 1 and it's: %d. \n", baseOther, testOther);
    if(baseOther != testOther - 1)
    {
	i += 1;
    	printf("The other players didn't draw.\n");
    }
    //assert money didn't change 
    assert(supplyCount(copper, &game) == supplyCount(copper, &testGame));
    assert(supplyCount(silver, &game) == supplyCount(silver, &testGame));
    assert(supplyCount(gold, &game) == supplyCount(gold, &testGame));
    // assert victory cards didn't change
    assert(supplyCount(estate, &game) == supplyCount(estate, &testGame));
    assert(supplyCount(duchy, &game) == supplyCount(duchy, &testGame));
    assert(supplyCount(province, &game) == supplyCount(province, &testGame));
    //assert kingdom cards didn't change
    int j = 0;
    for(j; j < 10; j++)
    {
        assert(supplyCount(k[j], &game) == supplyCount(k[j], &testGame));
    }
    //assert other players stuff didn't change (except handCount)
    assert(game.deckCount[1] == testGame.deckCount[1]);
    assert(game.discardCount[1] == testGame.discardCount[1]);
    printf("We've asserted the other player's stuff didn't change.\n");
    printf("We've confirmed the other card piles didn't change with assert() statements.\n");
    if(i == 0)
    {
	printf("If we didn't get an error, SUCCESS\n");
    }
    else
    {
	printf("We had some errors :( \n");
    }
    printf("------------------THIS CONCLUDES TESTING FOR playCouncilRoom() ---------------- \n");
    return 0;
}

