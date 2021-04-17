#include <iostream>

using namespace std;

#include "functions.h"
#include "global.h"

void check_check( int index_king, int *board_in, int *board_params, int *check_pieces, int *n_checks ) {

	// Don't update params on search
	int max_moves = 27;
        int **null_params = new int*[max_moves];
        for( int i = 0; i < max_moves; i++ ) {
                null_params[i] = new int[n_params];
	}

	int i_turn = board_params[0];

	int possem;
	int to_squares[max_moves];

	// If in CHECK
	board_params[0] *= -1;
	int counter = 0;
	for( int index = 0; index < 64; index++ ) {
		if( board_in[index]*i_turn < 0 ) { // Other color pieces
			// If other color move == your king
			piece_moves( board_in, board_params, null_params, index, to_squares, &possem );

			for( int i = 0; i < possem; i++ ) {
				if( to_squares[i] == index_king ) {
					check_pieces[counter] = index;
					counter++;
				}	
			}
		}
	}
	board_params[0] *= -1;

	*n_checks = counter;


	// Delete temp params
        for( int i = 0; i < max_moves; i++ ) {
                delete [] null_params[i];
	}
	delete [] null_params;

	return;
}
