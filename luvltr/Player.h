#ifndef PLAYER_H
#define PLAYER_H

#include "Button.h"
#include "Card.h"

class Button;

class Player
{

	private:
		const char* name;
		int id;
		Card* hand[2];
		Button* buttons[2];
		bool safeFromEffects;
		bool eliminated;
		bool replay;

	public:
		//constructor
		Player(const char* name, int id);
		
		//getters
		const char* getName();
		int getID();
		Card** getHand();
		Button** getButtons();

		//activates/decativates hand
		void setActiveHand(bool a);

		//adds card to hand
		bool addToHand(Card* card);
		
		//adds button to hand
		bool addToHand(Button* button);
		
		//removes button from hand
		void removeFromHand(Button* button);

		//checks if given card is in the hand
		bool cardInHand(Button* button);
		
		//checks if player is eliminated
		bool isEliminated();

		//checks if player is safe
		bool isSafe();

		//sets player safe/unsafes
		void setSafe(bool safe);

		//eliminates player
		void eliminate();

		//checks if player can play again
		bool playAgain();

		//lets player play again or not
		void setReplay(bool replay);
		
		//deletes player's hand
		void deleteHand();

		//prints player's hand in console
		void printHand();

		//resets player's hand
		void resetHand();

};


#endif /* PLAYER_H */