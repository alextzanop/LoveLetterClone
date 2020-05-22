#ifndef CARD_H
#define CARD_H
#include"allegro5/allegro.h"
#include <functional>

class Player;

class Card
{
	private:
		const char* name;
		int num;
		int x;
		int y;
		int width;
		int height;
		ALLEGRO_BITMAP* face;
		std::function<void(Player*, Player*)> onClick;


	public:
		//constructors
		Card();
		Card(const char* name, int num);
		Card(const char* name, int num, ALLEGRO_BITMAP* face);
		Card(const char* name, int num, ALLEGRO_BITMAP* face, std::function<void(Player*, Player*)> onClick);
		Card(const char* name, int num, ALLEGRO_BITMAP* face, int x, int y);
		//getters
		const char* getName();
		int getNum();
		int getX();
		int getY();
		int getWidth();
		int getHeight();
		ALLEGRO_BITMAP* getFace();
		//setters
		void setX(int x);
		void setY(int y);
		void setWidth(int x);
		void setHeight(int x);
		//card's function
		std::function<void(Player*, Player*)> getFunc();
};

#endif /* CARD_H */