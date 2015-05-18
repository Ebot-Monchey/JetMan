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
			PlayButton(Game* g) : game(g), JetMan::Graphics::Button("Play", g->normalFont) {}
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
			DemoButton(Game* g) : game(g), JetMan::Graphics::Button("Demo", g->normalFont) {}
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
			QuitButton(Game* g) : game(g), JetMan::Graphics::Button("Quit", g->normalFont) {}
			/*
			* Implements the quit button being clicked.
			*/
			void onClick();
		private:
			Game* game;
		};

		ALLEGRO_DISPLAY *gameWindow;			// The main window for outputting graphics.
		ALLEGRO_EVENT_QUEUE *eventQueue;		// The queue that holds all the events except the timer.
		ALLEGRO_EVENT_QUEUE *timerQueue;		// The queue for the timer events so that they don't starve handling of the other events.
		JetMan::Utils::SoundManager soundManager;				// The sound manager.
		JetMan::Utils::ImageManager imageManager;				// The image manager.
		ALLEGRO_TIMER* timer;					// Timer for updating at 60Fps.
		const float FPSIncrement = 1/120.0f;						// Frames per second increment (delta).
		bool shouldRun;							// Whether the game should run or not.

		JetMan::Graphics::Panel *currDisplay;	// The current display.
		ALLEGRO_FONT* bigFont;					// Font for the title of the game.
		ALLEGRO_FONT* normalFont;				// Font used for everything else.

		JetMan::Graphics::Panel mainMenu;		// The main menu screen.
		JetMan::Graphics::Label* title;			// The title of the game.
		PlayButton* play;						// The play button.
		DemoButton* demo;						// The demo button.
		QuitButton* quit;						// The quit button.

		JetMan::Graphics::Panel gameScreen;		// The game screen.
		JetMan::Graphics::InformationBox* info;	// The information display at the top of the game screen.
		JetMan::Graphics::Panel gameCanvas;		// The canvase to draw JetMan and the obstacles on.

		JetMan::Graphics::Widget* lastHover;	// The last widget the mouse hovered over.
		JetMan::Graphics::InformationBox::State state;	// The state of the game
		JetMan::Graphics::JetManSprite* jetMan;	// The main character.
		JetMan::Graphics::Wall* wall1;			// The first wall.
		JetMan::Graphics::Wall* wall2;			// The second wall
		JetMan::Graphics::Wall* wall3;			// The second wall
		JetMan::Graphics::Wall* front;			// The wall that is in front
		JetMan::Graphics::Wall* back;			// The wall that is at the very back

		int score;								// The player's score.

		/*
		 * Initialises the game components.
		 */
		void initGame();
		/*
		 * Display graphics.
		 */
		void display();
		/*
		 * Resets the game.
		 */
		void reset();
	};
}

#endif