#include <string>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

#include "functions.h"
#include "global.h"

void random_player() {

	// Load board into temporary for some reason then find every possible move
	int board_in[64];
	int max_tree = 111;
	int **possible_boards = new int*[max_tree];
	for( int i = 0; i < max_tree; i++ ) {
		possible_boards[i] = new int[64]; 
	}

	int count = 0;
	for( int row = 0; row < 8; row++ ) {
		for( int col = 0; col < 8; col++ ) {
			board_in[count] = board[row][col];
			count++;
		}
	}
	n_possible_moves = 0;
	all_moves(board_in, possible_boards);
	cout << "# Possible Moves = " << n_possible_moves << "\n";

	srand (time(NULL));
	int rando_board = rand() % n_possible_moves;
	int index = 0;
	for( int row = 0; row < 8; row++ ) {
		for( int col = 0; col < 8; col++ ) {
			board[row][col] = possible_boards[rando_board][index];
			index++;
		}
	}
	// Delete tree
	for( int i = 0; i < max_tree; i++ ) {
		delete [] possible_boards[i];
	}
	delete [] possible_boards;

	return;
}
