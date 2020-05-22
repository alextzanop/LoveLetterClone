#include "Card.h"


Card::Card() {

}
//constructors
Card::Card(const char* name, int num) {
	this->name = name;
	this->num = num;
}
Card::Card(const char* name, int num, ALLEGRO_BITMAP* face) {
	this->name = name;
	this->num  = num;
	this->face = face;
}
Card::Card(const char* name, int num, ALLEGRO_BITMAP* face, std::function<void(Player*, Player*)> onClick) {
	this->name = name;
	this->num = num;
	this->face = face;
	this->onClick = onClick;
}


Card::Card(const char* name, int num, ALLEGRO_BITMAP* face, int x, int y) {
	this->name = name;
	this->num = num;
	this->x = x;
	this->y = y;
	this->face = face;
}

//card's function
std::function<void(Player*, Player*)> Card::getFunc() {
	return this->onClick;
}

//getters 
const char* Card::getName() {
	return this->name;
}

int Card::getNum() {
	return this->num;
}

ALLEGRO_BITMAP* Card::getFace() {
	return this->face;
}

int Card::getX() {
	return this->x;
}

int Card::getY() {
	return this->y;
}

int Card::getWidth() {
	return this->width;
}

int Card::getHeight() {
	return this->height;
}

//setters

void Card::setX(int x) {
	this->x = x;
}

void Card::setY(int y) {
	this->y = y;
}

void Card::setWidth(int width) {
	this->width = width;
}

void Card::setHeight(int heigth) {
	this->height = heigth;
}

