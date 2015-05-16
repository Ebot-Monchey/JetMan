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
	std::unordered_map<SoundTrack, ALLEGRO_SAMPLE_ID*> trackIds();
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
	enum Image {BACKGROUND};
	/*
	 * Retrieves the Bitmap linked to the Image enum.
	 */
	ALLEGRO_BITMAP* getImage(Image image);
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