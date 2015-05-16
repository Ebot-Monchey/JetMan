// Main.cpp contains the main function which is the entry point to the game


// Main.cpp contains the main function which is the entry point to the game

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "game.h"

void initAllegro() {
	bool init = true;
	if (!al_init()) {
		init = false;
	}
	if (!al_install_keyboard()) {
		init = false;
	}
	if (!al_install_audio()) {
		init = false;
	}
	if (!al_init_acodec_addon()) {
		init = false;
	}
	if (!init) {
		throw "Could not fully initialise Allegro 5";
	}
}

/*
* Entry point to the game.
*/
int main(int n, char** args) {
	initAllegro();
	Game game;
	return game.loop();
}