#include "Deck.h"
#include <iostream>
//default constructor 
Deck::Deck() {

	this->currIndex = 0;
	this->len = 0;
	dummyCard = new Card("dummy", -1);
	
	for (int i = 0; i < 16; i++)
		stack16[i] = dummyCard;
}


Deck::Deck(Card* array16[16]) {
	this->currIndex = 0;
	this->len = 16;
	dummyCard = new Card("dummy", -1);

	for (int i = 0; i < 16; i++) {
		
		stack16[i] = array16[i];
		
	}

}
//returns how many cards are still in the deck
int Deck::getLen() {
	return this->len;
}

//returns the card in position i
Card* Deck::getCard(int i) {
	return this->stack16[i+this->currIndex];
}

//gets top card
Card* Deck::getTop() {
	return this->stack16[currIndex];
}
//removes top card
void Deck::removeTop() {
	this->len--;
	this->currIndex++;
	
}
//checks if deck is empty
bool Deck::isEmpty() {
	return this->len == 0;
}