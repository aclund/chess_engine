#include <iostream>

using namespace std;

#include "functions.h"
#include "global.h"

int pawn_rel_rank( int i ) {
	int rel_rank = (1-turn)*4.5 + (int(i/8) + 1)*turn;
	//cout << "i, rel_rank = " << i << " "<< rel_rank << "\n";
	return rel_rank; 
}

void store_board( int board_in[64], int **possible_boards, int piece, int index_from, int index_update ) {
	//cout << " index_from, index_update = " << index_from << "  " << index_update << "\n";
	for( int i = 0; i < 64; i++ ) {
		if( i == index_from ) {
			possible_boards[n_possible_moves][i] = 0; 
		}
		else if( i == index_update ) {
			possible_boards[n_possible_moves][i] = turn*piece;
		}
		else {	
			possible_boards[n_possible_moves][i] = board_in[i];
		}
	}
	n_possible_moves++;
	return;
}

void all_moves(int *board_in, int **possible_boards) {

	int n_count, index_update;
	int promote_pieces = 4;

	for( int index = 0; index < 64; index++ ) {

		if( board_in[index]*turn > 0 ) { // Your piece on square

			if( abs(board_in[index]) == pawn ) { // PAWNS
				index_update = index + 8*turn;  // Square in front
				if( board_in[index_update] == 0 ) {
					if( pawn_rel_rank(index_update) == 8 ) { // PROMOTE
						for( int n = 0; n < promote_pieces; n++ ) {
							store_board( board_in, possible_boards, n+2, index, index_update );
						}
					} else{ store_board( board_in, possible_boards, pawn, index, index_update ); }
				}
				index_update = index + 16*turn; // Up two beginning 
				if( board_in[index_update] == 0 &&
				    pawn_rel_rank(index) == 2 ) {
					store_board( board_in, possible_boards, pawn, index, index_update );
				}
				index_update = index + 7*turn;
				if( board_in[index_update]*turn < 0 or 
				    en_passant == index_update ) { // Capturable left
					store_board( board_in, possible_boards, pawn, index, index_update );
				}
				index_update = index + 9*turn;
				if( board_in[index_update]*turn < 0 or
				    en_passant == index_update ) { // Capturable right
					store_board( board_in, possible_boards, pawn, index, index_update );
				}
			}

			else if( abs(board_in[index]) == knight ) {
				for( int n_moves = 0; n_moves < n_knight_moves[index]; n_moves++ ) {
					if( board_in[knight_moves[index][n_moves]]*turn <= 0 ) {
						store_board( board_in, possible_boards, knight, index, knight_moves[index][n_moves] );
					}
				}
			}

			else if( abs(board_in[index]) == bishop ) {
				for( int n_direction = 4; n_direction < 8; n_direction++ ) {
					n_count = 0;
					index_update = index;
					while( n_count < count_to_edge[index][n_direction] ) {
						index_update += index_directions[n_direction];
						if( board_in[index_update] == 0 ) {
							store_board( board_in, possible_boards, bishop, index, index_update );
							n_count++;
						}
						else if( board_in[index_update]*turn < 0 ) {
							store_board( board_in, possible_boards, bishop, index, index_update );
							n_count = 7;
						}
						else { n_count = 7; }
					}
				}
			}

			else if( abs(board_in[index]) == rook ) {
				for( int n_direction = 0; n_direction < 4; n_direction++ ) {
					n_count = 0;
					index_update = index;
					while( n_count < count_to_edge[index][n_direction] ) {
						index_update += index_directions[n_direction];
						if( board_in[index_update] == 0 ) {
							store_board( board_in, possible_boards, rook, index, index_update );
							n_count++;
						}
						else if( board_in[index_update]*turn < 0 ) {
							store_board( board_in, possible_boards, rook, index, index_update );
							n_count = 7;
						}
						else { n_count = 7; }
					}
				}
			}

			else if( abs(board_in[index]) == queen ) {
				for( int n_direction = 0; n_direction < 8; n_direction++ ) {
					n_count = 0;
					index_update = index;
					while( n_count < count_to_edge[index][n_direction] ) {
						index_update += index_directions[n_direction];
						if( board_in[index_update] == 0 ) {
							store_board( board_in, possible_boards, queen, index, index_update );
							n_count++;
						}
						else if( board_in[index_update]*turn < 0 ) {
							store_board( board_in, possible_boards, queen, index, index_update );
							n_count = 7;
						}
						else { n_count = 7; }
					}
				}
			}

			else if( abs(board_in[index]) == king ) {
				for( int n_direction = 0; n_direction < 8; n_direction++ ) {
					n_count = 0;
					index_update = index + index_directions[n_direction];
					if( count_to_edge[index][n_direction] != 0 &&
					    board_in[index_update]*turn <= 0 ) {
						store_board( board_in, possible_boards, king, index, index_update );
					}
					// Castle
					bool castle = false;
					if( castle ) {
					}
				}
			}

			else { cout << "ERROR: board_in in all_moves\n"; }

		}
	}


	return;
}
