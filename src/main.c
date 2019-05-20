#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __linux__
#include <unistd.h>
#endif
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include "sdl.h"
#include "chip8/sys.h"

#define ARG_INFO "Filename is required.\nAvailable optional arguments:\n\
 -s, --speed\t\tThe number of milliseconds per cycle.\n"

#define DEFAULT_SPEED 1

int main(int argc, char* argv[]) {
    // Parsing command line arguments
    int speed = DEFAULT_SPEED;
    int options_index = 0;
    int arg;
    char* strtol_endptr;
    struct option options[] = {
        {"speed", required_argument, NULL, 's'}, // The speed of each cycle (in ms)
        {0, 0, 0, 0} // Null terminate this array
    };

    while ((arg = getopt_long(argc, argv, "s:dk:h", options, &options_index)) != -1) {
        switch (arg) {
            case 0:
                // We set a flag
                break;
            case 's':
                speed = strtol(optarg, &strtol_endptr, 10);
                if (strtol_endptr == optarg) {
                    // We never read in a number
                    printf(ARG_INFO);
                    return 1;
                }
                break;
            default:
                // An invalid argument was provided
                printf(ARG_INFO);
                return 1;
        }
    }

    srand(time(NULL)); // Needed for random numbers for the CXNN opcode.
    if (optind >= argc) {
        // No filename was provided
        printf(ARG_INFO);
        return 1;
    }

    FILE* file = fopen(argv[optind], "rb");
    if (file == NULL) {
        // File was not open
        perror("fopen");
        return 1;
    }
    init_sdl();

    int quit = FALSE;
    chip8_sys* sys = init_sys(file);

    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = TRUE;
                    break;
                case SDL_KEYDOWN:
                    key_down(sys, e.key.keysym.sym);
                    break;
                case SDL_KEYUP:
                    key_up(sys, e.key.keysym.sym);
                    break;
                default:
                    break;
            }
        }

        // Run a cycle and print
        cycle(sys);
        print_screen(sys->graphics);

        // Wait for next cycle
#ifdef _WIN32
        Sleep(speed);
#endif
#ifdef __linux__
        usleep(1000 * speed);
#endif
    }
    fclose(file);
    cleanup_sdl();
    return 0;
}
