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
		/*
		 * Helper class for buttons.
		 */
		class PlayButton : public JetMan::Graphics::Button {
		public:
			PlayButton(Game* g);
			/*
			 * Implements the play button being clicked.
			 */
			void onClick();
		private:
			Game* game;
		};

		/*
		 * Helper class for the demo button.
		 */
		class DemoButton : public JetMan::Graphics::Button {
		public:
			DemoButton(Game* g);
			/*
			* Implements the demo button being clicked.
			*/
			void onClick();
		private:
			Game* game;
		};

		/*
		* Helper class for buttons.
		*/
		class QuitButton : public JetMan::Graphics::Button {
		public:
			QuitButton(Game* g);
			/*
			* Implements the quit button being clicked.
			*/
			void onClick();
		private:
			Game* game;
		};

		ALLEGRO_DISPLAY *gameWindow;			// The main window for outputting graphics.
		ALLEGRO_EVENT_QUEUE *eventQueue;		// The queue that holds all the events.
		JetMan::Utils::SoundManager soundManager;				// The sound manager.
		JetMan::Utils::ImageManager imageManager;				// The image manager.
		ALLEGRO_TIMER* timer;					// Timer for updating at 60Fps.
		bool shouldRun;							// Whether the game should run or not.

		JetMan::Graphics::Panel *currDisplay;	// The current display.
		ALLEGRO_FONT* bigFont;					// Font for the title of the game.
		ALLEGRO_FONT* normalFont;				// Font used for everything else.
		JetMan::Graphics::Panel mainMenu;		// The main menu screen.
		JetMan::Graphics::Label* title;			// The title of the game.
		PlayButton* play;						// The play button.
		DemoButton* demo;						// The demo button.
		QuitButton* quit;						// The quit button.

		JetMan::Graphics::Widget* lastHover;	// The last widget the mouse hovered over.
		/*
		 * Initialises the game components.
		 */
		void initGame();
		/*
		 * Display graphics.
		 */
		void display();
	};
}

#endif