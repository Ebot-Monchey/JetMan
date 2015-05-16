// game.h contains the declarations for the classes used to create JetMan

#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <unordered_map>

/*
* Handles the sound loading and playing.
*/
class SoundManager {
public:
	/*
	* Initilaises the sound manager and loads all the resources.
	*/
	SoundManager();
	/*
	* Cleans up allocated resources.
	*/
	~SoundManager();
	/*
	* The different sounds that can be played.
	*/
	enum SoundTrack { INTRO };

	/*
	* Plays a sound in the given playback mode.
	*/
	void playSound(SoundTrack sound, ALLEGRO_PLAYMODE mode);
private:
	ALLEGRO_SAMPLE *introTrack;
	//std::unordered_map<SoundTrack, ALLEGRO_SAMPLE_ID*> trackIds();
};

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

	/*
	* Initialises the game components.
	*/
	void initGame();
};

#endif