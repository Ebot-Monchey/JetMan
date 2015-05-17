// game.h contains the declarations for the classes used to create JetMan

#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "utils.h"
#include "graphics.h"

namespace JetMan {
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
		JetMan::Utils::SoundManager soundManager;				// The sound manager.
		JetMan::Utils::ImageManager imageManager;				// The image manager.
		ALLEGRO_FONT* bigFont;					// Font for the title of the game.
		ALLEGRO_FONT* normalFont;				// Font used for everything else.
		JetMan::Graphics::Panel root;			// The root of all the widgets.
		JetMan::Graphics::Label* title;			// The title of the game.
		/*
		 * Initialises the game components.
		 */
		void initGame();
	};
}

#endif