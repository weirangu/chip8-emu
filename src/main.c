#include <stdio.h>
#include "chip8/sys.h"

int main(int argc, char* argv[]){
    if (argc >=2 ){
        printf("Path: %s", argv[1]);
        FILE* file = fopen(argv[1], "rb");
        print_sys_mem(init_sys(file));
        fclose(file);
    }
    else {
        printf("File required! argc: %d", argc);
    }
    char c = getchar();
    return 0;
}
