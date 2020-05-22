#include "Player.h"
#include <malloc.h>
#include <iostream>

//constructor
Player::Player(const char* name, int id) {
	this->name = name;
	this->id = id;
	this->hand[0] = NULL;
	this->hand[1] = NULL;
	this->buttons[0] = NULL;
	this->buttons[1] = NULL;
	this->safeFromEffects = false;
	this->eliminated = false;
	this->replay = false;
}

//get player's name
const char* Player::getName() {
	return this->name;
}

//get player's ID
int Player::getID() {
	return this->id;
}

//get player's hand
Card** Player::getHand() {
	return this->hand;
}

//get player's buttons
Button** Player::getButtons() {
	return this->buttons;
}

//add a card to the player's hand
bool Player::addToHand(Card* card) {
	if (!this->buttons[0]) {
		//this->hand[0] = card;
		if(card->getFunc())
			this->buttons[0] = new Button("card", card->getName(), card->getFace(), card->getX(),card->getY(), card->getWidth(),card->getHeight(),card ->getNum(), card->getFunc());
		else	
			this->buttons[0] = new Button("card", card->getName(), card->getFace(), card->getX(),card->getY(), card->getWidth(),card->getHeight());
	}
	else if (!this->buttons[1]) {
		if(card->getFunc())
			this->buttons[1] = new Button("card", card->getName(), card->getFace(), card->getX(), card->getY(), card->getWidth(), card->getHeight(), card->getNum(), card->getFunc());
		else
			this->buttons[1] = new Button("card", card->getName(), card->getFace(), card->getX(), card->getY(), card->getWidth(), card->getHeight());
	}
	else
		return false; //hand full
	return true; //card added
}

//add a button to the player's hand
bool Player::addToHand(Button* button) {
	if (!this->buttons[0]) {
		this->buttons[0] = button;
	}
	else if (!this->buttons[1]) {
		this->buttons[1] = button;
	}
	else
		return false;
	return true;
}


//delete player's hand
void Player::deleteHand() {
	if (this->buttons[0]) {
		std::cout << "removing " << this->buttons[0]->getName();
		this->buttons[0] = NULL;
	}
	if (this->buttons[1]) {
		std::cout << "removing " << this->buttons[1]->getName();
		this->buttons[1] = NULL;
	}
}

//remove the given button from player's hand
void Player::removeFromHand(Button* but) {
	if (this->buttons[0] == but)
		this->buttons[0] = NULL;
	else if (this->buttons[1] == but)	
		this->buttons[1] = NULL;
	
}

//print player's hand in the console
void Player::printHand() {
	if (this->buttons[0])
		std::cout << "Player " << this->name << " has: " << this->buttons[0]->getName() << std::endl;
	else
		std::cout << "Player " << this->name << ": No left hand\n";
	if (this->buttons[1])
		std::cout << "Player " << this->name << " has: " << this->buttons[1]->getName() << std::endl;
	else
		std::cout << "Player " << this->name << ": No right hand\n";
}

//activate/deactivate player's hand
void Player::setActiveHand(bool a) {
	if(this->buttons[0])
		this->buttons[0]->setActive(a);
	if(this->buttons[1])
		this->buttons[1]->setActive(a);
}
//checks if given card is in the hand
bool Player::cardInHand(Button* button) {
	std::cout << "AAA: " << button->getNum();
	if ((this->buttons[0] && this->buttons[0]->getNum() == button->getNum()) ||
		(this->buttons[1] && this->buttons[1]->getNum() == button->getNum()))
		return true;
	return false;
}

//set player safe/unsafe
void Player::setSafe(bool safe) {
	this->safeFromEffects = safe;
}


//eliminate player
void Player::eliminate() {
	this->eliminated = true;
}

//check if player is safe
bool Player::isSafe() {
	return this->safeFromEffects;
}

//check if player is eliminated
bool Player::isEliminated() {
	return this->eliminated;
}

//checks if palyer can play again
bool Player::playAgain() {
	return this->replay;
}

//lets player play again or not
void Player::setReplay(bool replay) {
	this->replay = replay;
}

//resets player's hand
void Player::resetHand() {
	if (this->buttons[0])
		this->buttons[0]->restorePosition();
	if (this->buttons[1])
		this->buttons[1]->restorePosition();
}