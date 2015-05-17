// Game.cpp implements the Game class found in game.h

// Game.cpp implements the Game class found in game.h

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
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
	al_destroy_font(bigFont);
	al_destroy_font(normalFont);
}

/*
* Initialises the game components.
*/
void JetMan::Game::initGame() {
	gameWindow = al_create_display(800, 600);
	eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue, al_get_display_event_source(gameWindow));
	al_set_window_title(gameWindow, "JetMan");

	root.setBounds(JetMan::Utils::Rectangle(0, 0, 800, 600));
	bigFont = al_load_ttf_font("assets/fonts/arial.ttf", 72, NULL);
	normalFont = al_load_ttf_font("assets/fonts/arial.ttf", 20, NULL);
	title = new JetMan::Graphics::Label("JetMan", bigFont);
	title->setPosition(250, 0);
	title->setColour(al_map_rgb(0, 100, 255));
	root.addWidget(title);
	soundManager.playSound(JetMan::Utils::SoundManager::INTRO, ALLEGRO_PLAYMODE_BIDIR);
}

/*
* The main game loop.
*/
int JetMan::Game::loop() {
	al_draw_bitmap(imageManager.getImage(JetMan::Utils::ImageManager::BACKGROUND), 0, 0, NULL);
	root.draw();
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