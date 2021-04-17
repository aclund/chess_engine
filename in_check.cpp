#include <iostream>
#include <math.h>

using namespace std;

#include "functions.h"
#include "global.h"

void in_check( int *board_in, int *board_params, int *pins, int check_index,
	       int *out_check_pieces, int *valid_squares, int *check_possem) {

	int counter = 0;

	// Don't update params on search
	int max_moves = 27;
	int to_squares[max_moves];
        int **null_params = new int*[max_moves];
        for( int i = 0; i < max_moves; i++ ) {
                null_params[i] = new int[n_params];
	}

	int i_turn = board_params[0];

	int index_king, possem;

	// If in CHECK
	for( int index = 0; index < 64; index++ ) {
		if( board_in[index] == i_turn*king ) {
			index_king = index;
			break;
		}
	}

	// Can move king out of check
	int n_not_free, null_check[2];
	piece_moves( board_in, board_params, null_params, index_king, to_squares, &possem );
	for( int i = 0; i < possem; i++ ) {
		check_check( to_squares[i], board_in, board_params, null_check, &n_not_free );
		//cout << " move " << i << "index " << to_squares[i] << " n_not_free " << n_not_free << endl;
		if( n_not_free == 0 ) {
			valid_squares[counter] = to_squares[i];
			out_check_pieces[counter] = index_king;
			counter++;
		}
	}

	// Capture out of check
	for( int index = 0; index < 64; index++ ) {
		if( board_in[index]*board_params[0] > 0 && pins[index] == 0 ) { // Your piece
			piece_moves( board_in, board_params, null_params, index, to_squares, &possem );
			for( int i = 0; i < possem; i++ ) {
				if( to_squares[i] == check_index ) {
					valid_squares[counter] = to_squares[i];
					out_check_pieces[counter] = index;
		//cout << " check capture to from " << valid_squares[counter] << " " << out_check_pieces[counter]<<endl;
		//cout << "possem = " << possem << " to " << to_squares[i] << endl;
					counter++;
				}
			}
		}
	}

	// Otherwise you got to block that bitch
	bool block_check = false; 
	int check_piece = board_in[check_index];
	// Easier to work in row col space
	int king_row, king_col, check_row, check_col;
	index2rc( index_king,  &king_row,  &king_col);
	index2rc(check_index, &check_row, &check_col);
	// Also find the coordinate direction
	int n_direction = -1;
	if( abs(check_piece) == queen or abs(check_piece) == bishop or abs(check_piece) == rook ) {
		//From king reference
		block_check = true;
		if(      king_col == check_col && check_row > king_row ) n_direction = 0; //n
		else if( king_row == check_row && check_col > king_col ) n_direction = 1; //e
		else if( king_col == check_col && check_row < king_row ) n_direction = 2; //s
		else if( king_row == check_row && check_col < king_col ) n_direction = 3; //w
		else if( (index_king - check_index)%9 == 0 && check_index > index_king ) n_direction = 4; //ne
		else if( (index_king - check_index)%7 == 0 && check_index < index_king ) n_direction = 5; //se
		else if( (index_king - check_index)%9 == 0 && check_index < index_king ) n_direction = 6; //sw
		else if( (index_king - check_index)%7 == 0 && check_index > index_king ) n_direction = 7; //nw
		else { cout << " ERROR in_check. No direction found!\n"; return; }
		//cout << "n_direction = " << n_direction << endl;
	}

	int n_count = 0, index_update, block_squares[6];
	if( block_check ) {
		n_count = 0;
		index_update = index_king + index_directions[n_direction];
		while( index_update != check_index ) {
			block_squares[n_count] = index_update;
			//cout << " block_squares " << block_squares[n_count] << endl;
			n_count++;
			if( index_update < 0 or index_update > 63 ) {
				cout << " ERROR in_check. Wrong direction found\n";
				return;
			}
			index_update += index_directions[n_direction];
		}
		for( int index = 0; index < 64; index++ ) {
			if( board_in[index]*board_params[0] > 0 &&
			    abs(board_in[index]) != king && pins[index] == 0 ) { // Your piece

				piece_moves( board_in, board_params, null_params, 
					     index, to_squares, &possem );

				for( int i = 0; i < possem; i++ ) {
					for( int j = 0; j < n_count; j++ ) {
						if( to_squares[i] == block_squares[j] ) {
							valid_squares[counter] = to_squares[i];
							out_check_pieces[counter] = index;
							counter++;
						}
					}
				}
			}
		}
	}


	*check_possem = counter;


	// Delete temp params
        for( int i = 0; i < max_moves; i++ ) {
                delete [] null_params[i];
	}
	delete [] null_params;

	return;
}
