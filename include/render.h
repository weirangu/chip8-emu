#ifndef RENDER_H
#define RENDER_H
#include <SDL2/SDL.h>

extern SDL_Window* sdl_win;
extern SDL_Renderer* sdl_ren;

// Initializes SDL and creates the window and renderer
// Exits the program on failure.
void init_sdl(void);

// Destroys the SDL window and r
void cleanup_sdl(void);

#endif
