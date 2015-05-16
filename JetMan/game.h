// game.h contains the declarations for the classes used to create JetMan

#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro.h>
#include "utils.h"

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
	SoundManager soundManager;				// The sound manager.
	ImageManager imageManager;				// The image manager.

	/*
	 * Initialises the game components.
	 */
	void initGame();
};

#endif