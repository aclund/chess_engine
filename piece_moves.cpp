#include <iostream>
#include <fstream>

using namespace std;

#include "global.h"
#include "functions.h"

void piece_moves( int *board_in, int *board_params, int **update_params, int index, int *to_square, int *possem ) {

	int counter = 0;
	int index_update, n_count, k_rook, q_rook, king_start, to_rook;

	int i_turn = board_params[0];

	int castle_offset = 0;
	if( i_turn == -1 ) castle_offset = 2;
	en_passant = board_params[5];

	int pawn_off_right = 40 - (1-i_turn)/2*17; // 40/23
	int pawn_off_left  = 31 - (1-i_turn)/2;    // 31/32

	int check_pieces[2], n_checks;

	int piece = i_turn*board_in[index];

	switch(piece) {

	case 1: // PAWN
		index_update = index + 8*i_turn;  // Square in front
		if( board_in[index_update] == 0 ) {
			to_square[counter] = index_update;
	pawn_counter++;
			counter++;
		}
		index_update = index + 16*i_turn; // Up two beginning 
		if( board_in[index_update]   == 0 &&
		    board_in[index+8*i_turn] == 0 &&
		    pawn_rel_rank(index, i_turn) == 2 ) {
			to_square[counter] = index_update;
			update_params[counter][5] = index + 8*i_turn;
	pawn_counter++;
			counter++;
		}
		index_update = index + 7*i_turn; // Capturable left
		if( ( board_in[index_update]*i_turn < 0 or 
		    en_passant == index_update ) && index_update != pawn_off_left  ) {
			to_square[counter] = index_update;
	pawn_counter++;
			counter++;
		}
		index_update = index + 9*i_turn; // Capturable right
		if( ( board_in[index_update]*i_turn < 0 or
		    en_passant == index_update ) && index_update != pawn_off_right ) {
			to_square[counter] = index_update;
	pawn_counter++;
			counter++;
		}
	break;

	case 2: // KNIGHT
		for( int n_moves = 0; n_moves < n_knight_moves[index]; n_moves++ ) {
			if( board_in[knight_moves[index][n_moves]]*i_turn <= 0 ) {
				to_square[counter] = knight_moves[index][n_moves];
	knight_counter++;
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
	bishop_counter++;
					counter++;
					n_count++;
				}
				else if( board_in[index_update]*i_turn < 0 ) {
					to_square[counter] = index_update;
	bishop_counter++;
					counter++;
					n_count = 7;
				}
				else { n_count = 7; }
			}
		}
	break;

	case 4: // ROOK
		k_rook = 7 + (1 - i_turn)*28;
		q_rook = 0 + (1 - i_turn)*28;
		for( int n_direction = 0; n_direction < 4; n_direction++ ) {
			n_count = 0;
			index_update = index;
			while( n_count < count_to_edge[index][n_direction] ) {
				index_update += index_directions[n_direction];
				if( board_in[index_update] == 0 ) {
					to_square[counter] = index_update;
	rook_counter++;
					// No castle
					if(      index == k_rook ) {
						update_params[counter][1+castle_offset] = 0;
					}
					else if( index == q_rook ) {
						update_params[counter][2+castle_offset] = 0;
					}
					counter++;
					n_count++;
				}
				else if( board_in[index_update]*i_turn < 0 ) {
					to_square[counter] = index_update;
	rook_counter++;
					// No castle
					if(      index == k_rook ) {
						update_params[counter][1+castle_offset] = 0;
					}
					else if( index == q_rook ) {
						update_params[counter][2+castle_offset] = 0;
					}
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
	queen_counter++;
					counter++;
					n_count++;
				}
				else if( board_in[index_update]*i_turn < 0 ) {
					to_square[counter] = index_update;
	queen_counter++;
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

				check_check( index_update, board_in, board_params, check_pieces, &n_checks );
	//cout << " index, n_checks = " << index_update << " " << n_checks << endl;
				if( n_checks == 0 ) {
					to_square[counter] = index_update;
	king_counter++;
					update_params[counter][1+castle_offset] = 0;
					update_params[counter][2+castle_offset] = 0;
					counter++;
				}
			}
		}
	break;

	}

	*possem = counter;

	return;
}
