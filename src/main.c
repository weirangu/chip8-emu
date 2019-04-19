#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <getopt.h>
#include "chip8/sys.h"

#define ARG_INFO "Filename is required.\nAvailable optional arguments:\n\
 -s, --speed\t\tThe number of milliseconds per cycle\n\
 -k, --key-hold-time\tThe number of cycles a key press is valid for\n\
 -d, --debug\t\tDisplays debugging information (such as register info)\n"

#define DEFAULT_KEY_HOLD_TIME 100
#define DEFAULT_SPEED 5

WINDOW* curses_win; // The curses window for this program
int debug = 0; // Determines whether we're in debug mode, defaults to 0

int main(int argc, char* argv[]){
    // Parsing command line arguments
    int speed = DEFAULT_SPEED;
    int key_hold_time = DEFAULT_KEY_HOLD_TIME;
    int options_index = 0;
    int arg;
    char *strtol_endptr;
    struct option options[] = {
            {"speed", required_argument, NULL, 's'}, // The speed of each cycle (in ms)
            {"debug", no_argument, &debug, 1}, // Also activated by -d, used to show register information
            {"key-hold-time", required_argument, NULL, 'k'}, // Changes the key hold time (in cycles) for pressed keys
            {0, 0, 0, 0} // Null terminate this array
    };

    while ((arg = getopt_long(argc, argv, "s:dk:", options, &options_index)) != -1) {
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

    curses_win = initscr();
    cbreak();
    noecho();
    curs_set(0); // Sets cursor to invis
    nodelay(curses_win, TRUE);

    run(init_sys(file, speed, key_hold_time));

    // This point shouldn't be reached (as run has an endless loop)
    endwin();
    fclose(file);

    return 0;
}
