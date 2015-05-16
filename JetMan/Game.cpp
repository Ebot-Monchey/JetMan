// Game.cpp implements the Game class found in game.h

#include <allegro5/allegro.h>
#include "game.h"

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
 * Makes the calls to initialise allegro and sets up the game components.
 */
Game::Game() {
	initAllegro();
	initGame();
}

/*
 * Frees up memory allocated.
 */
Game::~Game() { 
	al_destroy_display(gameWindow);
	al_destroy_event_queue(eventQueue);
}

/*
 * Initialises all the Allegro components needed.
 */
void Game::initAllegro() {
	bool init = true;
	if (!al_init()) {
		init = false;
	}
	if (!al_install_keyboard()) {
		init = false;
	}
	if (!init) {
		throw "Could not fully initialise Allegro 5";
	}
}

/*
 * Initialises the game components.
 */
void Game::initGame() {
	gameWindow = al_create_display(800, 600);
	eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue, al_get_display_event_source(gameWindow));
	al_set_window_title(gameWindow, "JetMan");
}

/*
 * The main game loop.
 */
int Game::loop() {
	ALLEGRO_EVENT nextEvent;
	while (true) {
		al_wait_for_event(eventQueue, &nextEvent);
		if (nextEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
	}
	return 0;
}