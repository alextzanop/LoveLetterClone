#ifndef BUTTON_H
#define BUTTON_H
#include "allegro5/allegro.h"
#include <functional>
#include <string>
#include "Player.h"
class Player;


//Disclaimer: Some of the following functions are not used.
class Button
{

private:
	int x; //Upper left corner X
	int y; //Upper left corner Y
	int startX;
	int startY;
	int width;
	int height;
	std::string type;
	std::string name;
	bool active;
	bool selected;
	bool clicked;
	int num;
	ALLEGRO_BITMAP* active_image;
	ALLEGRO_BITMAP* inactive_image;
	ALLEGRO_BITMAP* drawn_image;
	ALLEGRO_BITMAP* pressed_image;

	std::function<void (Player*, Player*)> onClick;

public:
	/*
	Constructor
	Params:
		xPos: x-Axis position
		yPos: y-Axis position
		width:  button width
		height: button height
	*/
	Button(std::string type, std::string name, ALLEGRO_BITMAP* face, int xPos, int yPos, int width, int height);
	Button(std::string type, std::string name, ALLEGRO_BITMAP* face, int xPos, int yPos, int width, int height, int num, std::function<void(Player* p1, Player* p2)> onClick);
	Button(std::string type, std::string name, ALLEGRO_BITMAP* face, int num, int xPos, int yPos, int width, int height);
		
	std::string getName();

	int getStartX();

	int getStartY();

	std::function<void(Player*, Player*)> getFunc();

	/*
	Description: returns the x-Axis position of the button
	Return: the x-Axis button position
	*/
	int getX();
	/*
	Description: returns the y-Axis position of the button
	Return: the y-Axis button position
	*/
	int getY();
	/*
	Description: returns the width of the button
	Return: the button's width
	*/
	int getWidth();
	/*
	Description: returns the heigth of the button
	Return: the button's height
	*/
	int getHeight();
	 
	int getNum();

	std::string getType();

	void restorePosition();

	ALLEGRO_BITMAP* getFace();

	void cardEffect(Player*, Player*);

	/*
	Description: Checks if the mouse is in bounds of the button
	Params:
		mouse_x: mouse x-Axis position
		mouse_y: mouse y-Axis position
	Return: true if mouse is in bounds, false otherwise
	*/
	bool mouseInBounds(int mouse_x, int mouse_y);

	void select();

	void unSelect();

	bool isSelected();

	/* Description: Manages the function of the button when pressed */
	void onPress();

	/* Description: Manages the function of the button when released */
	void onRelease();

	/* Description: Sets button to be inactive */
	void setInactive();

	/* Description: Sets button to active */
	void setActive(bool a);


	void setClicked(bool c);

	/*Description: Checks if button is active */
	bool isActive();

	bool isClicked();

	void resetButton();
};

#endif /* BUTTON_H */...ha...gaaayy!!

