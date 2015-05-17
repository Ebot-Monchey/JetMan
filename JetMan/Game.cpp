// Game.cpp implements the Game class found in game.h

// Game.cpp implements the Game class found in game.h

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "game.h"

/*
* Makes the calls to initialise allegro and sets up the game components.
*/
JetMan::Game::Game() {
	initGame();
}

/*
* Frees up memory allocated.
*/
JetMan::Game::~Game() {
	al_destroy_display(gameWindow);
	al_destroy_event_queue(eventQueue);
}

/*
* Initialises the game components.
*/
void JetMan::Game::initGame() {
	gameWindow = al_create_display(800, 600);
	eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue, al_get_display_event_source(gameWindow));
	al_set_window_title(gameWindow, "JetMan");
	soundManager.playSound(JetMan::Utils::SoundManager::INTRO, ALLEGRO_PLAYMODE_BIDIR);
}

/*
* The main game loop.
*/
int JetMan::Game::loop() {
	al_draw_bitmap(imageManager.getImage(JetMan::Utils::ImageManager::BACKGROUND), 0, 0, NULL);
	al_flip_display();

	ALLEGRO_EVENT nextEvent;
	while (true) {
		al_wait_for_event(eventQueue, &nextEvent);
		if (nextEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
	}
	return 0;
}