// game.h contains the declarations for the classes used to create JetMan

#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro.h>

/*
 * Used for representing the bounds of objects.
 */
class Rectangle {
public:
	/*
	 * Creates a new rectangle with the given bounds.
	 */
	Rectangle(float x, float y, float width, float height);
	/*
	 * Gets the x coordinate of the rectangle.
	 */
	float getX();
	/*
	 * Sets the x coordinate of the rectangle.
	 */
	void setX(float x);
	/*
	 * Gets the x coordinate of the rectangle.
	 */
	float getY();
	/*
	 * Sets the y coordinate of the rectangle.
	 */
	void setY(float y);
	/*
	 * Gets the width of the rectangle.
	 */
	float getWidth();
	/*
	 * Sets the width of the rectangle.
	 */
	void setWidth(float width);
	/*
	 * Gets the height of the rectangle.
	 */
	float getHeight();
	/*
	 * Sets the height of the rectangle.
	 */
	void setHeight(float height);
	/*
	 * Sets the bounds of the rectangle.
	 */
	void setBounds(float x, float y, float width, float height);
	/*
	 * Determines whether two rectangles intersect or not.
	 */
	bool intersects(Rectangle rect);
};

/*
 * The main game class.
 */
class Game {
public:
	/*
	 * Makes the calls to initialise allegro and sets up the game components.
	 */
	Game();
	/*
	 * Frees up memory allocated.
	 */
	~Game();
	/*
	 * The main game loop.
	 */
	int loop();
private:
	ALLEGRO_DISPLAY *gameWindow;			// The main window for outputting graphics.
	ALLEGRO_EVENT_QUEUE *eventQueue;		// The queue that holds all the events.

	/*
	 * Initialises all the Allegro components needed.
	 */
	void initAllegro();
	/*
	 * Initialises the game components.
	 */
	void initGame();
};

#endif