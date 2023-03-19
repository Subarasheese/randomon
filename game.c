#include <stdbool.h>
#include "game.h"
#include "graphics.h"
#include "audio.h"

// Global variables
SDL_Renderer *g_renderer = NULL;
bool g_running = false;

// Function prototypes
static void process_events();
static void update();
static void render();

// Initialize the game
bool game_init(SDL_Window *window) {
    // Initialize the renderer
    g_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (g_renderer == NULL) {
        fprintf(stderr, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Initialize graphics and audio
    if (!graphics_init() || !audio_init()) {
        return false;
    }

    // Start the game
    g_running = true;

    return true;
}

// Main game loop
void game_run() {
    while (g_running) {
        process_events();
        update();
        render();
        SDL_Delay(1000 / 60); // 60 FPS cap
    }
}

// Clean up resources
void game_cleanup() {
    audio_cleanup();
    graphics_cleanup();
    SDL_DestroyRenderer(g_renderer);
}

// Process events
static void process_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            g_running = false;
        }
    }
}

// Update game logic
static void update() {
    // Update game state here
}

// Render game
static void render() {
    // Clear the screen
    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
    SDL_RenderClear(g_renderer);

    // Render game objects here

    // Update the screen
    SDL_RenderPresent(g_renderer);
}
