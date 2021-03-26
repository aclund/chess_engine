#include <iostream>

using namespace std;

#include "functions.h"
#include "global.h"

void engine() {

	int i_start_depth[10] = {0, 1};
	int i_end_depth  [10] = {1};

	// Load board into temporary for some reason then find every possible move
	int max_tree = 111;
	int size_add = 1000;
	int **possible_boards = new int*[max_tree];
	for( int i = 0; i < max_tree; i++ ) {
		possible_boards[i] = new int[64]; 
	}

	// Set current board
	int count = 0;
	for( int row = 0; row < 8; row++ ) {
		for( int col = 0; col < 8; col++ ) {
			possible_boards[0][count] = board[row][col];
			count++;
		}
	}

	// Find all moves in depth
	int engine_board = 0;
	int move_counter = 0;
	int i_open;
	n_possible_moves = 0;
	for( int depth = 0; depth < max_depth; depth++ ) {

	cout << " Depth, i_start, i_end = " << depth << " " << i_start_depth[depth] << " " << i_end_depth[depth]<<endl;

		i_open = i_end_depth[depth];
		for( int i = i_start_depth[depth]; i < i_end_depth[depth]; i++ ) {
			all_moves(possible_boards[i], &possible_boards[i_open]);
			i_open += n_possible_moves;
			cout << "i # Possible Moves = " << i << " " << n_possible_moves << "\n";

			if( (max_tree - i_open) < 100 ) { // Could run out of memory next board
		return;
				size_t newSize = max_tree + size_add;
    				int **newArr = new int*[newSize];
				for( int i = 0; i < max_tree; i++ ) {
					newArr[i] = new int[64]; 
				}

    				memcpy( newArr, possible_boards, max_tree * sizeof(int) );

				for( int i = 0; i < max_tree; i++ ) {
					delete [] possible_boards[i];
				}
				delete [] possible_boards;

    				max_tree = newSize;
				for( int i = 0; i < max_tree; i++ ) {
					possible_boards[i] = newArr[i]; 
				}
				cout << " ALLOCATED MEMORY\n";
			}
		}
		i_end_depth[depth+1]   = i_open;
		i_start_depth[depth+2] = i_open;

	}

	// Update board with best move
	int index = 0;
	for( int row = 0; row < 8; row++ ) {
		for( int col = 0; col < 8; col++ ) {
			board[row][col] = possible_boards[engine_board][index];
			index++;
		}
	}

	// Delete tree
	cout << max_tree;
	for( int i = 0; i < max_tree; i++ ) {
		delete [] possible_boards[i];
	}
	delete [] possible_boards;

	return;
}
