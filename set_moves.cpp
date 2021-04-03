#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#include "functions.h"
#include "global.h"

void set_moves( ) {

	params[0] = turn; // turn
	params[1] =    1; // White Castle right
	params[2] =    1; // White Castle left
	params[3] =    1; // Black Castle right
	params[4] =    1; // Black Castle left
	params[5] =   -1; // en_passant

//	Find all knight moves for each square
	int i_knight_moves[8] = { -17, -15, -10, -6, 6, 10, 15, 17 };
	int r_knight_moves[8] = { -2, -2, -1, -1,  1,  1,  2,  2 };
	int c_knight_moves[8] = { -1,  1, -2,  2, -2,  2, -1,  1 };
	int index_update, row_update, col_update;
	int index_current = 0;
	int n_count = 0;
	for( int row = 0; row < 8; row++ ) {
		for( int col = 0; col < 8; col++ ) {
			n_knight_moves[index_current] = 0;
			for( int n_moves = 0; n_moves < 8; n_moves++ ) {
				index_update = index_current + i_knight_moves[n_moves];
				row_update = row + r_knight_moves[n_moves];
				col_update = col + c_knight_moves[n_moves];
				if( in_range(row_update,col_update) ) {
					n_knight_moves[index_current]++;
					knight_moves[index_current][n_count] = index_update;
					n_count++;
				}
			}
			n_count = 0;
			index_current++;
		}
	}

	/*
	for( int i = 0; i < 64; i++ ) {
		for( int n = 0; n < n_knight_moves[i]; n++ ) {
			cout << knight_moves[i][n] << " ";
		}
		cout << "\n";
	}
	*/

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

	return;
}
