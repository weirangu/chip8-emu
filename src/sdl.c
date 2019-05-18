#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "sdl.h"
#include "beep_wav.h"

SDL_Window* sdl_win = NULL;
SDL_Renderer* sdl_ren = NULL;
SDL_AudioDeviceID audio_dev = 0;
Uint32 beep_length = 0;
Uint8* beep_buffer = NULL;

// The following are not to be used anywhere else, but still needs to be kept
// track of for when we close SDL
static SDL_AudioSpec beep_wav;
static SDL_RWops* beep_rw = NULL;

void init_sdl(void) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) { //Start SDL
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_CreateWindowAndRenderer(800, 400, SDL_WINDOW_SHOWN, &sdl_win, &sdl_ren);
    if (sdl_win == NULL || sdl_ren == NULL) {
        fprintf(stderr, "SDL_CreateWindowAndRenderer failed: %s\n", SDL_GetError());
        exit(1);
    }

    // Initialize beep tone
    if ((beep_rw = SDL_RWFromConstMem(beep_wav_data, beep_wav_len)) == NULL) {
        fprintf(stderr, "SDL_RWFromConstMem failed: %s\n", SDL_GetError());
        exit(1);
    }

    if (SDL_LoadWAV_RW(beep_rw, 1, &beep_wav, &beep_buffer, &beep_length) == NULL) {
        fprintf(stderr, "SDL_LoadWAV_RW failed: %s\n", SDL_GetError());
        exit(1);
    }
    if ((audio_dev = SDL_OpenAudioDevice(NULL, 0, &beep_wav, NULL, 0)) == 0) {
        fprintf(stderr, "SDL_OpenAudioDevice failed: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_PauseAudioDevice(audio_dev, 0);
}
void cleanup_sdl(void) {
    if (audio_dev != 0) {
        SDL_CloseAudioDevice(audio_dev);
    }
    if (beep_buffer != NULL) {
        SDL_FreeWAV(beep_buffer);
    }
    if (beep_rw != NULL) {
        SDL_RWclose(beep_rw);
    }
    if (sdl_ren != NULL) {
        SDL_DestroyRenderer(sdl_ren);
    }
    if (sdl_win != NULL) {
        SDL_DestroyWindow(sdl_win);
    }
    SDL_Quit();
}

void print_screen(unsigned char graphics[SCREEN_WIDTH][SCREEN_HEIGHT]) {
    SDL_Surface* surface = SDL_GetWindowSurface(sdl_win);
    Uint32 white = SDL_MapRGB(surface->format, 255, 255, 255);
    Uint32 black = SDL_MapRGB(surface->format, 0, 0, 0);
    SDL_Rect rect = {.h = 10, .w = 10};

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            for (int k = 7; k >= 0; k--) {
                // We see the value of each bit and draw if its a 1
                int bit = graphics[j][i] & 1 << k;
                rect.x = (j * 8 + (7 - k)) * 10;
                rect.y = i * 10;

                if (bit) {
                    SDL_FillRect(surface, &rect, white);
                }
                else {
                    SDL_FillRect(surface, &rect, black);
                }
            }
        }
    }

    SDL_UpdateWindowSurface(sdl_win);
}