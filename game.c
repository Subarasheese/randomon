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

// Global variables
SDL_Renderer *g_renderer = NULL;
SDL_Rect g_camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
bool g_running = false;


typedef struct {
    int x, y;
    int width, height;
    int speed;
    int direction;
} Player;

// Directions
enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
};

Player player = {100, 100, 32, 32, 2, DIR_DOWN};


// Overworld dimensions
#define WORLD_WIDTH 100
#define WORLD_HEIGHT 100

typedef struct {
    int id;
    bool solid;
} Tile;

Tile world[WORLD_HEIGHT][WORLD_WIDTH];


// Initialize the game
bool game_init(SDL_Window *window) {
    // Initialize the renderer
    g_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (g_renderer == NULL) {
        fprintf(stderr, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    create_overworld();
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
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    player.direction = DIR_UP;
                    break;
                case SDLK_DOWN:
                    player.direction = DIR_DOWN;
                    break;
                case SDLK_LEFT:
                    player.direction = DIR_LEFT;
                    break;
                case SDLK_RIGHT:
                    player.direction = DIR_RIGHT;
                    break;
            }
        }
    }
}

bool is_collision(int x, int y, Player *player) {
    int tile_size = 32;
    int left_tile = x / tile_size;
    int top_tile = y / tile_size;
    int right_tile = (x + player->width - 1) / tile_size;
    int bottom_tile = (y + player->height - 1) / tile_size;

    // Check if any of the four corners of the player's new position collide with solid tiles
    if (world[top_tile][left_tile].solid || world[top_tile][right_tile].solid ||
        world[bottom_tile][left_tile].solid || world[bottom_tile][right_tile].solid) {
        return true;
    }

    return false;
}

// Update game logic
static void update() {
    // ...
    // Calculate the new position based on player's direction and speed
    int new_x = player.x;
    int new_y = player.y;

       switch (player.direction) {
        case DIR_UP:
            new_y -= player.speed;
            break;
        case DIR_DOWN:
            new_y += player.speed;
            break;
        case DIR_LEFT:
            new_x -= player.speed;
            break;
        case DIR_RIGHT:
            new_x += player.speed;
            break;
    }

    // Check for collision with solid tiles
    if (!is_collision(new_x, new_y, &player)) {
        player.x = new_x;
        player.y = new_y;
    }

    // Ensure the player stays within the grid and on-screen
    int gridSize = 32;
    player.x = (player.x / gridSize) * gridSize;
    player.y = (player.y / gridSize) * gridSize;

    if (player.x < 0) player.x = 0;
    if (player.y < 0) player.y = 0;
    if (player.x > SCREEN_WIDTH - player.width) player.x = SCREEN_WIDTH - player.width;
    if (player.y > SCREEN_HEIGHT - player.height) player.y = SCREEN_HEIGHT - player.height;
}

static void create_overworld() {
    // Fill the world array with tile data
    // Use 0 for non-solid tiles and 1 for solid tiles
    // For example:

    for (int y = 0; y < WORLD_HEIGHT; y++) {
        for (int x = 0; x < WORLD_WIDTH; x++) {
            world[y][x].id = (x == 0 || y == 0 || x == WORLD_WIDTH - 1 || y == WORLD_HEIGHT - 1) ? 1 : 0;
            world[y][x].solid = (world[y][x].id == 1);
        }
    }
}


// Render game
static void render() {
    // Clear the screen
    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
    SDL_RenderClear(g_renderer);
    render_overworld(world, &g_camera);
    // Render game objects here
    render_player(&player, &g_camera);

    // Update the screen
    SDL_RenderPresent(g_renderer);
}

