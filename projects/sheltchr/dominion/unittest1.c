#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//testing if isGameOver(struct gameState *state) works

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
    memcpy(&testGame, &game, sizeof(struct gameState));
    printf("When the game ends, the isGameOver() function will return 1, otherwise it will return 0.\n");
    printf("Confirm that we get a return of 0, the game is not over. Since the game cannot end before the first player's turn, if we check right when we initialize a game, it should return a value of 0.\n");
    int check = isGameOver(&game);
    printf("We expect a value of 0 and we get: %d. \n", check);
    assert(check == 0);
    printf("Now we can check if the game ends when the province supply is 0 by setting it to 0.\n");
    testGame.supplyCount[province] = 0;
    check = isGameOver(&testGame);
    printf("We expect to get a value of 1, signifying the game's ended and we get: %d. \n", check);
    assert(check == 1);
    printf("We will not reset test game back to the initial game state.\n");
    memcpy(&testGame, &game, sizeof(struct gameState));
    printf("We will now test if the game ends on any one pile having a supply of 0. Let's try estate.\n");
    testGame.supplyCount[estate] = 0;
    check = isGameOver(&testGame);
    printf("We expect to get a value of 0, signifying the game is not over and we get: %d. \n", check);
    assert(check == 0);
    printf("We will now empty another supply pile to check if it ends on 2 empty piles. We will empty mine.\n");
    testGame.supplyCount[mine] = 0;
    check = isGameOver(&testGame);
    printf("We expect to get a value of 0, signifying the game is not over and we get: %d. \n", check);
    assert(check == 0);
    printf("We will now empty another supply pile to check if it ends on 3 empty piles. We will empty silver.\n");
    testGame.supplyCount[silver] = 0;
    check = isGameOver(&testGame);
    printf("We expect to get a value of 1, signifying the game is over and we get: %d. \n", check);
    assert(check == 1);
    printf("We will now empty another supply pile to check if it ends on 4 empty piles. We will empty gold.\n");
    testGame.supplyCount[gold] = 0;
    check = isGameOver(&testGame);
    printf("We expect to get a value of 1, signifying the game is over and we get: %d. \n", check);
    assert(check == 1);
    printf("If we didn't get an error, SUCCESS\n");
    printf("------------------THIS CONCLUDES TESTING FOR buyCard() ---------------- \n");
    return 0;
}
