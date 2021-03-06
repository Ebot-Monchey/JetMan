// Utils.cpp implements the SoundManager utility class
#include <allegro5\allegro.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include "utils.h"

// =========================Sound Manager==================================
/*
 * Initilaises the sound manager and loads all the resources.
 */
JetMan::Utils::SoundManager::SoundManager() {
	al_reserve_samples(2);
	sadPiano = al_load_sample("assets/sounds/Sad Piano.ogg");
	missionImpossible = al_load_sample("assets/sounds/Mission Impossible.ogg");
	crash = al_load_sample("assets/sounds/crash.wav");
}

/*
 * Frees allocated memory.
 */
JetMan::Utils::SoundManager::~SoundManager() {
	al_destroy_sample(sadPiano);
	al_destroy_sample(missionImpossible);
	al_destroy_sample(crash);
}

/*
 * Plays a sound file.
 */
void JetMan::Utils::SoundManager::playSound(JetMan::Utils::SoundManager::SoundTrack sound, ALLEGRO_PLAYMODE mode, float volume) {
	if (sound == SAD_PIANO) {
		al_play_sample(sadPiano, volume, 0.0, 1.0, mode, &sadPianoId);
	}
	else if (sound == MISSION_IMPOSSIBLE) {
		al_play_sample(missionImpossible, volume, 0.0, 1.0, mode, &missionImpossibleId);
	}
	else if (sound == CRASH) {
		al_play_sample(crash, volume, 0.0, 1.0, mode, &crashId);
	}
}

/*
 * Stops playing the sound. Usually for sound tracks that are played in a loop.
 */
void JetMan::Utils::SoundManager::stopSound(JetMan::Utils::SoundManager::SoundTrack sound) {
	if (sound == SAD_PIANO) {
		al_stop_sample(&sadPianoId);
	}
	else if (sound == MISSION_IMPOSSIBLE) {
		al_stop_sample(&missionImpossibleId);
	}
	else if (sound == CRASH) {
		al_stop_sample(&crashId);
	}
}

// ===================ImageManager============================
/*
 * Initialises the image manager and loads all the resources.
 */
JetMan::Utils::ImageManager::ImageManager() {
	background = al_load_bitmap("assets/images/background.jpg");
	jetMan = al_load_bitmap("assets/images/jetman.png");
	wall = al_load_bitmap("assets/images/wall.png");
}

/*
 * Frees memory allocated to image resources.
 */
JetMan::Utils::ImageManager::~ImageManager() {
	al_destroy_bitmap(background);
	al_destroy_bitmap(jetMan);
	al_destroy_bitmap(wall);
}

/*
 * Gets the image associated with the enum.
 */
ALLEGRO_BITMAP* JetMan::Utils::ImageManager::getImage(JetMan::Utils::ImageManager::Image image) {
	switch (image) {
	case BACKGROUND:
		return background;
		break;
	case JETMAN:
		return jetMan;
		break;
	case WALL:
		return wall;
		break;
	default:
		return NULL;
	}
}