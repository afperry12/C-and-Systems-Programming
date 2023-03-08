#include "lab04.h"
#include <stdio.h>
#include <math.h>

//initialize a tic tac toe board
void init_board(board_t board, char** argv) {
	int sizeOfArgv = 0;
	while(argv[++sizeOfArgv]);
	sizeOfArgv-=2;
	sizeOfArgv = sqrt(sizeOfArgv);
	int argvIter = 0;
	// printf("%i\n", sizeOfArgv);
	// printf("before: %c\n",board[0][5]);
	for(int x = 0; x < sizeOfArgv; x++) {
		for(int y = 0; y < sizeOfArgv; y++) {
			board[x][y] = *argv[argvIter];
			argvIter++;
		}
	}
}

//print the squares of a board
void print_board(board_t board) {
	for(int x = 0;x < sizeof(board[0]);x++) {
		for(int y = 0;y < sizeof(board_t)/sizeof(board[0]);y++) {
			printf(" ");
			printf("%c",board[x][y]);
			if(y+1 != sizeof(board_t)/sizeof(board[0])) {
				printf(" ");
				printf("|");
			}
		}
		if(x+1 != sizeof(board[0])) {
			printf("\n---+---+---");
		}
		printf("\n");
	}
}

//check who wins
int check_board(board_t board) {
	//check horizontal
	for(int x = 0;x < sizeof(board[0]);x++) {
		char t = board[x][0];
		for(int y = 0;y < sizeof(board_t)/sizeof(board[0]);y++) {
			if(t!=board[x][y]) {
				t='\0';
			}
		}
		if(t!='\0') {
			if(t=='X') return 1;
			else if(t=='O') return -1;
		}
	}

	//check vertical
	for(int x = 0;x < sizeof(board[0]);x++) {
		char t = board[0][x];
		for(int y = 0;y < sizeof(board_t)/sizeof(board[0]);y++) {
			if(t!=board[y][x]) {
				t='\0';
			}
		}
		if(t!='\0') {
			if(t=='X') return 1;
			else if(t=='O') return -1;
		}
	}
	
	//check diaganol
	char t = board[0][0];
	int x = 0;
	int y = 0;
	for(int i = 0;i < sizeof(board[0]);i++) {
		if(t!=board[x][y]) {
			t='\0';
		}
		x++;
		y++;
	}
		
	if(t!='\0') {
		if(t=='X') return 1;
		else if(t=='O') return -1;
	}

	//check backwards diaganol
	t = board[0][2];
	x = 0;
	y = 2;
	for(int i = 0;i < sizeof(board[0]);i++) {
		if(t!=board[x][y]) {
			t='\0';
		}
		x++;
		y--;
	}
		
	if(t!='\0') {
		if(t=='X') return 1;
		else if(t=='O') return -1;
	}
	
}
