#define BOARD_SZ 3
#define EMPTY '_'

typedef char board_t[3][3];

void init_board(board_t board, char **argv);

void print_board(board_t board);

int check_board(board_t board);

