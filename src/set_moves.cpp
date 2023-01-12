#include "functions.h"

void set_moves( ) {

//	Find all knight moves for each square
	int i_knight_moves[8] = { -17, -15, -10, -6, 6, 10, 15, 17 };
	int r_knight_moves[8] = { -2, -2, -1, -1,  1,  1,  2,  2 };
	int c_knight_moves[8] = { -1,  1, -2,  2, -2,  2, -1,  1 };
	int index_update, row_update, col_update;
	int index_current = 0, n_count = 0;
	for( int row = 0; row < 8; row++ ) {
		for( int col = 0; col < 8; col++ ) {
                        n_knight_moves[index_current] = 0;
			for( int n_moves = 0; n_moves < 8; n_moves++ ) {
				knight_squares[index_current][n_moves] = 0;
				index_update = index_current + i_knight_moves[n_moves];
				row_update = row + r_knight_moves[n_moves];
				col_update = col + c_knight_moves[n_moves];
				if( in_range(row_update,col_update) ) {
                                        n_knight_moves[index_current]++;
					BIT_FLIP(knight_squares[index_current][n_count],index_update);
					n_count++;
				}
			}
			n_count = 0;
			index_current++;
		}
	}

	///*
	for( int i = 0; i < 64; i++ ) {
		//cout << "i, n_knights = " << i << "  " << n_knight_moves[i] << endl;
		for( int n = 0; n < n_knight_moves[i]; n++ ) {
			//print_binary( knight_squares[i][n] ); cout << endl;
		}
		//cout << "\n\n";
	}
	//*/

//	Calculate number of squares to edge for each direction
//                              n,  e,  s,  w, ne, se, sw, nw 
	index_current = 0;
	for( int row = 0; row < 8; row++ ) {
		for( int col = 0; col < 8; col++ ) {
			for( int n_direction = 0; n_direction < 8; n_direction++ ) {
				row_update = row;
				col_update = col;
				count_to_edge[index_current][n_direction] = -1;

				while( in_range(row_update,col_update) ) {
					count_to_edge[index_current][n_direction]++;
					row_update += row_directions[n_direction];
					col_update += col_directions[n_direction];
				}
			}
			index_current++;
		}
	}

	/*
	for( int i = 0; i < 64; i++ ) {
		for( int n = 0; n < 8; n++ ) {
			cout << count_to_edge[i][n] << " ";
		}
		cout << "\n";
	}
	*/

	// Add piece_scores to pst's
	for( int i = 0; i < 64; i++ ) {
		mg_pawn_table  [i] += mg_pieces[0];
		mg_knight_table[i] += mg_pieces[1];
		mg_bishop_table[i] += mg_pieces[2];
		mg_rook_table  [i] += mg_pieces[3];
		mg_queen_table [i] += mg_pieces[4];
		mg_king_table  [i] += mg_pieces[5];

		eg_pawn_table  [i] += eg_pieces[0];
		eg_knight_table[i] += eg_pieces[1];
		eg_bishop_table[i] += eg_pieces[2];
		eg_rook_table  [i] += eg_pieces[3];
		eg_queen_table [i] += eg_pieces[4];
		eg_king_table  [i] += eg_pieces[5];
	}

	return;
}
