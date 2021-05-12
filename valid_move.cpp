#include <string>
#include <iostream>
#include<bits/stdc++.h>

using namespace std;

#include "functions.h"
#include "global.h"
#include "initialize.h"
#include "convert_binary.h"
#include "piece_moves.h"
#include "check_check.h"
#include "preform_move.h"

int piece_convert(char piece) {
	if(	   piece == 'p' ) {
		return pawn;
	} else if( piece == 'n' ) {
		return knight;
	} else if( piece == 'b'  ) {
		return bishop;
	} else if( piece == 'r' ) {
		return rook;
	} else if( piece == 'q' ) {
		return queen;
	} else if( piece == 'k' ) {
		return king;
	}
	return 0;
}

int valid_move( string move_AN, int *moves_found, int ierr ) {

	ierr = 0;

	string string_move_piece  = "rnbqkp";
	string move_letter_square = "abcdefgh";
	string move_number_square = "12345678";

	// Check move string in range
	string move_square;
	int numbers = 0;
	int letters = 0;
	char read;
	bool found_piece = false;

	// Lower case input
	transform(move_AN.begin(), move_AN.end(), move_AN.begin(), ::tolower);

        int i_turn;
	Pieces *your_pieces, *their_pieces;
        switch( bitboards.Parameters & 1 ) {
          case 0: // White to Move
                your_pieces  = &bitboards.White;
                their_pieces = &bitboards.Black;
                i_turn = 1;
          break;
          case 1: // Black to Move
                your_pieces  = &bitboards.Black;
                their_pieces = &bitboards.White;
                i_turn = -1;
          break;
	}

	// If castle
	uint64_t king_spot = 0;
	Moves_temp *check_pieces = newTemp(2);
	int n_checks;
	if( move_AN.find('o') != string::npos ) {
		*moves_found = -1;

		int castle_o = 0;
		for( int n_read = 0; n_read < move_AN.length(); n_read++ ) {
			read = move_AN[n_read];
			if( read == 'o' ) castle_o++;
		}

        	int castle_offset = 0;
        	int color_offset = 0;
        	if( params[0] == -1 ) { castle_offset = 2; color_offset = 56; }

		// King/Rook positions rc
		int castle_row = 0 + 7*((1-params[0])/2);
		int king_col   = 4;

		if(      castle_o == 2 && params[1+castle_offset] == 1 &&
		    board[castle_row*8+king_col+1] == 0 &&
		    board[castle_row*8+king_col+2] == 0 ) { // castle_k

			int index_s = rc2index(castle_row,king_col);
			for( int index = 0; index < 3; index++ ) {
				BIT_SET( king_spot, index_s+index );
				check_check( king_spot, your_pieces->All, their_pieces, 
					     ~bitboards.All_Pieces, i_turn, check_pieces, &n_checks );
				if( n_checks != 0 ) {
					cout << " Castling through check!\n";
					return 1;
				}
			}
			move_piece = 0;
			move_index = 7 + color_offset;
			found_piece = true;
		}
		else if( castle_o == 3 && params[2+castle_offset] == 1 &&
		    board[castle_row*8+king_col-1] == 0 && 
		    board[castle_row*8+king_col-2] == 0 && 
		    board[castle_row*8+king_col-3] == 0 ) { // castle_q

			int index_s = rc2index(castle_row,king_col);
			for( int index = 0; index < 3; index++ ) {
				BIT_SET( king_spot, index_s-index );
				check_check( king_spot, your_pieces->All, their_pieces, 
					     ~bitboards.All_Pieces, i_turn, check_pieces, &n_checks );
				if( n_checks != 0 ) {
					cout << " Castling through check!\n";
					return 1;
				}
			}
			move_piece = 0;
			move_index = 0 + color_offset;
			found_piece = true;
		}
		else {
			cout << " Can't castle!\n";
			return 1;
		}
	}

	//Promote
	bool promote = false;
	if( move_AN.find('=') != string::npos ) {
		promote = true;
	}

	// Convert user input to move
	if( !found_piece ) {
		for( int n_read = 0; n_read < move_AN.length(); n_read++ ) {
				read = move_AN[n_read];
				if(  string_move_piece.find(read) != string::npos &&
						move_AN.length() != 2 && !found_piece ) {
						move_piece = i_turn*piece_convert(read);
						found_piece = true;
				}
				else if( move_letter_square.find(read) != string::npos ) {
						move_square[0] = read;
						letters++;
				}
				else if( move_number_square.find(read) != string::npos ) {
						move_square[1] = read;
						numbers++;
				}
		}
		if( !found_piece ) { move_piece = i_turn*pawn; }
		if( numbers != 1 ) { cout << "ONE row number only!!!\n"; return 1; }
		if( letters  < 1 ) { cout << "NO square letter?\n"; return 1; }
		// b is a duplicate and semi handled
		else if( letters  > 1 ) {
				for( int n_read = 0; n_read < move_AN.length(); n_read++ ) {
                		read = move_AN[n_read];
                		if( move_letter_square.find(read) != string::npos ) {
                        		// Specify move_piece
						}
				}
		}

		// Find and check target square
		index_square(move_square, &move_row, &move_column); 
		move_index = rc2index(move_row, move_column);
		//cout<< move_piece << "   " << move_row << " : " << move_column << " move_index = " << move_index <<endl;

		if( board[move_row*8+move_column]*i_turn > 0 ) { // Your piece on square
			cout << "Occupado\n";
			return 1;
		}
	}

	Moves *moves_add = newMoves( bitboards.Parameters, max_moves );

	int n_possible_moves = 0;
	all_moves( bitboards, moves_add, &n_possible_moves );
	*moves_found = n_possible_moves;
	cout << "# Possible Moves = " << n_possible_moves << "\n";

	//print_moves( moves_add, n_possible_moves, your_pieces->All );

	for( int n = 0; n < n_possible_moves; n++ ) {
		if( moves_add[n].piece*i_turn == move_piece or (abs(move_piece)==pawn and moves_add[n].piece == 10) ) {
			int indices[3] = {-1,-1,-1};
			convert_binary( moves_add[n].bitmove, indices );
			int i = 0;
			while( indices[i] != -1 ) {
				if( indices[i] == move_index ) {
cout << "Making Move...\n";
					bitboards = preform_move( bitboards, moves_add[n] );
					
					free( moves_add );
					return 0;
				}
				i++;
			}
		}
	}	

	free( moves_add );

	// Move not found!
	return 1;
}
