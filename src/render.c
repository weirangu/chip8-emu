#include <stdio.h>
#include <stdlib.h>
#include "render.h"

SDL_Window* sdl_win = NULL;
SDL_Renderer* sdl_ren = NULL;

void init_sdl(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { //Start SDL
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_CreateWindowAndRenderer(640, 320, SDL_WINDOW_SHOWN, &sdl_win, &sdl_ren);
    if (sdl_win == NULL || sdl_ren == NULL) {
        fprintf(stderr, "SDL_CreateWindowAndRenderer failed: %s\n", SDL_GetError());
        exit(1);
    }
}

void cleanup_sdl(void) {
    if (sdl_ren != NULL) {
        SDL_DestroyRenderer(sdl_ren);
    }
    if (sdl_win != NULL) {
        SDL_DestroyWindow(sdl_win);
    }
    SDL_Quit();
}