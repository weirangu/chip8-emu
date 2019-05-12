#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __linux__
#include <unistd.h>
#endif
#include <SDL2/SDL.h>
#include <getopt.h>
#include "render.h"
#include "chip8/sys.h"

#define ARG_INFO "Filename is required.\nAvailable optional arguments:\n\
 -s, --speed\t\tThe number of milliseconds per cycle\n\
 -k, --key-hold-time\tThe number of cycles a key press is valid for.\n\
 -d, --debug\t\tDisplays debugging information (such as register info)\n\
 -h, --hold-key\t\tMakes a keypress last for the entire duration of the key hold time,\
 \n\t\t\trather than resetting when the state of the key is checked.\n"

#define DEFAULT_KEY_HOLD_TIME 100
#define DEFAULT_SPEED 5

WINDOW* curses_win; // The curses window for this program
int debug = 0; // Determines whether we're in debug mode, defaults to 0
int hold_key = 0; // Determines whether key should be reset to 0 when we run a EXXX that checks for that key

int main(int argc, char* argv[]) {
    // Parsing command line arguments
    int speed = DEFAULT_SPEED;
    int key_hold_time = DEFAULT_KEY_HOLD_TIME;
    int options_index = 0;
    int arg;
    char* strtol_endptr;
    struct option options[] = {
            {"speed",         required_argument, NULL, 's'}, // The speed of each cycle (in ms)
            {"debug",         no_argument, &debug,     1}, // Also activated by -d, used to show register information
            {"key-hold-time", required_argument, NULL, 'k'}, // Changes the key hold time (in cycles) for pressed keys
            {"hold-key",      no_argument, &hold_key,  1}, // Also activated by -h, when active key doesn't reset on EXXX opcodes
            {0,               0,           0,          0} // Null terminate this array
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
            case 'k':
                key_hold_time = strtol(optarg, &strtol_endptr, 10);
                if (strtol_endptr == optarg) {
                    // We never read in a number
                    printf(ARG_INFO);
                    return 1;
                }
                break;
            case 'd':
                debug = 1;
                break;
            case 'h':
                hold_key = 1;
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

    bool quit = FALSE;
    chip8_sys* sys = init_sys(file, speed, key_hold_time);

    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = TRUE;
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
