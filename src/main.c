#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include "chip8/sys.h"

int main(int argc, char* argv[]){
    if (argc < 2){
        perror("File required as an argument.");
        return 1;
    }
    else {
        FILE* file = fopen(argv[1], "rb");
        if (file == NULL) {
            // File was not open
            perror("File could not be open.");
            return 1;
        }
        initscr();
        run(init_sys(file));
        refresh();
        int c = getch();
        endwin();
        fclose(file);
    }
    return 0;
}
