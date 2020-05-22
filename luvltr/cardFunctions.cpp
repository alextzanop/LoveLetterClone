//couldn't get it to work separately from source.cpp.
//Want to get back to it in the future

/**#include "cardFunctions.h"
#include <iostream>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "Button.h"


//a is active, b in inactive

void BaronEffect(Player* a, Player* b) {
	std::cout << "Baron\n";
}
void CountessEffect(Player* a, Player* b) {
	std::cout << "Countess\n";
}
void GuardEffect(Player* a, Player* b) {
	//text
	/**int n = 0;
	std::cout << "Pick a number between 2 and 8";
	std::cin >> n;
	while (n < 2 or n > 8) {
		std::cout << "I said, between 2 and 8";
		std::cin >> n;
	};

	if (b->getButtons()[0] && b->getButtons()[0]->getNum() == n || b->getButtons()[1] && b->getButtons()[1]->getNum() == n)
		std::cout << "Player " << b->getName() << " is dead!\n";
	
	//bitmaps
	Button two = Button("guardButton", "guardTwo", al_load_bitmap("two.jpg"), 20, 20, 64, 64);
	al_draw_bitmap(two.getFace(), two.getX(), two.getY(), 0);



}
void HandmaidEffect(Player* a, Player* b) {
	std::cout << "Handmaid\n";
}
void KingEffect(Player* a, Player* b) {
	std::cout << "King\n";
}
void PriestEffect(Player* a, Player* b) {
	if (b->getButtons()[0]) {
		std::cout << "Player " << b->getName() << "'s hand: " << b->getButtons()[0]->getNum();
	}
	else if (b->getButtons()[1])
		std::cout << "Player " << b->getName() << "'s hand: " << b->getButtons()[1]->getNum();
	
}
void PrinceEffect(Player* a, Player* b) {
	std::cout << "Prince\n";
}

void PrincessEffect(Player* a, Player* b) {
	std::cout << a->getName() << " loses!!\n";

}**/