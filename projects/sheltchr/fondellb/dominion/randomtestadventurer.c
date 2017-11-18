#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define MAX_TEST 10000

//randomly tests the use of the adventurer card


int main()
{
    struct gameState game;
    int i;
    int j;
    int n;
    int handCards, deckCards, discardCards, totalCards;
    int currentPlayer;
    int actions;
    int newTotal;
    int errors = 0;
    int numPlayers;
    int baseSeed;
    int seed = time(NULL);
    srand(seed);
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    for(i=0; i < MAX_TEST; i++)
    {
	int beforeTreasure = 0;
	int afterTreasure = 0;
	//initialize game and players randomly
	numPlayers = rand() % 3 + 2; //2-4 players
        baseSeed = rand();
        printf("Initializing:\n");
        initializeGame(numPlayers, k, baseSeed, &game);

	//generate random componenets for player(s)
	currentPlayer = whoseTurn(&game);
        deckCards = rand() % MAX_DECK;
        handCards = rand() % MAX_HAND;
        discardCards = rand() % MAX_DECK;
        totalCards = deckCards + handCards + discardCards;
        game.deckCount[currentPlayer] = deckCards;
	//make the deck with actual cards for this test
	for(n=0; n < deckCards; n++)
	{
	    game.deck[currentPlayer][n] = rand() % treasure_map; 
	    //treasure map is the highest enum card
	}
        game.handCount[currentPlayer] = handCards;
	for(n=0; n < handCards; n++)
	{
	    game.hand[currentPlayer][n] = rand() % treasure_map;
	    //count treasures in hand before we play adventurer
	    if(game.hand[currentPlayer][n] >= copper && game.hand[currentPlayer][n] <= gold)
	    {
		beforeTreasure += 1;
	    }
	}	
        game.discardCount[currentPlayer] = discardCards;
	for(n=0; n < discardCards; n++)
	{
	    game.discard[currentPlayer][n] = rand() % treasure_map;
	}
        actions = game.numActions;
        printf("The information before the Adventurer Card is played:\n");
        printf("The number of cards in deck is: %d \n", deckCards);
        printf("The number of cards in hand is: %d \n", handCards);
        printf("The number of cards in discard is: %d \n", discardCards);
        printf("The number of actions remaining is: %d \n", actions);
	printf("The number of treasure cards in hand is: %d \n", beforeTreasure);
        printf("The total number of cards is: %d \n", totalCards);
	//we've also saved variables with card information before we play the card.
        adventurerCard(&game); //weirdly this doesn't need a handPos
        newTotal = game.deckCount[currentPlayer] + game.handCount[currentPlayer] + game.discardCount[currentPlayer];
        printf("The information following Adventurer being played: \n");
        printf("The number of cards in deck is: %d \n", game.deckCount[currentPlayer]);
        printf("The number of cards in hand is: %d \n", game.handCount[currentPlayer]);
        printf("The number of cards in discard is: %d \n", game.discardCount[currentPlayer]);
        printf("The number of actions remaining is: %d \n", game.numActions);
        printf("The total number of cards is: %d \n", newTotal);
	for(n=0; n < game.handCount[currentPlayer]; n++)
	{
	    if(game.hand[currentPlayer][n] >= copper && game.hand[currentPlayer][n] <= gold)
	    {
		afterTreasure += 1;
	    }
	}
	printf("The number of treasure cards in hand is: %d \n", afterTreasure);
	if(newTotal != totalCards - 1) //account for adventurer being "played"
	{
	    errors += 1;
	    printf("There's an error related to the total number of cards.\n");
	}
	if(handCards != game.handCount[currentPlayer] - 1) //draw 2, discard 1
	{
	    errors += 1;
	    printf("There's an error related to the card draw.\n");
	}
	if(beforeTreasure != afterTreasure - 2) //2 new treasure should be drawn
	{
	    errors += 1;
	    printf("There's an error related to the number of treasure cards.\n");
	}
    }
    printf("There are %d total errors.\n", errors);
    return 0;
    //done
}
