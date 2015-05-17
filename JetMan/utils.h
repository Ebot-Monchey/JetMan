// utils.h contains the declarations of utility classes used in JetMan

#ifndef UTILS_H
#define UTILS_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <unordered_map>

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
			enum SoundTrack { INTRO };

			/*
			 * Plays a sound in the given playback mode.
			 */
			void playSound(SoundTrack sound, ALLEGRO_PLAYMODE mode, float volume);
		private:
			ALLEGRO_SAMPLE *introTrack;
			std::unordered_map<SoundTrack, ALLEGRO_SAMPLE_ID*> trackIds;
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
			enum Image { BACKGROUND };
			/*
			 * Retrieves the Bitmap linked to the Image enum.
			 */
			ALLEGRO_BITMAP* getImage(Image image);
		private:
			ALLEGRO_BITMAP* background;
		};

		/*
		 * Used for representing the bounds of objects.
		 */
		class Rectangle {
		public:
			/*
			 * Creates a new rectangle with the given bounds.
			 */
			Rectangle(float x, float y, float width, float height);
			/*
			 * Gets the x coordinate of the rectangle.
			 */
			float getX();
			/*
			 * Sets the x coordinate of the rectangle.
			 */
			void setX(float x);
			/*
			 * Gets the x coordinate of the rectangle.
			 */
			float getY();
			/*
			 * Sets the y coordinate of the rectangle.
			 */
			void setY(float y);
			/*
			 * Gets the width of the rectangle.
			 */
			float getWidth();
			/*
			 * Sets the width of the rectangle.
			 */
			void setWidth(float width);
			/*
			 * Gets the height of the rectangle.
			 */
			float getHeight();
			/*
			 * Sets the height of the rectangle.
			 */
			void setHeight(float height);
			/*
			 * Sets the bounds of the rectangle.
			 */
			void setBounds(float x, float y, float width, float height);
			/*
			 * Determines whether two rectangles intersect or not.
			 */
			bool intersects(Rectangle rect);
		private:
			float x;
			float y;
			float width;
			float height;
		};
	}
}

#endif