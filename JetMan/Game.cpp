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
	al_destroy_event_queue(timerQueue);
	al_destroy_timer(timer);
	al_destroy_font(bigFont);
	al_destroy_font(normalFont);
	delete(title);
	delete(play);
	delete(demo);
	delete(quit);
}

/*
* Initialises the game components.
*/
void JetMan::Game::initGame() {
	gameWindow = al_create_display(800, 600);
	eventQueue = al_create_event_queue();
	timerQueue = al_create_event_queue();
	al_register_event_source(eventQueue, al_get_display_event_source(gameWindow));
	al_set_window_title(gameWindow, "JetMan");
	timer = al_create_timer(1 / ((double)60));
	al_register_event_source(timerQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_mouse_event_source());

	
	bigFont = al_load_ttf_font("assets/fonts/arial.ttf", 72, NULL);
	normalFont = al_load_ttf_font("assets/fonts/arial.ttf", 20, NULL);

	mainMenu.setBounds(JetMan::Utils::Rectangle(0, 0, 800, 600));
	title = new JetMan::Graphics::Label("JetMan", bigFont);
	title->setPosition(250, 0);
	title->setColour(al_map_rgb(0, 100, 255));
	mainMenu.addWidget(title);

	play = new JetMan::Game::PlayButton(this);
	play->setPosition(350, 150);
	mainMenu.addWidget(play);
	demo = new JetMan::Game::DemoButton(this);
	demo->setPosition(350, 200);
	mainMenu.addWidget(demo);
	quit = new JetMan::Game::QuitButton(this);
	quit->setPosition(350, 250);
	mainMenu.addWidget(quit);

	soundManager.playSound(JetMan::Utils::SoundManager::INTRO, ALLEGRO_PLAYMODE_BIDIR);

	lastHover = nullptr;
	shouldRun = true;
	currDisplay = &mainMenu;
	al_start_timer(timer);
}

/*
* The main game loop.
*/
int JetMan::Game::loop() {
	ALLEGRO_EVENT nextEvent;
	int nUpdates = 0;
	bool hasNext;
	while (shouldRun) {
		hasNext = al_get_next_event(eventQueue, &nextEvent);
		if (hasNext) {
			if (nextEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				shouldRun = false;
			}
			else if (nextEvent.type == ALLEGRO_EVENT_MOUSE_AXES) {
				JetMan::Utils::Rectangle mouse(nextEvent.mouse.x, nextEvent.mouse.y, 2, 2);
				if (lastHover != nullptr) {
					if (!lastHover->getBounds().intersects(mouse)) {
						lastHover->onMouseOut();
						lastHover = currDisplay->onMouseOver(mouse);
					}
					else {
						lastHover = lastHover->onMouseOver(mouse);
					}
				}
				else {
					lastHover = currDisplay->onMouseOver(mouse);
				}
			}
			else if (nextEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				JetMan::Utils::Rectangle mouse(nextEvent.mouse.x, nextEvent.mouse.y, 2, 2);
				currDisplay->onMouseClick(mouse);
			}
		}
		hasNext = al_get_next_event(timerQueue, &nextEvent);
		if (hasNext) {
			// Timer event - Update game here
			nUpdates++;
		}

		if (nUpdates == 10) {
			// Display at 30 fps
			nUpdates = 0;
			display();
		}
	}
	return 0;
}

/*
 * Display the graphics.
 */
void JetMan::Game::display() {
	al_draw_bitmap(imageManager.getImage(JetMan::Utils::ImageManager::BACKGROUND), 0, 0, NULL);
	currDisplay->draw();
	al_flip_display();
}

/*
 * Constructor for the play button
 */
JetMan::Game::PlayButton::PlayButton(JetMan::Game* g) : game(g), JetMan::Graphics::Button("Play", g->normalFont) {

}

/*
 * Implements the play button being clicked.
 */
void JetMan::Game::PlayButton::onClick() {
	
}

/*
 * Constructor for the demo button
 */
JetMan::Game::DemoButton::DemoButton(JetMan::Game* g) : game(g), JetMan::Graphics::Button("Demo", g->normalFont) {

}

/*
 * Implements the demo button being clicked.
 */
void JetMan::Game::DemoButton::onClick() {
	
}

/*
 * Constructor for the quit button
 */
JetMan::Game::QuitButton::QuitButton(JetMan::Game* g) : game(g), JetMan::Graphics::Button("Quit", g->normalFont) {

}

/*
 * Implements the quit button being clicked.
 */
void JetMan::Game::QuitButton::onClick() {
	game->shouldRun = false;
}