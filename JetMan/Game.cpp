// Game.cpp implements the Game class found in game.h

#include <allegro5/allegro.h>
#include "game.h"

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