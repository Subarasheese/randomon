#include <stdbool.h>
#include "graphics.h"
#include "game.h"

// Global variables
SDL_Texture *g_player_texture = NULL;

static bool load_assets() {
    // Load player sprite sheet
    g_player_texture = load_texture("player_spritesheet.png");
    if (!g_player_texture) {
        fprintf(stderr, "Failed to load player sprite sheet!\n");
        return false;
    }

    // Load other assets...

    return true;
}

// Load texture function
SDL_Texture *load_texture(const char *filename) {
    SDL_Surface *surface = IMG_Load(filename);
    if (!surface) {
        fprintf(stderr, "Error loading image: %s\n", IMG_GetError());
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(g_renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
        return NULL;
    }

    return texture;
}


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
    // Free the player's texture
    SDL_DestroyTexture(g_player_texture);

    // Free other textures...
}

void render_background(SDL_Rect *camera) {
    // Render the background with the camera's position offset
    // ...
    SDL_Rect dest = {bg.x - camera->x, bg.y - camera->y, bg.width, bg.height};
    SDL_RenderCopy(g_renderer, bg.texture, NULL, &dest);
}

void render_player(Player *player, SDL_Rect *camera) {
    // Calculate the source rectangle based on player direction
    SDL_Rect src = {
        player->direction * player->width,
        0,
        player->width,
        player->height
    };

    // Calculate the destination rectangle with the camera's position offset
    SDL_Rect dest = {
        player->x - camera->x,
        player->y - camera->y,
        player->width,
        player->height
    };

    // Render the player's sprite
    SDL_RenderCopy(g_renderer, g_player_texture, &src, &dest);
}

void render_enemies(SDL_Rect *camera) {
    // Render the enemies with the camera's position offset
    for (int i = 0; i < num_enemies; i++) {
        // ...
        SDL_Rect dest = {enemies[i].x - camera->x, enemies[i].y - camera->y, enemies[i].width, enemies[i].height};
        SDL_RenderCopy(g_renderer, enemies[i].texture, NULL, &dest);
    }
}
