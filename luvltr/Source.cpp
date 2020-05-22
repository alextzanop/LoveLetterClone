#include <iostream>
#include <stdio.h> //NULL
#include <stdlib.h> //rand
#include <time.h> //time
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"

#include "includeAll.h"


void drawStuff();
Card** makeDeck16();
void dealCards(Player* p1, Player* p2, Deck* deck);
void giveCard(Player* player, Deck* deck);
void drawButton(Button*);
void makeGuardButtons();
void drawGuardButtons(Button** guardButtons);
void makePrinceButtons();
void drawPrinceButtons(Button** princeButtons);




Player* player1 = new Player("one", 1);
Player* player2 = new Player("two", 2);
Button* play = new Button("play", "play", NULL, SCRN_W / 2 - 50, SCRN_H / 2 - 25, 100, 50);
bool pause = false; //this is for pausing the game when a player finished their turn. Click the play button again to unpause
//when paused, both hands are inactive and only the cardbacks are shown
ALLEGRO_BITMAP* back11 = NULL;
ALLEGRO_BITMAP* back12 = NULL;
ALLEGRO_BITMAP* back21 = NULL;
ALLEGRO_BITMAP* back22 = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
Player* activePlayer = player1;
Player* inactivePlayer = player2;
Button* guardButtons[7];
Button* guardPick = NULL;
Button* princeButtons[2];
Deck* deck16;
ALLEGRO_COLOR bgcol;


int main() {


	//Initialize Allegro
	al_init();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_mouse();
	
	bgcol = al_map_rgb(250, 0, 0); //bg color
	ALLEGRO_DISPLAY* display = al_create_display(SCRN_W, SCRN_H);

	//initialize event queue
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_mouse_event_source());
	

	//make card backs
	back11 = al_load_bitmap(CARD_BACK_URL);
	back12 = al_load_bitmap(CARD_BACK_URL);
	back21 = al_load_bitmap(CARD_BACK_URL);
	back22 = al_load_bitmap(CARD_BACK_URL);

	makeGuardButtons();
	makePrinceButtons();


	Card** cards = makeDeck16();
	deck16 = new Deck(cards);
	

	int mouseX = 0;
	int mouseY = 0;
	dealCards(player1, player2, deck16);
	player2->setActiveHand(false);
	//Button* butList[5] = { play, player1->getButtons()[0], player1->getButtons()[1], player2->getButtons()[0], player2->getButtons()[1] };
	

	while (true) {
		//end game when a player is eliminated
		if (activePlayer->isEliminated() || inactivePlayer->isEliminated()) {
			std::cout << "Game over";
			al_clear_to_color(al_map_rgb(123, 456, 789));
			al_flip_display();
			break;
		}


		drawStuff();
		

		ALLEGRO_EVENT events;
		Button* tempBut = NULL;
		al_wait_for_event(event_queue, &events);

		//reset hands
		if (activePlayer->playAgain()) {
			activePlayer->setReplay(false);
			activePlayer->resetHand();
			inactivePlayer->resetHand();
		}
		

		//check mouse button down
		if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			mouseX = events.mouse.x;
			mouseY = events.mouse.y;
			
			//selects the green play button
			if (play->mouseInBounds(mouseX, mouseY))
				play->select();

			//selects the active player's left card
			else if (activePlayer->getButtons()[0] && activePlayer->getButtons()[0]->mouseInBounds(mouseX, mouseY)) {
				activePlayer->getButtons()[0]->select();
				//if (activePlayer->getButtons()[1] && activePlayer->getButtons()[1]->isSelected())
					//activePlayer->getButtons()[1]->unSelect();
			}

			//selects the avtice player's right card
			else if (activePlayer->getButtons()[1] && activePlayer->getButtons()[1]->mouseInBounds(mouseX, mouseY)) {
				activePlayer->getButtons()[1]->select();
				//if (activePlayer->getButtons()[0] && activePlayer->getButtons()[0]->isSelected())
					//activePlayer->getButtons()[0]->unSelect();
			}
			
		}
		//check mouse button up
		else if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			mouseX = events.mouse.x;
			mouseY = events.mouse.y;
			
			//Play selected
			if (play->mouseInBounds(mouseX, mouseY) && play->isSelected()) {
				Button* selectedBut = NULL;
				//get selected card
				if (!pause && activePlayer->getButtons()[0] && activePlayer->getButtons()[0]->isSelected()) {
					
					selectedBut = activePlayer->getButtons()[0];
					//unselect other card
					if(activePlayer->getButtons()[1])
						activePlayer->getButtons()[1]->unSelect();
				}
				else if (!pause && activePlayer->getButtons()[1] && activePlayer->getButtons()[1]->isSelected()) {
					selectedBut = activePlayer->getButtons()[1];
					//unselect other card
					if(activePlayer->getButtons()[0])
						activePlayer->getButtons()[0]->unSelect();
				}
				
				
				if (!pause && selectedBut && !activePlayer->playAgain()) {
					
					//activate the selected card's effect
					selectedBut->cardEffect(activePlayer, inactivePlayer);

					//if the inactive player is safe, do nothing
					if(inactivePlayer->isSafe())
						inactivePlayer->setSafe(false);

					play->onRelease();

					if (!inactivePlayer->isSafe() && !activePlayer->playAgain()) {
						if (activePlayer == player1) {
							activePlayer = player2; //change active player
							inactivePlayer = player1; //change inactive player
							player1->removeFromHand(selectedBut); //remove card
							player1->setActiveHand(false); //deactivate player's buttons
							bgcol = al_map_rgb(0, 0, 255); //change bg color
						}
						else {
							activePlayer = player1; //change active player
							inactivePlayer = player2; //change inactive player
							player2->removeFromHand(selectedBut); //remove card
							player2->setActiveHand(false); //deactivate player's buttons
							bgcol = al_map_rgb(255, 0, 0); //change bg color
						}

						giveCard(activePlayer, deck16); //deal next card
						activePlayer->setActiveHand(true); //activate hand
					}

					if (activePlayer->playAgain()) {
						play->unSelect();
						activePlayer->resetHand();
					}
					pause = true;
				}

				//if player has to play again, remove that
				//might be useless
				else if (!pause && activePlayer->playAgain()) {
					activePlayer->setReplay(false);
					if (selectedBut) {
						selectedBut->unSelect();
						selectedBut->setClicked(false);
					}
				}

				else if (pause) {
					pause = false;
				}

			}

			//select left card
			else if (!pause && activePlayer->getButtons()[0] && activePlayer->getButtons()[0]->mouseInBounds(mouseX, mouseY) && activePlayer->getButtons()[0]->isSelected()) {
				activePlayer->getButtons()[0]->onRelease();
				play->unSelect();
				if(activePlayer->getButtons()[1])
					activePlayer->getButtons()[1]->unSelect();
			}

			//select right card
			else if (!pause && activePlayer->getButtons()[1] && activePlayer->getButtons()[1]->mouseInBounds(mouseX, mouseY) && activePlayer->getButtons()[1]->isSelected()) {
				activePlayer->getButtons()[1]->onRelease();
				play->unSelect();
				if(activePlayer->getButtons()[0])
					activePlayer->getButtons()[0]->unSelect();
			}

		}

		drawStuff();
		al_flip_display();

		
	}
		
	//kill stuff	
	al_destroy_display(display);
	al_destroy_bitmap(back11);
	al_destroy_bitmap(back12);
	al_destroy_bitmap(back21);
	al_destroy_bitmap(back22);
	al_destroy_event_queue(event_queue);
	al_uninstall_mouse();


	
	
	return 0;
}

//draws all the buttons on the screen
void drawStuff() {
	al_clear_to_color(bgcol);
	drawButton(play);
	//draw initial cards

	if (pause) {
		if (player1->getButtons()[0]) {
			al_draw_bitmap(back11, player1->getButtons()[0]->getX(), player1->getButtons()[0]->getY(), 0);
		}
		if (player1->getButtons()[1]) {
			al_draw_bitmap(back12, player1->getButtons()[1]->getX(), player1->getButtons()[1]->getY(), 0);
		}

		if (player2->getButtons()[0])
			al_draw_bitmap(back21, player2->getButtons()[0]->getX(), player2->getButtons()[0]->getY(), 0);
		if (player2->getButtons()[1])
			al_draw_bitmap(back22, player2->getButtons()[1]->getX(), player2->getButtons()[1]->getY(), 0);
		return;
	}

	if (activePlayer == player1) {
		if(player1->getButtons()[0])
			al_draw_bitmap(player1->getButtons()[0]->getFace(), player1->getButtons()[0]->getX(), player1->getButtons()[0]->getY(), 0);
		if (player1->getButtons()[1])
			al_draw_bitmap(player1->getButtons()[1]->getFace(), player1->getButtons()[1]->getX(), player1->getButtons()[1]->getY(), 0);
		
		if (player2->getButtons()[0])
			al_draw_bitmap(back21, player2->getButtons()[0]->getX(), player2->getButtons()[0]->getY(), 0);
		if (player2->getButtons()[1])
			al_draw_bitmap(back22, player2->getButtons()[1]->getX(), player2->getButtons()[1]->getY(), 0);
	}

	else {
		if (player1->getButtons()[0]) {
			al_draw_bitmap(back11, player1->getButtons()[0]->getX(), player1->getButtons()[0]->getY(), 0);
		}
		if (player1->getButtons()[1]) {
			al_draw_bitmap(back12, player1->getButtons()[1]->getX(), player1->getButtons()[1]->getY(), 0);
		}
		if (player2->getButtons()[0])
			al_draw_bitmap(player2->getButtons()[0]->getFace(), player2->getButtons()[0]->getX(), player2->getButtons()[0]->getY(), 0);
		if (player2->getButtons()[1])
			al_draw_bitmap(player2->getButtons()[1]->getFace(), player2->getButtons()[1]->getX(), player2->getButtons()[1]->getY(), 0);
	}
	
}

//create the 16 card deck
Card** makeDeck16() {
	Card* princess  = new Card("Princess", 8, al_load_bitmap("../Cards/princess.jpg"), PrincessEffect);
	Card* countess  = new Card("Countess", 7, al_load_bitmap("../Cards/countess.jpg"), CountessEffect);
	Card* king	    = new Card("King", 6, al_load_bitmap("../Cards/king.jpg"), KingEffect);
	Card* prince1   = new Card("Prince", 5, al_load_bitmap("../Cards/prince.jpg"), PrinceEffect);
	Card* prince2   = new Card("Prince", 5, al_load_bitmap("../Cards/prince.jpg"), PrinceEffect);
	Card* handmaid1 = new Card("Handmaid", 4, al_load_bitmap("../Cards/handmaid.jpg"), HandmaidEffect);
	Card* handmaid2 = new Card("Handmaid", 4, al_load_bitmap("../Cards/handmaid.jpg"), HandmaidEffect);
	Card* baron1	= new Card("Baron", 3, al_load_bitmap("../Cards/baron.jpg"), BaronEffect);
	Card* baron2	= new Card("Baron", 3, al_load_bitmap("../Cards/baron.jpg"), BaronEffect);
	Card* priest1	= new Card("Priest",2, al_load_bitmap("../Cards/priest.jpg"), PriestEffect);
	Card* priest2	= new Card("Priest", 2, al_load_bitmap("../Cards/priest.jpg"), PriestEffect);
	Card* guard1	= new Card("Guard", 1, al_load_bitmap("../Cards/guard.jpg"), GuardEffect);
	Card* guard2	= new Card("Guard", 1, al_load_bitmap("../Cards/guard.jpg"), GuardEffect);
	Card* guard3	= new Card("Guard", 1, al_load_bitmap("../Cards/guard.jpg"), GuardEffect);
	Card* guard4	= new Card("Guard", 1, al_load_bitmap("../Cards/guard.jpg"), GuardEffect);
	Card* guard5	= new Card("Guard", 1, al_load_bitmap("../Cards/guard.jpg"), GuardEffect);

	Card** newDeck16 = (Card **)malloc(16 * sizeof(Card*));
	//shuffle deck
	srand(time(NULL));

	int shufflePos[16] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int temp[16];
	int r = -1;
	int mod = 0;

	for (int i = 0; i < 16; i++) {
		do {
			mod = rand() % 16;
			r = shufflePos[mod];
		} while (r == -1);
		shufflePos[mod] = -1;
		temp[i] = r;
	}
	

	
	newDeck16[temp[0]] = princess;
	newDeck16[temp[1]] = countess;
	newDeck16[temp[2]] = king;
	newDeck16[temp[3]] = prince1;
	newDeck16[temp[4]] = prince2;
	newDeck16[temp[5]] = handmaid1;
	newDeck16[temp[6]] = handmaid2;
	newDeck16[temp[7]] = baron1;
	newDeck16[temp[8]] = baron2;
	newDeck16[temp[9]] = priest1;
	newDeck16[temp[10]] = priest2;
	newDeck16[temp[11]] = guard1;
	newDeck16[temp[12]] = guard2;
	newDeck16[temp[13]] = guard3;
	newDeck16[temp[14]] = guard4;
	newDeck16[temp[15]] = guard5;
	

	

	return newDeck16;
}

//create buttons for when playing a guard
void makeGuardButtons() {
	Button* two   = new Button("guardButton", "guardTwo", al_load_bitmap("../Cards/two.jpg"),2, 64, SCRN_H / 2 - 32, 64, 64);
	Button* three = new Button("guardButton", "guardThree", al_load_bitmap("../Cards/three.jpg"),3, 3 * 64, SCRN_H / 2 - 32, 64, 64);
	Button* four  = new Button("guardButton", "guardFour", al_load_bitmap("../Cards/four.jpg"),4, 5 * 64, SCRN_H / 2 - 32, 64, 64);
	Button* five  = new Button("guardButton", "guardFive", al_load_bitmap("../Cards/five.jpg"),5, 7 * 64, SCRN_H / 2 - 32, 64, 64);
	Button* six   = new Button("guardButton", "guardSix", al_load_bitmap("../Cards/six.jpg"),6, 9 * 64, SCRN_H / 2 - 32, 64, 64);
	Button* seven = new Button("guardButton", "guardSeven", al_load_bitmap("../Cards/seven.jpg"),7, 11 * 64, SCRN_H / 2 - 32, 64, 64);
	Button* eight = new Button("guardButton", "guardEight", al_load_bitmap("../Cards/eight.jpg"),8, 13 * 64, SCRN_H / 2 - 32, 64, 64);

	guardButtons[0] = two;
	guardButtons[1] = three;
	guardButtons[2] = four;
	guardButtons[3] = five;
	guardButtons[4] = six;
	guardButtons[5] = seven;
	guardButtons[6] = eight;

	guardPick = new Button("guardPick", "guardPick", al_load_bitmap("../Cards/guardPick.jpg"), 500, 500, 128, 32);
}

//draw the buttons for when playing the guard
void drawGuardButtons(Button** guardButtons) {
	for (int i = 0; i < 7; i++) {
		al_draw_bitmap(guardButtons[i]->getFace(), guardButtons[i]->getX(), guardButtons[i]->getY(), 0);
	}

	//pick button
	al_draw_bitmap(guardPick->getFace(), guardPick->getX(), guardPick->getY(), 0);

	al_flip_display();
	
}

//create buttons for when playing a prince
void makePrinceButtons() {
	Button* princePlayer1 = new Button("princeButton", "princePlayer1", al_load_bitmap("../Cards/you.jpg"), 5 * 64, SCRN_H / 2 - 32 ,128, 32);
	Button* princePlayer2 = new Button("princeButton", "princePlayer2", al_load_bitmap("../Cards/other.jpg"), 9 * 64, SCRN_H / 2 - 32 , 128, 32);
	
	princeButtons[0] = princePlayer1;
	princeButtons[1] = princePlayer2;

}

//draw the buttons for when playing a guard
void drawPrinceButtons(Button** princeButtons) {
	al_draw_bitmap(princeButtons[0]->getFace(), princeButtons[0]->getX(), princeButtons[0]->getY(), 0);
	al_draw_bitmap(princeButtons[1]->getFace(), princeButtons[1]->getX(), princeButtons[1]->getY(), 0);

	al_draw_bitmap(guardPick->getFace(), guardPick->getX(), guardPick->getY(), 0);

	al_flip_display();
}


//deal cards from the deck to both players
void dealCards(Player* p1, Player* p2, Deck* deck) {

	Card* card;
	card = deck->getTop();
	card->setX(300);
	card->setY(TOP_Y);
	card->setWidth(CARD_WDT);
	card->setHeight(CARD_HGT);
	p1->addToHand(card);
	deck ->removeTop();

	card = deck->getTop();
	card->setX(500);
	card->setY(TOP_Y);
	card->setWidth(CARD_WDT);
	card->setHeight(CARD_HGT);
	p1->addToHand(card);
	deck->removeTop();

	card = deck->getTop();
	card->setX(300);
	card->setY(BOT_Y);
	card->setWidth(CARD_WDT);
	card->setHeight(CARD_HGT);
	p2->addToHand(card);
	deck->removeTop();


	/*card = deck.getTop();
	card->setX(500);
	card->setY(BOT_Y);
	card->setWidth(CARD_WDT);
	card->setHeight(CARD_HGT);
	p2->addToHand(card);
	deck.removeTop();*/
	

}

//draw the given button on the screen
void drawButton(Button* button) {
	al_draw_filled_rectangle(button->getX(), button->getY(), button->getX() + button->getWidth(),
		button->getY() + button->getHeight(), al_map_rgb(123, 201, 24));
	//al_flip_display();
}

//deals the next card from the deck to the given player
void giveCard(Player* player, Deck* deck) {
	Card* card = NULL;
	if (!deck->isEmpty()) {
		card = deck->getTop();
		if (player == player1) {
			if (!player->getButtons()[0]) {
				card->setX(300);
				card->setY(TOP_Y);
				card->setWidth(CARD_WDT);
				card->setHeight(CARD_HGT);
			}
			else if (!player->getButtons()[1]) {
				card = deck->getTop();
				card->setX(500);
				card->setY(TOP_Y);
				card->setWidth(CARD_WDT);
				card->setHeight(CARD_HGT);
			}
		}
		else if (player == player2) {
			if (!player->getButtons()[0]) {
				card = deck->getTop();
				card->setX(300);
				card->setY(BOT_Y);
				card->setWidth(CARD_WDT);
				card->setHeight(CARD_HGT);
			}
			else if (!player->getButtons()[1]) {
				card = deck->getTop();
				card->setX(500);
				card->setY(BOT_Y);
				card->setWidth(CARD_WDT);
				card->setHeight(CARD_HGT);
			}
		}
		player->addToHand(deck->getTop());
		deck->removeTop();
	}
}


//effects for each card
//a being the active player, b being the inactive player

void BaronEffect(Player* a, Player* b) {
	
	if (b->isSafe())
		return;

	Button* playerA = a->getButtons()[0] ? a->getButtons()[0] : a->getButtons()[1];
	Button* playerB = b->getButtons()[0] ? b->getButtons()[0] : b->getButtons()[1];

	if (playerA->getNum() < playerB->getNum()) {
		std::cout << "Player " << a->getName() << " eliminated!";
		a->eliminate();
	}
	else if (playerB->getNum() < playerA->getNum()) {
		std::cout << "Player " << b->getName() << " eliminated!";
		b->eliminate();
	}
}

void CountessEffect(Player* a, Player* b) {
	std::cout << "Countess\n";
}

void GuardEffect(Player* a, Player* b) {
	if (b->isSafe())
		return;

	ALLEGRO_EVENT ev;
	int mouseX = 0;
	int mouseY = 0;
	Button* selectedButton = NULL;
	bool done = false;
	do {
		drawStuff();
		drawGuardButtons(guardButtons);
		al_wait_for_event(event_queue, &ev);
		mouseX = ev.mouse.x;
		mouseY = ev.mouse.y;
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			
			//check pick button
			if (guardPick->mouseInBounds(mouseX, mouseY)) {
				guardPick->select();
			}

			
			else {

				//check guard buttons
				for (int i = 0; i < 7; i++) {
					if (guardButtons[i]->mouseInBounds(mouseX, mouseY)) {
							if (!guardButtons[i]->isSelected()) {
									guardButtons[i]->select();
									selectedButton = guardButtons[i];

								//unselect all others
								for (int j = 0; j < 7; j++) {
									if (j != i ) {
										guardButtons[j]->unSelect();
									}
								}
							}
							else {
								guardButtons[i]->unSelect();
								//guardButtons[i]->resetButton();
								selectedButton = NULL;
							}
						break;

					}
				}
			}
			
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			if (guardPick->mouseInBounds(mouseX, mouseY)) {
				if (selectedButton && guardPick->isSelected() && selectedButton->isClicked()) {
					
					done = true;
					guardPick->unSelect();
				}
			}
			else {
				//check guard buttons
				if (selectedButton && selectedButton->mouseInBounds(mouseX, mouseY)) {
					if (selectedButton->isClicked())
						selectedButton->resetButton();
					else {
						selectedButton->setClicked(true);
						selectedButton->onRelease();
					}
				}
				

				for (int i = 0; i < 7; i++) {
					if (!guardButtons[i]->isSelected() && (guardButtons[i]->getStartY() != guardButtons[i]->getY())) {
						guardButtons[i]->resetButton();
					}
					
				}
			}
		}


		//skip all other events
		else {
			continue;
		}
		
		
	} while (!done);
	if (selectedButton)
		selectedButton->resetButton();
	if (selectedButton && b->cardInHand(selectedButton))
		b->eliminate();


}

void HandmaidEffect(Player* a, Player* b) {
	a->setSafe(true);
}

void KingEffect(Player* a, Player* b) {
	
	//check countess(working)	
	if (a->getButtons()[0]->getName() == "Countess" || a->getButtons()[1]->getName() == "Countess") {
		std::cout << "WARNING: You must discard the Countess";
		a->setReplay(true);
		return;
	}

	if (b->isSafe())
		return;


	int aY = 0;
	int bY = 0;
	if (a == player1) {
		aY = TOP_Y;
		bY = BOT_Y;
	}
	else {
		aY = BOT_Y;
		bY = TOP_Y;
	}

	
	
	
	/*(next step)*/
	
	
	//trade hands
	Button* playerA = a->getButtons()[0]->getName() == "King" ? a->getButtons()[1] : a->getButtons()[0];
	Button* playerB = b->getButtons()[0] ? b->getButtons()[0] : b->getButtons()[1];
	a->deleteHand();
	b->deleteHand();
		
		
	if (!a->addToHand(new Button("card", playerB->getName(), playerB->getFace(), 300, aY, playerB->getWidth(), playerB->getHeight(), playerB->getNum(), playerB->getFunc())))
		std::cout << "CAN'T ADD\n";
	if (!b->addToHand(new Button("card", playerA->getName(), playerA->getFace(), 300, bY, playerA->getWidth(), playerA->getHeight(), playerA->getNum(), playerA->getFunc()))) {
		std::cout << "CAN'T ADD\n";
	}
	
	
	
}

void PriestEffect(Player* a, Player* b) {
	if (b->isSafe())
		return;

	if (b->getButtons()[0]) {
		std::cout << "Player " << b->getName() << "'s hand: " << b->getButtons()[0]->getName()<<std::endl;
	}
	else if (b->getButtons()[1])
		std::cout << "Player " << b->getName() << "'s hand: " << b->getButtons()[1]->getName()<<std::endl;

}

void PrinceEffect(Player* a, Player* b) {
	//check countess
	if (a->getButtons()[0]->getName() == "Countess" || a->getButtons()[0]->getName() == "Countess") {
		std::cout << "WARNING: You must discard the Countess\n";
		a->setReplay(true);
		return;
	}

	if (b->isSafe()) {
		std::cout << "The other player is safe. Picking you automatically\n";
		a->deleteHand();
		giveCard(a, deck16);
		return;
	}

	//choose player
	ALLEGRO_EVENT ev;
	int mouseX = 0;
	int mouseY = 0;
	Button* selectedButton = NULL;
	bool done = false;
	do {
		drawStuff();
		drawPrinceButtons(princeButtons);
		al_wait_for_event(event_queue, &ev);
		mouseX = ev.mouse.x;
		mouseY = ev.mouse.y;
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

			//check pick button
			if (guardPick->mouseInBounds(mouseX, mouseY)) {
				guardPick->select();
			}


			else {

				//check guard buttons
				for (int i = 0; i < 2; i++) {
					if (princeButtons[i]->mouseInBounds(mouseX, mouseY)) {
						if (!princeButtons[i]->isSelected()) {
							princeButtons[i]->select();
							selectedButton = princeButtons[i];

							//unselect all others
							for (int j = 0; j < 2; j++) {
								if (j != i) {
									princeButtons[j]->unSelect();
								}
							}
						}
						else {
							princeButtons[i]->unSelect();
							//princeButtons[i]->resetButton();
							selectedButton = NULL;
						}
						break;

					}
				}
			}

		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			if (guardPick->mouseInBounds(mouseX, mouseY)) {
				if (selectedButton && guardPick->isSelected() && selectedButton->isClicked()) {
					
					done = true;
					guardPick->unSelect();
				}
			}
			else {
				//check prince buttons
				if (selectedButton && selectedButton->mouseInBounds(mouseX, mouseY)) {
					if (selectedButton->isClicked())
						selectedButton->resetButton();
					else {
						selectedButton->setClicked(true);
						selectedButton->onRelease();
					}
				}


				for (int i = 0; i < 2; i++) {
					if (!princeButtons[i]->isSelected() && (princeButtons[i]->getStartY() != princeButtons[i]->getY())) {
						princeButtons[i]->resetButton();
					}

				}
			}
		}


		//skip all other events
		else {
			continue;
		}


	} while (!done);
	if (selectedButton)
		selectedButton->resetButton();

	//effect
	if (selectedButton) {
		//active player picked themselves
		if (selectedButton == princeButtons[0]) {
			a->deleteHand();
			giveCard(a, deck16);
		}
		//active player picked the inactive player
		else if (selectedButton == princeButtons[1]) {
			b->deleteHand();
			giveCard(b, deck16);
		}
	}


}

void PrincessEffect(Player* a, Player* b) {
	a->eliminate();
}