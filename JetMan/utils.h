// utils.h contains the declarations of utility classes used in JetMan

#ifndef UTILS_H
#define UTILS_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

namespace JetMan {
	namespace Utils {
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
			enum SoundTrack { SAD_PIANO, MISSION_IMPOSSIBLE, CRASH };

			/*
			 * Plays a sound in the given playback mode.
			 */
			void playSound(SoundTrack sound, ALLEGRO_PLAYMODE mode, float volume);
			/*
			 * Stops playing the sound. Usually for sound tracks that are played in a loop.
			 */
			void stopSound(SoundTrack sound);
		private:
			ALLEGRO_SAMPLE *sadPiano;
			ALLEGRO_SAMPLE_ID sadPianoId;
			ALLEGRO_SAMPLE *missionImpossible;
			ALLEGRO_SAMPLE_ID missionImpossibleId;
			ALLEGRO_SAMPLE *crash;
			ALLEGRO_SAMPLE_ID crashId;
		};

		/*
		 * Class to handle working with images.
		 */
		class ImageManager {
		public:
			/*
			 * Creates a new ImageManager.
			 */
			ImageManager();
			/*
			 * Frees allocated memory.
			 */
			~ImageManager();
			/*
			 * The different images available.
			 */
			enum Image { BACKGROUND, JETMAN, WALL};
			/*
			 * Retrieves the Bitmap linked to the Image enum.
			 */
			ALLEGRO_BITMAP* getImage(Image image);
		private:
			ALLEGRO_BITMAP* background;
			ALLEGRO_BITMAP* jetMan;
			ALLEGRO_BITMAP* wall;
		};
	}
}

#endif