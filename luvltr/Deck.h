#ifndef DECK_H
#define DECK_H

#include "Card.h"
class Deck //stack
{
private:
	Card* stack16[16];
	int currIndex;
	Card* dummyCard;
	int len;

public:
	//constructors
	Deck();
	Deck(Card* array16[16]);
	
	//returns how many cards are still in the deck
	int getLen();
	
	//returns the card in position i
	Card* getCard(int i);

	//gets top card
	Card* getTop();
	
	//removes top card
	void removeTop();

	//checks if deck is empty
	bool isEmpty();

	
};



#endif /* DECK_H */
