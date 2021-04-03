#include <iostream>

using namespace std;

#include "functions.h"
#include "global.h"

int n_open;

void store_board( int board_update[64], int **possible_boards, int piece, int index_from, int index_update ) {
	//cout << " index_from, index_update = " << index_from << "  " << index_update << "\n";
	//board_update[index_from]   = 0;
	//board_update[index_update] = piece;
	for( int i = 0; i < 64; i++ ) {
		possible_boards[n_open][i] = board_update[i];
	}
	possible_boards[n_open][index_from] = 0; 
	possible_boards[n_open][index_update] = piece;
	n_open++;
	n_possible_moves++;
	return;
}

void all_moves( int *board_in, int *board_params, int **possible_boards, int i_turn ) {

	n_open = 0;

	int n_count, index_update, index_king, piece, possem, check_possem;
	int n_checks = 0;
	int pins[64], to_squares[28], check_piece[2];
	int promote_pieces = 4;

	// If in CHECK
check_possem = 0;
	board_params[0] = -1*i_turn;
	for( int index = 0; index < 64; index++ ) {
		if( board_in[index] == i_turn*king ) {
			index_king = index;
		}
	}
	for( int index = 0; index < 64; index++ ) {
		if( board_in[index]*i_turn < 0 ) { // Other color pieces
			// If move == your king
			piece_moves( board_in, board_params, index, to_squares, &possem );

			for( int n = 0; n < possem; n++ ) {
				if( to_squares[n] == index_king ) {
					check_piece[n_checks] = index;
					n_checks++;
				}	
			}
		}
	}
	if( n_checks > 0 ) {
		//in_check( board_in, board_params, check_piece, n_checks, to_squares, &check_possem );
		for( int j = 0; j < check_possem; j++ ) { 
			//store_board( board_in, possible_boards, board_in[check_piece], index, to_squares[j] );
		}
		return;
	}

	board_params[0] = i_turn;
	for( int index = 0; index < 64; index++ ) {

		if( board_in[index]*i_turn > 0 ) { // Your piece on square

			piece = board_in[index];

			piece_moves( board_in, board_params, index, to_squares, &possem );

			for( int n = 0; n < possem; n++ ) {
				store_board( board_in, possible_boards, piece, index, to_squares[n] );
			}

		}
	}


	return;
}
