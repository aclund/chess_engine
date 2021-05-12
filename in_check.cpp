//#include <math.h>
#include <iostream>
using namespace std;

#include "functions.h"
#include "global.h"
#include "initialize.h"
#include "convert_binary.h"
#include "piece_moves.h"
#include "check_check.h"

//void in_check( int *board_in, int *board_params, int *pins, int index_check, int *out_check_pieces, int *valid_squares, int *check_possem) {

int in_check( Moves *moves_add, Chess_Board chess_board, Moves_temp bad_boy, uint64_t pinned, int t_en_passant ) {

	int i_spot = 0;

	int i_turn;
	Pieces *your_pieces, *their_pieces;
	switch( chess_board.Parameters & 1 ) {
	  case 0: // White to Move
		your_pieces  = &chess_board.White;
		their_pieces = &chess_board.Black;
		i_turn = 1;
	  break;
	  case 1: // Black to Move
		your_pieces  = &chess_board.Black;
		their_pieces = &chess_board.White;
		i_turn = -1;
	  break;
	}

	int index_king = 0;
	convert_binary( your_pieces->King, &index_king );

	// Figure out whos tryna murder your broke ass
	int index_check = 0;
	//print_binary( bad_boy.bitmove ); cout << endl;
	convert_binary( bad_boy.bitmove, &index_check );


	// Can move king out of check
	Moves *moves_around = newMoves( chess_board.Parameters, max_moves );
	int n_king_moves = king_moves( moves_around, your_pieces->King, your_pieces->All, their_pieces, 
				       ~chess_board.All_Pieces, i_turn );
cout << " n_king_moves " << n_king_moves << endl;
	uint64_t squirrel_that_king;
	Moves_temp *check_pieces = newTemp(2);
	int n_checks;
	for( int i = 0; i < n_king_moves; i++ ) {
		squirrel_that_king  = your_pieces->King;
		squirrel_that_king ^= moves_around[i].bitmove;
		check_check( squirrel_that_king, your_pieces->All, their_pieces, ~chess_board.All_Pieces,
			     i_turn, check_pieces, &n_checks );
cout << i << " n_checks " << n_checks << endl;
		if( n_checks == 0 ) {
			moves_add[i_spot] = moves_around[i];
			i_spot++;
		}
	}
	free( moves_around );


	// Capture out of check
	Moves *moves_capture = newMoves( chess_board.Parameters, max_moves );
	
	int np_captures = piecey_pie_moves( &moves_capture[0], your_pieces, their_pieces->All,
					    ~chess_board.All_Pieces, ~pinned, t_en_passant, i_turn );
	for( int n = 0; n < np_captures; n++ ) {
		if( (bad_boy.bitmove & moves_capture[n].bitmove) != 0 ) {
			moves_add[i_spot] = moves_capture[n];
			i_spot++;
		}
	}
	free( moves_capture );


	// Otherwise you got to block that bitch
	bool block_check = false; 

	// Easier to work in row col space
	int king_row, king_col, check_row, check_col;
	index2rc( index_king,  &king_row,  &king_col);
	index2rc(index_check, &check_row, &check_col);

	// Also find the coordinate direction
	int n_direction = -1;
	if( (bad_boy.piece) == queen or (bad_boy.piece) == bishop or (bad_boy.piece) == rook ) {
//cout << "Piece " <<bad_boy.piece << " @ " << index_check << " " << index_king << endl;
		// From king reference
		block_check = true;
		if(      king_col == check_col && check_row > king_row ) n_direction = 0; //n
		else if( king_row == check_row && check_col > king_col ) n_direction = 1; //e
		else if( king_col == check_col && check_row < king_row ) n_direction = 2; //s
		else if( king_row == check_row && check_col < king_col ) n_direction = 3; //w

		else if( (index_king - index_check)%9 == 0 && index_check > index_king ) n_direction = 4; //ne
		else if( (index_king - index_check)%7 == 0 && index_check < index_king ) n_direction = 5; //se
		else if( (index_king - index_check)%9 == 0 && index_check < index_king ) n_direction = 6; //sw
		else if( (index_king - index_check)%7 == 0 && index_check > index_king ) n_direction = 7; //nw
		else { cout << " ERROR in_check. No direction found!\n"; return 0; }
		//cout << "n_direction = " << n_direction << endl;
	}

	int n_count = 0, index_update;
	uint64_t block_squares[6] = {0,0,0,0,0,0};
	if( block_check ) {
		n_count = 0;
		index_update = index_king + index_directions[n_direction];
		while( index_update != index_check ) {
			BIT_SET( block_squares[n_count], index_update);
			//cout << " block_squares "; print_binary(block_squares[n_count]); cout << endl;
			n_count++;
			if( index_update < 0 or index_update > 63 ) {
				cout << " ERROR in_check. Wrong direction found\n";
				return 0;
			}
			index_update += index_directions[n_direction];
		}

		Moves *moves_block = newMoves( chess_board.Parameters, max_moves );
		int np_blocks = piecey_pie_moves( &moves_block[0], your_pieces, their_pieces->All,
						  ~chess_board.All_Pieces, ~pinned, t_en_passant, i_turn );
		for( int n = 0; n < np_blocks; n++ ) {
			for( int jugs = 0; jugs < n_count; jugs++ ) {
				if( (block_squares[jugs] & moves_block[n].bitmove) != 0 ) {
					moves_add[i_spot] = moves_block[n];
					i_spot++;
				}
			}
		}
		free( moves_block );
	}


	return i_spot;
}
