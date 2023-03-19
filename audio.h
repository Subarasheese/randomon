#ifndef AUDIO_H
#define AUDIO_H

#include <stdbool.h>
#include <SDL_mixer.h>

// Initialize audio
bool audio_init();

// Clean up resources
void audio_cleanup();

#endif // AUDIO_H
