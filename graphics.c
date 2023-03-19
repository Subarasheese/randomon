#include <stdbool.h>
#include "graphics.h"
#include "game.h"

// Function prototypes
static bool load_assets();

// Initialize graphics
bool graphics_init() {
    // Load assets
    if (!load_assets()) {
        fprintf(stderr, "Failed to load assets!\n");
        return false;
    }

    return true;
}

// Load assets
static bool load_assets() {
    // Load textures, sprites, and other graphical assets here
    // Return false if any loading fails

    return true;
}

// Clean up resources
void graphics_cleanup() {
    // Free textures, sprites, and other graphical assets here
}

void render_background(SDL_Rect *camera) {
    // Render the background with the camera's position offset
    // ...
    SDL_Rect dest = {bg.x - camera->x, bg.y - camera->y, bg.width, bg.height};
    SDL_RenderCopy(g_renderer, bg.texture, NULL, &dest);
}

void render_player(SDL_Rect *camera) {
    // Render the player with the camera's position offset
    // ...
    SDL_Rect dest = {player.x - camera->x, player.y - camera->y, player.width, player.height};
    SDL_RenderCopy(g_renderer, player.texture, NULL, &dest);
}

void render_enemies(SDL_Rect *camera) {
    // Render the enemies with the camera's position offset
    for (int i = 0; i < num_enemies; i++) {
        // ...
        SDL_Rect dest = {enemies[i].x - camera->x, enemies[i].y - camera->y, enemies[i].width, enemies[i].height};
        SDL_RenderCopy(g_renderer, enemies[i].texture, NULL, &dest);
    }
}
