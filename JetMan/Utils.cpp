// Utils.cpp implements the SoundManager utility class
#include<allegro5\allegro.h>
#include<allegro5\allegro_audio.h>
#include<allegro5\allegro_acodec.h>
#include "game.h"

/*
* Initilaises the sound manager and loads all the resources.
*/
SoundManager::SoundManager() {
	al_reserve_samples(1);
	introTrack = al_load_sample("Mission Impossible.wav");
}

SoundManager::~SoundManager() {
	al_destroy_sample(introTrack);
}

void SoundManager::playSound(SoundManager::SoundTrack sound, ALLEGRO_PLAYMODE mode) {
	if (sound == INTRO) {
		al_play_sample(introTrack, 1.0, 0.0, 1.0, mode, NULL);
	}
}