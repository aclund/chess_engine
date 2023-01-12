#include "functions.h"
#include "piece_moves.h"

uint8_t piece_convert(char piece) {
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

int valid_move( Chess_Board bitboards, string move_AN, vector<Moves> moves_add, int *target ) {

	int ierr = 0;

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

	int board[64], params[6];
	convert2board( bitboards, board, params );

	// If castle
	uint64_t king_spot = 0;
	int n_checks;
	if( move_AN.find('o') != string::npos ) {

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
					     ~bitboards.All_Pieces, i_turn, &n_checks );
				if( n_checks != 0 ) {
					cout << " Castling through check!\n";
					return 1;
				}
			}
			move_piece = 7;
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
					     ~bitboards.All_Pieces, i_turn, &n_checks );
				if( n_checks != 0 ) {
					cout << " Castling through check!\n";
					return 1;
				}
			}
			move_piece = 7;
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
	uint8_t promote_piece;
	if( move_AN.find('=') != string::npos ) {
		promote = true;
		read = move_AN[move_AN.find('=')+1];
		if( string_move_piece.find(read) == string::npos ) {
			cout << " CANNOT convert inputted promotion!\n";
			return 1;
		}
		promote_piece = piece_convert(read) + 6;
		//cout << promote_piece << endl;
	}

	// Convert user input to move
	if( !found_piece ) {
		for( int n_read = 0; n_read < move_AN.length(); n_read++ ) {
				read = move_AN[n_read];
				if(  string_move_piece.find(read) != string::npos &&
						move_AN.length() != 2 && !found_piece ) {
						move_piece = piece_convert(read);
						found_piece = true;
				}
				else if( move_letter_square.find(read) != string::npos ) {
						move_square.insert( 0, &read );
						letters++;
				}
				else if( move_number_square.find(read) != string::npos &&
					 letters != 0 ) {
						move_square.insert( 1, &read );
						numbers++;
				}
		}
		if( !found_piece ) { move_piece = pawn; }
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
		if( promote ) { move_piece = promote_piece; }

		// Find and check target square
		index_square(move_square, &move_row, &move_column); 
		move_index = rc2index(move_row, move_column);
		//cout<< move_piece << "   " << move_row << " : " << move_column << " move_index = " << move_index <<endl;

		if( board[move_row*8+move_column]*i_turn > 0 ) { // Your piece on square
			cout << "Occupado\n";
			return 1;
		}
	}

	int duplicate_shield = 0;
	int found[2] = {-1,-1};
	for( int n = 0; n < moves_add.size(); n++ ) {
		if( moves_add[n].piece == move_piece or (abs(move_piece)==pawn and moves_add[n].piece == 12) ) {
			int indices[3] = {-1,-1,-1};
			convert_binary( moves_add[n].bitmove, indices );
			int i = 0;
			while( indices[i] != -1 ) {
				if( indices[i] == move_index ) {
					found[duplicate_shield] = n;
					duplicate_shield++;
				}
				i++;
			}
		}
	}
	if(      duplicate_shield == 0 ) { ierr = 1; }
	else if( duplicate_shield >  1 ) { // Duplicate
		char identifier = move_AN[1];

		int options = 2, distinguish = -1;
		while( options != 0 ) {
			int index, flipper = options - 1, flipper1 = options%2;
			uint64_t p_move = moves_add[found[flipper]].bitmove;
			p_move &= ~moves_add[found[flipper1]].bitmove;
			convert_binary( p_move, &index );

			string in_square = index2square( index );
			if( in_square.find( identifier ) != string::npos ) { distinguish = flipper; break; }

			options--;
		}

		if( distinguish == -1 ) {
			cout << "ERROR: duplicate move not identified! Second character input MUST distinguish move\n";
			ierr = 1;
		}
		else {
			*target = found[distinguish];
		}
	}
	else {
		*target = found[0];
	}

	return ierr;
}
