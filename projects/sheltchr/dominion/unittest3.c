#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//tests that supplyCount(int card, struct gameState *state) works

int main() {
    int handpos = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState game, testGame;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		 sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &game);
    printf("--------------------TESTING supplyCount(): ------------------- \n");
    //copy the state to another "test" game.
    memcpy(&testGame, &game, sizeof(struct gameState));
    int baseSupply = game.supplyCount[estate];
    int testSupply = testGame.supplyCount[estate];
    printf("Confirm the base supply count for 'estate' is the same between game states. \n");
    printf("Estate supply in the base game is: %d and the supply in test game is: %d. \n", baseSupply, testSupply);
    assert(baseSupply == testSupply);
    int functionSupply = supplyCount(estate, &testGame);
    printf("Confirm the direct call matches the function call for supplyCount() on 'estate'. \n");
    printf("Estate supply directly called is: %d and function called is: %d. \n", testSupply, functionSupply);
    assert(testSupply == functionSupply);
    int buyEstate = buyCard(estate, &testGame);
    int newSupply = supplyCount(estate, &testGame);
    printf("Confirm buying an estate in the test game changes the supply call on 'estate'. \n");
    printf("Estate supply in base game is: %d and estate supply in test game is: %d. \n", baseSupply, newSupply);
    assert(baseSupply == newSupply + 1);
    printf("If we didn't get an error, SUCCESS\n");
    printf("------------------THIS CONCLUDES TESTING FOR supplyCount() ---------------- \n");
    return 0;
}
