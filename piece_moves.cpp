#include <iostream>
#include <fstream>

using namespace std;

#include "global.h"
#include "functions.h"

void piece_moves( int *board_in, int *board_params, int index, int *to_square, int *possem ) {

	int counter = 0;
	int index_update, n_count;

	int i_turn = board_params[0];

	int offset = 0;
	if( i_turn == -1 ) offset = 2;
	bool castle_l = false, castle_r = false;
        if( board_params[1+offset] == 1 ) castle_r = true;
        if( board_params[2+offset] == 1 ) castle_l = true;
	//en_passant = params[5];
	en_passant = -1;

	board_params[5] = -1;

	int piece = i_turn*board_in[index];

	switch(piece) {

	case 1: // PAWN
		index_update = index + 8*i_turn;  // Square in front
		if( board_in[index_update] == 0 ) {
			to_square[counter] = index_update;
			counter++;
		}
		index_update = index + 16*i_turn; // Up two beginning 
		if( board_in[index_update]   == 0 &&
		    board_in[index+8*i_turn] == 0 &&
		    pawn_rel_rank(index, i_turn) == 2 ) {
			to_square[counter] = index_update;
			counter++;
			params[5] = index + 8*turn;
		}
		index_update = index + 7*i_turn;
		if( board_in[index_update]*i_turn < 0 or 
		    en_passant == index_update ) { // Capturable left
			to_square[counter] = index_update;
			counter++;
		}
		index_update = index + 9*i_turn;
		if( board_in[index_update]*i_turn < 0 or
		    en_passant == index_update ) { // Capturable right
			to_square[counter] = index_update;
			counter++;
		}
	break;

	case 2: // KNIGHT
		for( int n_moves = 0; n_moves < n_knight_moves[index]; n_moves++ ) {
			if( board_in[knight_moves[index][n_moves]]*i_turn <= 0 ) {
				to_square[counter] = knight_moves[index][n_moves];
				counter++;
			}
		}
	break;

	case 3: // BISHOP
		for( int n_direction = 4; n_direction < 8; n_direction++ ) {
			n_count = 0;
			index_update = index;
			while( n_count < count_to_edge[index][n_direction] ) {
				index_update += index_directions[n_direction];
				if( board_in[index_update] == 0 ) {
					to_square[counter] = index_update;
					counter++;
					n_count++;
				}
				else if( board_in[index_update]*i_turn < 0 ) {
					to_square[counter] = index_update;
					counter++;
					n_count = 7;
				}
				else { n_count = 7; }
			}
		}
	break;

	case 4: // ROOK
		for( int n_direction = 0; n_direction < 4; n_direction++ ) {
			n_count = 0;
			index_update = index;
			while( n_count < count_to_edge[index][n_direction] ) {
				index_update += index_directions[n_direction];
				if( board_in[index_update] == 0 ) {
					to_square[counter] = index_update;
					counter++;
					n_count++;
				}
				else if( board_in[index_update]*i_turn < 0 ) {
					to_square[counter] = index_update;
					counter++;
					n_count = 7;
				}
				else { n_count = 7; }
			}
		}
	break;

	case 5: // QUEEN
		for( int n_direction = 0; n_direction < 8; n_direction++ ) {
			n_count = 0;
			index_update = index;
			while( n_count < count_to_edge[index][n_direction] ) {
				index_update += index_directions[n_direction];
				if( board_in[index_update] == 0 ) {
					to_square[counter] = index_update;
					counter++;
					n_count++;
				}
				else if( board_in[index_update]*i_turn < 0 ) {
					to_square[counter] = index_update;
					counter++;
					n_count = 7;
				}
				else { n_count = 7; }
			}
		}
	break;

	case 6: // KING
		for( int n_direction = 0; n_direction < 8; n_direction++ ) {
			n_count = 0;
			index_update = index + index_directions[n_direction];
			if( count_to_edge[index][n_direction] != 0 &&
			    board_in[index_update]*i_turn <= 0 ) {
				to_square[counter] = index_update;
				counter++;
			}
			// Castle
			if( castle_r ) {
			}
			if( castle_l ) {
			}
		}
	break;

	}

	*possem = counter;

	return;
}
