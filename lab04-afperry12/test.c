#include <stdio.h>
#include <string.h>
#include "lab04.h"

void print_result (int result) {
    switch (result) {
        case 1: printf("X wins\n"); break;
        case -1: printf("O wins\n"); break;
        default: printf("draw\n");
    }
}
int main(int argc, char **argv) {

    board_t b;

    if (strcmp(argv[1], "empty") == 0) {
        char* argv[] = {"_", "_", "_", "_", "_", "_", "_", "_", "_"};
        init_board(b, argv);
        print_board(b);

    } else if (strcmp(argv[1], "print") == 0) {
        for (int r = 0; r < BOARD_SZ; r++) {
            for (int c = 0; c < BOARD_SZ; c++) {
                b[r][c] = '_';
            }
        }
        print_board(b);

    } else if (strcmp(argv[1], "init") == 0) {
        char* argv[]  = {"X", "_", "O", "_", "X", "_", "_", "_", "O"};
        init_board(b, argv);
        if ((b[0][0] == 'X') && (b[0][0] == b[1][1]) && 
            (b[0][1] == '_') && (b[0][1] == b[1][0]) && (b[0][1] == b[1][2]) && (b[0][1] == b[2][0]) && (b[0][1] == b[2][1]) &&
            (b[0][2] == 'O') && (b[0][2] == b[2][2])) {
                printf("init success\n");
        } else {
            printf("init fail\n");
        }

    }  else if (strcmp(argv[1], "board") == 0) {
         char* argv[]  = {"X", "_", "O", "_", "X", "_", "_", "_", "O"};
        init_board(b, argv);
        print_board(b);

    }  else if (strcmp(argv[1], "check") == 0) {
        b[0][0] = b[0][1] = b[0][2] = 'X';
        b[1][0] = b[1][2] = b[2][0] = b[2][1] = '_';
        b[1][1] = b[2][2] = 'O';
        print_result(check_board(b));

    }  else if (strcmp(argv[1], "xhoriz") == 0) {
        char* argv[]  = {"X", "X", "X", "_", "O", "_", "_", "_", "O"};
        init_board(b, argv);
        print_board(b);
        print_result(check_board(b));

    } else if (strcmp(argv[1], "overt") == 0) {
        char* argv[]  = { "X", "X", "O", "_", "_", "O", "_", "_", "O"};
        init_board(b, argv);
        print_board(b);
        print_result(check_board(b));

    } else if (strcmp(argv[1], "diag1") == 0) {
        char* argv[]  = {"O", "X", "X", "_", "O", "X", "X", "_", "O"};
        init_board(b, argv);
        print_board(b);
        print_result(check_board(b));

    } else if (strcmp(argv[1], "diag2") == 0) {
        char* argv[]  = {"O", "X", "X", "_", "X", "X", "X", "_", "O"};
        init_board(b, argv);
        print_board(b);
        print_result(check_board(b));
        
    } else if (strcmp(argv[1], "draw") == 0) {
        char* argv[]  = {"X", "O", "X", "O", "X", "O", "O", "X", "O"};
        init_board(b, argv);
        print_board(b);
        print_result(check_board(b));
    } 
    
    return 0;
}
