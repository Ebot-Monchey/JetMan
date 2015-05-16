// Utils.cpp implements the SoundManager utility class
#include <allegro5\allegro.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include "utils.h"

// =========================Sound Manager==================================
/*
 * Initilaises the sound manager and loads all the resources.
 */
SoundManager::SoundManager() {
	al_reserve_samples(1);
	introTrack = al_load_sample("Mission Impossible.wav");
}

/*
 * Frees allocated memory.
 */
SoundManager::~SoundManager() {
	al_destroy_sample(introTrack);
}

/*
 * Plays a sound file.
 */
void SoundManager::playSound(SoundManager::SoundTrack sound, ALLEGRO_PLAYMODE mode) {
	if (sound == INTRO) {
		al_play_sample(introTrack, 0.4, 0.0, 1.0, mode, NULL);
	}
}

// ===================ImageManager============================
/*
 * Initialises the image manager and loads all the resources.
 */
ImageManager::ImageManager() {
	background = al_load_bitmap("background.png");
}

/*
 * Frees memory allocated to image resources.
 */
ImageManager::~ImageManager() {
	al_destroy_bitmap(background);
}

/*
 * Gets the image associated with the enum.
 */
ALLEGRO_BITMAP* ImageManager::getImage(ImageManager::Image image) {
	switch (image) {
	case BACKGROUND:
		return background;
		break;
	default:
		return NULL;
	}
}

// ========================Rectangle===============================
/*
 * Creates a new rectangle with the given bounds.
 */
Rectangle::Rectangle(float x, float y, float width, float height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

/*
 * Gets the x coordinate of the rectangle.
 */
float Rectangle::getX() {
	return x;
}

/*
 * Sets the x coordinate of the rectangle.
 */
void Rectangle::setX(float x) {
	this->x = x;
}

/*
 * Gets the y coordinate of the rectangle.
 */
float Rectangle::getY() {
	return y;
}

/*
 * Sets the y coordinate of the rectangle.
 */
void Rectangle::setY(float y) {
	this->y = y;
}

/*
 * Gets the width of the rectangle.
 */
float Rectangle::getWidth() {
	return width;
}

/*
 * Sets the width of the rectangle.
 */
void Rectangle::setWidth(float width) {
	this->width = width;
}

/*
 * Gets the height of the rectangle.
 */
float Rectangle::getHeight() {
	return height;
}

/*
 * Sets the height of the rectangle.
 */
void Rectangle::setHeight(float height) {
	this->height = height;
}

/*
 * Sets the bounds of the rectangle.
 */
void Rectangle::setBounds(float x, float y, float width, float height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

/*
 * Determines whether the rectangle intersects another rectangle.
 */
bool Rectangle::intersects(Rectangle rect) {
	if (rect.getX() > x + width) {
		return false;
	}
	else if (rect.getX() + rect.getWidth() < x) {
		return false;
	}
	else if (rect.getY() > y + height) {
		return false;
	}
	else if (rect.getY() + rect.getHeight() < y) {
		return false;
	}
	else {
		return true;
	}
}