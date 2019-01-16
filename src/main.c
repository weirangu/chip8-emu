#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include "chip8/sys.h"

int main(int argc, char* argv[]){
    if (argc < 2) {
        perror("File required as an argument.");
        return 1;
    }
    srand(time(NULL)); // Needed for random numbers for the CXNN opcode.
    FILE* file = fopen(argv[1], "rb");
    if (file == NULL) {
        // File was not open
        perror("File could not be open.");
        return 1;
    }
    WINDOW* win = initscr();
    cbreak();
    noecho();
    nodelay(win, TRUE);

    run(init_sys(file));

    endwin();
    fclose(file);
    return 0;
}
