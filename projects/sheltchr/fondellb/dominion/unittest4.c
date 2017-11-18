#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//checks that buyCard(int supplyPos, struct gameState *state) works. int supply pos is something like "estate", it's the card name.

int main() {
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState game, testGame;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		 sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &game);
    printf("--------------------Testing buyCard(): -------------------\n");
    //copy the state to another "test" state.
    memcpy(&testGame, &game, sizeof(struct gameState));
    //test buyCard under normal conditions
    printf("Before we test that the buyCard fails, let's ensure it works like it's supposed to.\n");
    printf("Since the least money you can start with is 2, you should always be able to buy an estate.\n");
    int supplyBefore = supplyCount(estate, &testGame);
    int testBuy = buyCard(estate, &testGame);
    int supplyAfter = supplyCount(estate, &testGame);
    printf("Supply before the buy attempt is: %d and supply after is: %d. \n", supplyBefore, supplyAfter);
    assert(supplyBefore == supplyAfter + 1);
    assert(testBuy == 0);
    //reset the testing states
    printf("We will reinitialize the game and test game between each test to ensure all data is reset to normal.\n");
    initializeGame(numPlayers, k, seed, &game);
    memcpy(&testGame, &game, sizeof(struct gameState));
    //test buyCard() with 0 buys
    printf("Confirm that you cannot buy a card if you have no buys left to make.\n");
    printf("We will change the numBuys of testGame to 0 and then attempt to buy an estate.\n");
    testGame.numBuys = 0;
    supplyBefore = supplyCount(estate, &testGame);
    testBuy = buyCard(estate, &testGame);
    supplyAfter = supplyCount(estate, &testGame);
    printf("Supply before the buy attempt is: %d and supply after is: %d. \n", supplyBefore, supplyAfter);
    assert(supplyBefore == supplyAfter);
    assert(testBuy == -1);
    //reset again
    initializeGame(numPlayers, k, seed, &game);
    memcpy(&testGame, &game, sizeof(struct gameState));
    printf("We've RESET again.\n");
    //test buyCard() with supply of 0.
    printf("Confirm that if the supply count is 0, you cannot buy that card.\n");
    testGame.supplyCount[estate] = 0;
    printf("We've set the test game's estate supply count to 0.\n");
    supplyBefore = supplyCount(estate, &testGame);
    testBuy = buyCard(estate, &testGame);
    supplyAfter = supplyCount(estate, &testGame);
    printf("Supply before the buy attempt is: %d and supply after is: %d. \n", supplyBefore, supplyAfter);
    assert(supplyBefore == supplyAfter);
    assert(testBuy == -1);
    //reset again
    initializeGame(numPlayers, k, seed, &game);
    memcpy(&testGame, &game, sizeof(struct gameState));
    printf("We've RESET again.\n");
    //test buyCard() with 0 coins
    printf("Confirm that if the supply count is 0, you cannot buy that card.\n");
    testGame.coins = 0;
    printf("We've set the test game's coin count to 0.\n");
    supplyBefore = supplyCount(estate, &testGame);
    testBuy = buyCard(estate, &testGame);
    supplyAfter = supplyCount(estate, &testGame);
    printf("Supply before the buy attempt is: %d and supply after is: %d. \n", supplyBefore, supplyAfter);
    assert(supplyBefore == supplyAfter);
    assert(testBuy == -1);
    printf("If we didn't get an error, SUCCESS\n");
    printf("------------------THIS CONCLUDES TESTING FOR buyCard() ---------------- \n");
    return 0;
}
