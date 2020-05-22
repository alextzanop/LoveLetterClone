#include "Button.h"
#include "Macros.h"
#include <iostream>

//Disclaimer: Some of the following functions are not used.

/*
Constructor
Params:
	xPos: x-Axis position
	yPos: y-Axis position
	width:  button width
	height: button height
*/
Button::Button(std::string type, std::string name, ALLEGRO_BITMAP* face, int xPos, int yPos, int width, int height) {
	this->x = xPos;
	this->y = yPos;
	this->startX = xPos;
	this->startY = yPos;
	this->width = width;
	this->height = height;
	this->type = type;
	this->name = name;
	this->active = true;
	this->selected = false;
	this->active_image = face;
	this->onClick = NULL;
	this->clicked = false;
}

Button::Button(std::string type, std::string name, ALLEGRO_BITMAP* face, int num, int xPos, int yPos, int width, int height) {
	this->x = xPos;
	this->y = yPos;
	this->startX = xPos;
	this->startY = yPos;
	this->width = width;
	this->height = height;
	this->type = type;
	this->name = name;
	this->active = true;
	this->selected = false;
	this->active_image = face;
	this->onClick = NULL;
	this->clicked = false;
	this->num = num;
}

Button::Button(std::string type, std::string name, ALLEGRO_BITMAP* face, int xPos, int yPos, int width, int height, int num, std::function<void(Player*, Player*)> onClick) {
	this->x = xPos;
	this->y = yPos;
	this->width = width;
	this->height = height;
	this->type = type;
	this->name = name;
	this->active = true;
	this->selected = false;
	this->active_image = face;
	this->onClick = onClick;
	this->num = num;
	this->clicked = false;
}

std::function<void(Player*, Player*)> Button::getFunc() {
	return this->onClick;
}

void Button::cardEffect(Player* p1, Player* p2) {
	std::cout << "PLAYED " << this->getName()<<": \n";
	this->onClick(p1, p2);
}

std::string Button::getName() {
	return this->name;
}

int Button::getStartX() {
	return this->startX;
}

int Button::getStartY() {
	return this->startY;
}

/*
Description: returns the x-Axis position of the button
Return: the x-Axis button position
*/
int Button::getX() {
	return this->x;
}
/*
Description: returns the y-Axis position of the button
Return: the y-Axis button position
*/
int Button::getY() {
	return this->y;
}
/*
Description: returns the width of the button
Return: the button's width
*/
int Button::getWidth() {
	return this->width;
}
/*
Description: returns the heigth of the button
Return: the button's height
*/
int Button::getHeight() {
	return this->height;
}

ALLEGRO_BITMAP* Button::getFace() {
	return this->active_image;
}

int Button::getNum() {
	return this->num;
}

/*
Description: Checks if the mouse is in bounds of the button
Params:
	mouse_x: mouse x-Axis position
	mouse_y: mouse y-Axis position
Return: 1 if mouse is in bounds, 0 otherwise
*/
bool Button::mouseInBounds(int mouse_x, int mouse_y) {
	return(
		(this->x <= mouse_x && mouse_x <= this->x + this->width) && //x-Axis
		(this->y <= mouse_y && mouse_y <= this->y + this->height)	//y-Axis
		);
}

/* Description: Manages the function of the button when pressed */
void Button::onPress() {
	if(this->active)
		this->selected = true;
}

void Button::restorePosition() {
	if (this->y == TOP_Y + 20)
		this->y = TOP_Y;
	else if (this->y == BOT_Y - 20)
		this->y = BOT_Y;
	//this->unSelect();
	this->setClicked(false);
}


/* Description: Manages the function of the button when released */
void Button::onRelease() {
	int dy = 20;
	if (this->selected) {
		//moves the button to declare it's been selected
		if (this->type == "card") {
			
			//top cards
			if (this->y == TOP_Y) {
				this->y += dy;
			}
			//bot cards
			else if (this->y == BOT_Y) {
				this->y -= dy;
			}
			//top clicked
			else if (this->y == TOP_Y + dy) {
				this->y -= 20;
				this->selected = false;
			}
			//bot clicked
			else if (this->y == BOT_Y - dy) {
				this->y += dy;
				this->selected = false;
			}
			
		}

		else if (this->type == "play") {
			
			this->selected = false;
		}

		else if (this->type == "guardButton" || this->type == "princeButton") {
			if (this->y == startY)
				this->y -= dy;
			else
				this->y = startY;
		}
	}
}

/* Description: Sets button to be inactive */
void Button::setInactive() {
	this->active = false;
	this->drawn_image = this->inactive_image;
}

void Button::select() {
	this->selected = true;
}

void Button::unSelect() {
	this->selected = false;
	this->restorePosition();
}

bool Button::isSelected() {
	return this->selected;
}


void Button::setClicked(bool c) {
	this->clicked = c;
}


/* Description: Sets button to active */
void Button::setActive(bool a) {
	this->active = a;
	//this->drawn_image = this->active_image;
}

/*Description: Checks if button is active */
bool Button::isActive() {
	return this->active;
}

bool Button::isClicked() {
	return this->clicked;
}


std::string Button::getType() {
	return this->type;
}

void Button::resetButton() {
	this->x = this->startX;
	this->y = this->startY;
	this->active = true;
	this->selected = false;
	this->clicked = false;
	
}