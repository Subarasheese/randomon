#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <SDL.h>

// Initialize the game
bool game_init(SDL_Window *window);

// Main game loop
void game_run();

// Clean up resources
void game_cleanup();

#endif // GAME_H
