#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define MAX_TEST 10000

//random tests for smithy card

int main() 
{
    struct gameState game;
    int i;
    int baseSeed;
    int numPlayers;
    int errors = 0;
    int handCards, deckCards, discardCards, totalCards;
    int currentPlayer;
    int actions;
    int newTotal;
    int seed = time(NULL);
    srand(seed);
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    for(i=0; i < MAX_TEST; i++)
    {
	//initialize the game and players randomly
	numPlayers = rand() % 3 + 2; //2-4 players
	baseSeed = rand();
	printf("Initializing:\n");
	initializeGame(numPlayers, k, baseSeed, &game);
	
	//generate random components for player(s)
	currentPlayer = whoseTurn(&game);
	deckCards = rand() % MAX_DECK;
	handCards = rand() % MAX_HAND;
	discardCards = rand() % MAX_DECK;
	totalCards = deckCards + handCards + discardCards;
	game.deckCount[currentPlayer] = deckCards;
	game.handCount[currentPlayer] = handCards;
	game.discardCount[currentPlayer] = discardCards;
	actions = game.numActions;
	printf("The information before the Smithy Card is played:\n");
	printf("The number of cards in deck is: %d \n", deckCards);
        printf("The number of cards in hand is: %d \n", handCards);
        printf("The number of cards in discard is: %d \n", discardCards);
        printf("The number of actions remaining is: %d \n", actions);
        printf("The total number of cards is: %d \n", totalCards);
	//we've also saved the values for certain things in variables before we play the card
	
	//we're going to play the card, so we'll introduce it to the player's hand
	game.hand[currentPlayer][0] = smithy;
	playSmithy(&game, 0);
	newTotal = game.deckCount[currentPlayer] + game.handCount[currentPlayer] + game.discardCount[currentPlayer];
	//check that the number of cards doesn't change
	printf("The information following Smithy being played: \n");
	printf("The number of cards in deck is: %d \n", game.deckCount[currentPlayer]);
        printf("The number of cards in hand is: %d \n", game.handCount[currentPlayer]);
        printf("The number of cards in discard is: %d \n", game.discardCount[currentPlayer]);
        printf("The number of actions remaining is: %d \n", game.numActions);
        printf("The total number of cards is: %d \n", newTotal);
	if(totalCards != newTotal + 1) //add 1 to account to smithy being played
	{
	    errors += 1;
	    printf("We've found an error relating to the total number of card.\n");
	}
	if(handCards != game.handCount[currentPlayer] - 2) //draw 3, play 1
	{
	    errors += 1;
	    printf("We've found an error relating to the number of cards drawn.\n");
	}
	if(actions != game.numActions + 1)
	{
	    errors += 1;
	    printf("We've found an error relating to the number of actions.\n");
	}
    }
    printf("Number of Errors is: %d \n", errors);
    return 0;
    //done
}
