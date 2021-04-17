#include <iostream>

using namespace std;

#include "functions.h"
#include "global.h"

int n_open;

void store_board( int board_update[64], int *update_params, int **possible_boards, int **possible_params,
		  int piece, int index_from, int index_update ) {
	//cout << " index_from, index_update = " << index_from << "  " << index_update << "\n";
	for( int i = 0; i < 64; i++ ) {
		possible_boards[n_open][i] = board_update[i];
	}
	possible_boards[n_open][index_from] = 0; 
	possible_boards[n_open][index_update] = piece;

	// Store new params
	for( int n = 0; n < n_params; n++ ) {
		possible_params[n_open][n] = update_params[n];
	}

	n_open++;
	n_possible_moves++;

	return;
}

void all_moves( int *board_in, int *board_params, int **possible_boards, int **possible_params ) {

	n_open = 0;

	int max_moves = 27;
        int **update_params = new int*[max_moves];
        for( int i = 0; i < max_moves; i++ ) {
                update_params[i] = new int[n_params];
		for( int n = 0; n < n_params-1; n++ ) {
			update_params[i][n] = board_params[n];
		}
		update_params[i][5] = -1;
	}

	int i_turn = board_params[0];
	int n_count, index_update, index_king, piece, possem, check_possem;
	int n_checks = 0, n_not_free = 0;
	int pins[64], to_squares[max_moves], check_pieces[2], null_check[2], out_check_pieces[max_moves];
	int promote_pieces = 4;
	int castle_offset = 0;
	if( i_turn == -1 ) { castle_offset = 2; }

	// index_king
	for( int index = 0; index < 64; index++ ) {
		if( board_in[index] == i_turn*king ) {
			index_king = index;
			break;
		}
	}

	check_check( index_king, board_in, board_params, check_pieces, &n_checks );

	// Find all pinned pieces AND can move out of single pin with capture
	int save_piece, n_check_pins;
	for( int index = 0; index < 64; index++ ) {
		n_check_pins = 0;
		if( board_in[index]*i_turn > 0 && abs(board_in[index]) != king ) { // Your piece on square
			save_piece      = board_in[index];
			board_in[index] = 0;       // Remove and check_check
			check_check( index_king, board_in, board_params, check_pieces, &n_check_pins );
			board_in[index] = save_piece;

			if( n_check_pins > n_checks ) { // Pin = true
				piece_moves( board_in, board_params, update_params, index, to_squares, &possem );
				for( int i = 0; i < possem; i++ ) {
					if( to_squares[i] == check_pieces[0] ) { // Capture pin

						store_board( board_in, update_params[0], possible_boards, possible_params, 
                                        		     save_piece, index, check_pieces[0] );

						// Move along pin
						int total_direction = check_pieces[0] - index;
						int piece_case = save_piece; 
						if( piece_case == queen ) {
							if(      total_direction%7 == 0 ) piece_case = 3;
							else if( total_direction%9 == 0 ) piece_case = 3;
							else piece_case = 4;
						}

						int open_squares = 0;
						switch (piece_case) {
						case 3: // diag
							if(      total_direction%7 == 0 ) {
								open_squares = total_direction/7 - 1;
							}
							else if( total_direction%9 == 0 ) {
								open_squares = total_direction/9 - 1;
							}
						break;
						case 4: // file
							if(      total_direction%8 == 0 ) {
								open_squares = total_direction/8 - 1;
							}
							else {
								open_squares = total_direction/1 - 1;
							}
						break;
						}

						for( int s = 0; s < open_squares; s++ ) {
							int dir = total_direction/(open_squares+1);
							store_board( board_in, update_params[0], possible_boards,
							   possible_params, save_piece, index, index+(s+1)*dir );
						}

					}
					// Reset params
					for( int n = 0; n < n_params-1; n++ ) {
						update_params[i][n] = board_params[n];
					}
					update_params[i][5] = -1;
				}
			}
		}
		pins[index] = n_check_pins - n_checks; // Could be > 1
	}

	if( n_checks > 0 ) {
		if( n_checks == 2 ) {
			piece_moves( board_in, board_params, update_params, index_king, to_squares, &possem );
			for( int i = 0; i < possem; i++ ) {
				check_check( to_squares[i], board_in, board_params, null_check, &n_not_free );
				if( n_not_free == 0 ) {
					store_board( board_in, update_params[i], possible_boards, possible_params,
					             king, index_king, to_squares[i] );
					possible_params[n_open][1+castle_offset] = 0;
					possible_params[n_open][2+castle_offset] = 0;
				}
			}
		}
		else {
			in_check( board_in, board_params, pins, check_pieces[0], out_check_pieces,
				  to_squares, &check_possem );
			for( int i = 0; i < check_possem; i++ ) { 

				store_board( board_in, update_params[i], possible_boards, possible_params,
					     board_in[out_check_pieces[i]], out_check_pieces[i], to_squares[i] );

				// Reset params
				for( int n = 0; n < n_params-1; n++ ) {
					update_params[i][n] = board_params[n];
				}
				update_params[i][5] = -1;
			}
		}

		// Delete temp params
        	for( int i = 0; i < max_moves; i++ ) {
        	        delete [] update_params[i];
		}
		delete [] update_params;

		return;
	}

	// Find moves not involving check
	int i_en_passant;
	for( int index = 0; index < 64; index++ ) {

		if( board_in[index]*i_turn > 0 && pins[index] == 0 ) { // Your piece on square can move

			piece_moves( board_in, board_params, update_params, index, to_squares, &possem );

			for( int i = 0; i < possem; i++ ) {

				store_board( board_in, update_params[i], possible_boards, possible_params,
					     board_in[index], index, to_squares[i] );

				// Capture en passant
				if( abs(board_in[index]) == pawn && to_squares[i] == board_params[5] ) { 
					i_en_passant = to_squares[i] - 8*board_params[0];
					possible_boards[n_open-1][i_en_passant] = 0;
				}

				// Castle
	int castle_offset = 0;
	if( i_turn == -1 ) castle_offset = 2;
	bool castle_k = false, castle_q = false;
        if( board_params[1+castle_offset] == 1 ) castle_k = true;
        if( board_params[2+castle_offset] == 1 ) castle_q = true;

				// Reset params
				for( int n = 0; n < n_params-1; n++ ) {
					update_params[i][n] = board_params[n];
				}
				update_params[i][5] = -1;
			}

		}
	}

	// Delete temp params
        for( int i = 0; i < max_moves; i++ ) {
                delete [] update_params[i];
	}
	delete [] update_params;

	return;
}
