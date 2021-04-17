#include <iostream>

using namespace std;

#include "functions.h"
#include "global.h"

bool game_over() {

	bool is_over = false;

	int max_tree = 111;
	int **possible_boards = new int*[max_tree];
	int **possible_params = new int*[max_tree];
	for( int i = 0; i < max_tree; i++ ) {
		possible_boards[i] = new int[64]; 
		possible_params[i] = new int[n_params]; 
	}

	int count = 0;
	for( int row = 0; row < 8; row++ ) {
		for( int col = 0; col < 8; col++ ) {
			possible_boards[0][count] = board[row][col];
			count++;
		}
	}
	n_possible_moves = 0;
	all_moves(possible_boards[0], params, &possible_boards[1], &possible_params[1]);

	int n_checks = 0;
	int check_pieces[2];
	if( n_possible_moves == 0 ) {
		is_over = true;
		write_board();

		int index_king;
		int i_turn = params[0];
		for( int index = 0; index < 64; index++ ) {
        	        if( possible_boards[0][index] == i_turn*king ) {
                	        index_king = index;
                       	 break;
                	}
        	}

		check_check( index_king, possible_boards[0], params, check_pieces, &n_checks );
		if( n_checks == 0 ) {
			cout << " STALEMATE! \n";
		}
		else {
			cout << " CHECKMATE! \n";
		}
	}


	// Delete tree
	for( int i = 0; i < max_tree; i++ ) {
		delete [] possible_boards[i];
		delete [] possible_params[i];
	}
	delete [] possible_boards;
	delete [] possible_params;

	return is_over;
}
