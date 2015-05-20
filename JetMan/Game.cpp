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
	delete title;
	delete play;
	delete demo;
	delete quit;
	delete info;
	delete jetMan;
	delete wall1;
	delete wall2;
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
	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_mouse_event_source());
	al_register_event_source(eventQueue, al_get_keyboard_event_source());

	
	bigFont = al_load_ttf_font("assets/fonts/arial.ttf", 72, NULL);
	normalFont = al_load_ttf_font("assets/fonts/arial.ttf", 20, NULL);

	mainMenu.setBounds(JetMan::Graphics::Rectangle(0, 0, 800, 600));
	title = new JetMan::Graphics::Label("JetMan", bigFont);
	title->setPosition(260, 100);
	title->setColour(al_map_rgb(7, 70, 70));
	mainMenu.addWidget(title);

	play = new JetMan::Game::PlayButton(this);
	play->setPosition(360, 250);
	mainMenu.addWidget(play);
	demo = new JetMan::Game::DemoButton(this);
	demo->setPosition(360, 300);
	mainMenu.addWidget(demo);
	quit = new JetMan::Game::QuitButton(this);
	quit->setPosition(360, 350);
	mainMenu.addWidget(quit);

	gameScreen.setBounds(JetMan::Graphics::Rectangle(0, 0, 800, 600));
	info = new JetMan::Graphics::InformationBox(800, 100, normalFont);
	gameScreen.addWidget(info);
	gameCanvas.setBounds(JetMan::Graphics::Rectangle(0, 100, 800, 500));
	
	jetMan = new JetMan::Graphics::JetManSprite(imageManager.getImage(JetMan::Utils::ImageManager::JETMAN));
	jetMan->setPosition(50, 250);
	gameCanvas.addWidget(jetMan);
	wall1 = new JetMan::Graphics::Wall(imageManager.getImage(JetMan::Utils::ImageManager::WALL), 1);
	wall1->setPosition(480, 100);
	wall1->setVelocityX(-70);
	gameScreen.addWidget(wall1);
	wall2 = new JetMan::Graphics::Wall(imageManager.getImage(JetMan::Utils::ImageManager::WALL), 2);
	wall2->setPosition(980, 100);
	wall2->setVelocityX(-70);
	gameScreen.addWidget(wall2);
	wall3 = new JetMan::Graphics::Wall(imageManager.getImage(JetMan::Utils::ImageManager::WALL), 3);
	wall3->setPosition(1460, 100);
	wall3->setVelocityX(-70);
	gameScreen.addWidget(wall3);
	gameScreen.addWidget(&gameCanvas);

	front = wall1;
	back = wall3;

	soundManager.playSound(JetMan::Utils::SoundManager::SAD_PIANO, ALLEGRO_PLAYMODE_BIDIR, 0.6);
	state = JetMan::Graphics::InformationBox::OVER;

	score = 0;
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
	bool redraw = false;

	float spaceStartHold = 0;
	float spaceLengthHeld = 0;

	while (shouldRun) {
		al_wait_for_event(eventQueue, &nextEvent);

		if (nextEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			shouldRun = false;
		}
		else if (nextEvent.type == ALLEGRO_EVENT_MOUSE_AXES) {
			JetMan::Graphics::Rectangle mouse(nextEvent.mouse.x, nextEvent.mouse.y, 2, 2);
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
			JetMan::Graphics::Rectangle mouse(nextEvent.mouse.x, nextEvent.mouse.y, 2, 2);
			currDisplay->onMouseClick(mouse);
		}
		else if (nextEvent.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (nextEvent.keyboard.keycode == ALLEGRO_KEY_SPACE) {
				if (currDisplay == &(gameScreen)) {
					if (state == JetMan::Graphics::InformationBox::ACTIVE) {
						spaceStartHold = al_current_time();
					}
				}
			}
		}
		else if (nextEvent.type == ALLEGRO_EVENT_KEY_UP) {
			if (currDisplay == &(gameScreen)) {
				if (nextEvent.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					if (state == JetMan::Graphics::InformationBox::ACTIVE) {
						// Pause the game
						state = JetMan::Graphics::InformationBox::PAUSED;
						info->setState(state);
						soundManager.stopSound(JetMan::Utils::SoundManager::MISSION_IMPOSSIBLE);
					}
					else {
						// return to main menu
						if (state == JetMan::Graphics::InformationBox::DEMO) {
							soundManager.stopSound(JetMan::Utils::SoundManager::MISSION_IMPOSSIBLE);
						}
						soundManager.playSound(JetMan::Utils::SoundManager::SAD_PIANO, ALLEGRO_PLAYMODE_BIDIR, 0.6);
						state = JetMan::Graphics::InformationBox::OVER;
						info->setState(state);
						currDisplay = &(mainMenu);
					}
				}
				else if (nextEvent.keyboard.keycode == ALLEGRO_KEY_ENTER) {
					if (state == JetMan::Graphics::InformationBox::PAUSED) {
						soundManager.playSound(JetMan::Utils::SoundManager::MISSION_IMPOSSIBLE, ALLEGRO_PLAYMODE_BIDIR, 0.6);
						state = JetMan::Graphics::InformationBox::ACTIVE;
						info->setState(state);
					}
					else if (state == JetMan::Graphics::InformationBox::OVER) {
						soundManager.playSound(JetMan::Utils::SoundManager::MISSION_IMPOSSIBLE, ALLEGRO_PLAYMODE_BIDIR, 0.6);
						state = JetMan::Graphics::InformationBox::ACTIVE;
						info->setState(state);
						reset();
					}
				}
				else if (nextEvent.keyboard.keycode == ALLEGRO_KEY_SPACE) {
					if (currDisplay == &(gameScreen)) {
						if (state == JetMan::Graphics::InformationBox::ACTIVE) {
							spaceLengthHeld = al_current_time() - spaceStartHold;
							if (spaceLengthHeld > 0.2f) {
								jetMan->setVelocityY(-120);
							}
							else {
								jetMan->setVelocityY(-50);
							}
						}
					}
				}
			}
		}
		else if (nextEvent.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
			// Timer event - Update game here
			if (state == JetMan::Graphics::InformationBox::DEMO) {
				// AI for the demo part of the game
				demoMove();
			}

			if (state != JetMan::Graphics::InformationBox::PAUSED && state != JetMan::Graphics::InformationBox::OVER) {
				jetMan->update(FPSIncrement);
				wall1->update(FPSIncrement);
				wall2->update(FPSIncrement);
				wall3->update(FPSIncrement);

				JetMan::Graphics::Rectangle jetManBounds = jetMan->getBounds();
				if (jetManBounds.getY() < 100) {
					jetManBounds.setY(100);
					jetMan->setBounds(jetManBounds);
					jetMan->setVelocityY(0);
				}

				if (jetManBounds.getY() > 600 - jetManBounds.getHeight()) {
					// Crashed down.
					if (state == JetMan::Graphics::InformationBox::DEMO) {
						soundManager.stopSound(JetMan::Utils::SoundManager::MISSION_IMPOSSIBLE);
						soundManager.playSound(JetMan::Utils::SoundManager::CRASH, ALLEGRO_PLAYMODE_ONCE, 0.6);
						soundManager.playSound(JetMan::Utils::SoundManager::MISSION_IMPOSSIBLE, ALLEGRO_PLAYMODE_BIDIR, 0.6);
						reset();
					}
					else {
						state = JetMan::Graphics::InformationBox::OVER;
						info->setState(state);
						soundManager.stopSound(JetMan::Utils::SoundManager::MISSION_IMPOSSIBLE);
						soundManager.playSound(JetMan::Utils::SoundManager::CRASH, ALLEGRO_PLAYMODE_ONCE, 0.6);
					}
				}
				else if ((wall1->collides(jetManBounds)) || (wall2->collides(jetManBounds)) || (wall3->collides(jetManBounds))) {
					// Collided with a wall.
					if (state == JetMan::Graphics::InformationBox::DEMO) {
						soundManager.stopSound(JetMan::Utils::SoundManager::MISSION_IMPOSSIBLE);
						soundManager.playSound(JetMan::Utils::SoundManager::CRASH, ALLEGRO_PLAYMODE_ONCE, 0.6);
						soundManager.playSound(JetMan::Utils::SoundManager::MISSION_IMPOSSIBLE, ALLEGRO_PLAYMODE_BIDIR, 0.6);
						reset();
					}
					else {
						state = JetMan::Graphics::InformationBox::OVER;
						info->setState(state);
						soundManager.stopSound(JetMan::Utils::SoundManager::MISSION_IMPOSSIBLE);
						soundManager.playSound(JetMan::Utils::SoundManager::CRASH, ALLEGRO_PLAYMODE_ONCE, 0.6);
					}
				}
				else {
					JetMan::Graphics::Rectangle* w1 = &front->getBounds();
					if (w1->getX() < -w1->getWidth()) {
						score++;
						info->updateScore(score);
						w1->setX(back->getBounds().getX() + 3 * w1->getWidth() + 20);
						front->setBounds(*w1);
						front->updateGap();
						back = front;
						if (front == wall1) {
							front = wall2;
						}
						else if (front == wall2) {
							front = wall3;
						}
						else {
							front = wall1;
						}
					}
				}
			}
		}

		if (redraw && al_is_event_queue_empty(eventQueue)) {
			// Update the display
			redraw = false;
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
 * Implements the play button being clicked.
 */
void JetMan::Game::PlayButton::onClick() {
	game->state = JetMan::Graphics::InformationBox::ACTIVE;
	game->info->setState(game->state);
	game->currDisplay = &game->gameScreen;
	game->soundManager.stopSound(JetMan::Utils::SoundManager::SAD_PIANO);
	game->soundManager.playSound(JetMan::Utils::SoundManager::MISSION_IMPOSSIBLE, ALLEGRO_PLAYMODE_BIDIR, 0.6);
	game->reset();
}

/*
 * Implements the demo button being clicked.
 */
void JetMan::Game::DemoButton::onClick() {
	game->state = JetMan::Graphics::InformationBox::DEMO;
	game->info->setState(game->state);
	game->currDisplay = &game->gameScreen;
	game->soundManager.stopSound(JetMan::Utils::SoundManager::SAD_PIANO);
	game->soundManager.playSound(JetMan::Utils::SoundManager::MISSION_IMPOSSIBLE, ALLEGRO_PLAYMODE_BIDIR, 0.6);
	game->reset();
}

/*
 * Implements the quit button being clicked.
 */
void JetMan::Game::QuitButton::onClick() {
	game->shouldRun = false;
}

/*
 * Resets the game.
 */
void JetMan::Game::reset() {
	jetMan->setPosition(50, 250);
	jetMan->setVelocityY(0);
	score = 0;
	info->updateScore(score);
	wall1->setPosition(480, 100);
	wall2->setPosition(980, 100);
	wall3->setPosition(1460, 100);
	front = wall1;
	back = wall3;
}

/*
 * Simulated AI to decide whether the robot should move or not.
 */
void JetMan::Game::demoMove() {
	JetMan::Graphics::Rectangle nextWallBounds = front->getBounds();
	JetMan::Graphics::Rectangle jetManBounds = jetMan->getBounds();

	int gapY = 100 + 100 * front->getGapPosition();			// The y position of the gap.
	if (jetManBounds.getY() < gapY) {
		// JetMan is above the gap position - Let gravity pull him down
	}
	else if (jetManBounds.getY()> gapY + nextWallBounds.getHeight()) {
		// JetMan is below the gap position
		jetMan->setVelocityY(-120);
	}
	else {
		// JetMan is line up in between the gap - Do little jump when he gets to a certain y coordinate just above the wall.
		if (jetManBounds.getY() + jetManBounds.getHeight() > gapY + nextWallBounds.getHeight() - 10) {
			jetMan->setVelocityY(-50);
		}
	}
}