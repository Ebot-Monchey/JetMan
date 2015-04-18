// Main.cpp contains the main function which is the entry point to the game


#include "game.h"

/*
 * Entry point to the game.
 */
int main(int n, char** args) {
	Game game;
	return game.loop();
}