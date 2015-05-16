// Game.cpp implements the Game class found in game.h

// Game.cpp implements the Game class found in game.h

#include <allegro5/allegro.h>
#include "game.h"

/*
* Makes the calls to initialise allegro and sets up the game components.
*/
Game::Game() {
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
* Initialises the game components.
*/
void Game::initGame() {
	gameWindow = al_create_display(800, 600);
	eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue, al_get_display_event_source(gameWindow));
	al_set_window_title(gameWindow, "JetMan");
	soundManager.playSound(SoundManager::INTRO, ALLEGRO_PLAYMODE_BIDIR);
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

/*
 * Creates a new rectangle with the given bounds.
 */
Rectangle::Rectangle(float x, float y, float width, float height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

/*
 * Gets the x coordinate of the rectangle.
 */
float Rectangle::getX() {
	return x;
}

/*
 * Sets the x coordinate of the rectangle.
 */
void Rectangle::setX(float x) {
	this->x = x;
}

/*
 * Gets the y coordinate of the rectangle.
 */
float Rectangle::getY() {
	return y;
}

/*
 * Sets the y coordinate of the rectangle.
 */
void Rectangle::setY(float y) {
	this->y = y;
}

/*
 * Gets the width of the rectangle.
 */
float Rectangle::getWidth() {
	return width;
}

/*
 * Sets the width of the rectangle.
 */
void Rectangle::setWidth(float width) {
	this->width = width;
}

/*
 * Gets the height of the rectangle.
 */
float Rectangle::getHeight() {
	return height;
}

/*
 * Sets the height of the rectangle.
 */
void Rectangle::setHeight(float height) {
	this->height = height;
}

/*
 * Sets the bounds of the rectangle.
 */
void Rectangle::setBounds(float x, float y, float width, float height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

/*
 * Determines whether the rectangle intersects another rectangle.
 */
bool Rectangle::intersects(Rectangle rect) {
	if (rect.getX() > x + width) {
		return false;
	}
	else if (rect.getX() + rect.getWidth < x) {
		return false;
	}
	else if (rect.getY() > y + height) {
		return false;
	}
	else if (rect.getY() + rect.getHeight < y) {
		return false;
	}
	else {
		return true;
	}
}