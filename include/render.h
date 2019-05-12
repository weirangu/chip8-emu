#ifndef RENDER_H
#define RENDER_H
#include <SDL2/SDL.h>
#include "chip8/sys.h" // For SCREEN_WIDTH and SCREEN_HEIGHT


extern SDL_Window* sdl_win;
extern SDL_Renderer* sdl_ren;

// Initializes SDL and creates the window and renderer
// Exits the program on failure.
void init_sdl(void);

// Destroys the SDL window and r
void cleanup_sdl(void);

// Draws the emulator's screen
void print_screen(unsigned char graphics[SCREEN_WIDTH][SCREEN_HEIGHT]);

#endif
