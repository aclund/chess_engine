#include "functions.h"
#include "piece_moves.h"

void all_moves( Chess_Board chess_board, vector<Moves>& moves_add ) {

	int n_moves = 0;

	int i_turn;
	Pieces *your_pieces, *their_pieces;

	// Seperate Chess Board to move King (check_check)
	int n_checks;
	Chess_Board chess_moved;
	Pieces *s_your_pieces, *s_their_pieces;

	switch( chess_board.Parameters & 1 ) {
	  case 0: // White to Move
		your_pieces  = &chess_board.White;
		their_pieces = &chess_board.Black;
		i_turn = 1;

		s_your_pieces  = &chess_moved.White;
		s_their_pieces = &chess_moved.Black;
	  break;
	  case 1: // Black to Move
		your_pieces  = &chess_board.Black;
		their_pieces = &chess_board.White;
		i_turn = -1;

		s_your_pieces  = &chess_moved.Black;
		s_their_pieces = &chess_moved.White;
	  break;
	}

	int t_en_passant = ( ((1 << 19) - 1) & (chess_board.Parameters >> 12));
	if( t_en_passant == 0 ) { t_en_passant = -1; } //cout << t_en_passant << " t_en_passant\n";

	uint64_t not_all_pieces = ~chess_board.All_Pieces;

	//n_moves = piecey_pie_moves( &moves_add[n_moves], your_pieces, their_pieces->All,
	//			    not_all_pieces, t_en_passant, i_turn );

///*
//Legal Move Check

	Moves *moves_all = newMoves( chess_board.Parameters, max_moves );
	int  n_moves_all = piecey_pie_moves( moves_all, your_pieces, their_pieces->All,
					     not_all_pieces, t_en_passant, i_turn );

	for( int n = 0; n < n_moves_all; n++ ) {
		chess_moved = preform_move( chess_board, moves_all[n] );
		check_check( s_your_pieces->King, s_your_pieces->All, s_their_pieces, 
			     ~chess_moved.All_Pieces, i_turn, &n_checks );
		//cout << " # checks = " << n_checks << " move piece " << moves_all[n].piece << endl;
		if( n_checks == 0 ) {
			moves_add.push_back(moves_all[n]);
			n_moves++;
		}
	}
//*/

	// Castling Rights
	check_check( your_pieces->King, your_pieces->All, their_pieces, 
		     ~chess_board.All_Pieces, i_turn, &n_checks );
	if( n_checks != 0 ) { return; }

	int bit_offset = 0 + (1-i_turn);
	int index_king = 4 + (1-i_turn)*28;
	
	Moves *castle_through = newMoves( chess_board.Parameters, 1 );
	castle_through[0].piece = king;

	//Castle King
	if( (chess_board.Parameters >> (1+bit_offset)) & 1 and
	    (not_all_pieces >> (index_king+1)) & 1 and
	    (not_all_pieces >> (index_king+2)) & 1 ) {
		// Square+1
		castle_through[0].bitmove = your_pieces->King;
		BIT_SET( castle_through[0].bitmove, index_king+1 );
		chess_moved = preform_move( chess_board, castle_through[0] );
		check_check( s_your_pieces->King, s_your_pieces->All, s_their_pieces, 
			     ~chess_moved.All_Pieces, i_turn, &n_checks );
		if( n_checks == 0 ) {
			// Square+2
			castle_through[0].bitmove = your_pieces->King;
			BIT_SET( castle_through[0].bitmove, index_king+2 );
			chess_moved = preform_move( chess_board, castle_through[0] );
			check_check( s_your_pieces->King, s_your_pieces->All, s_their_pieces, 
				     ~chess_moved.All_Pieces, i_turn, &n_checks );
			if( n_checks == 0 ) {
				// CAN Castle
				BIT_SET( moves_all[n_moves_all].bitmove, index_king   );
				BIT_SET( moves_all[n_moves_all].bitmove, index_king+3 );
				moves_all[n_moves_all].piece = 7;
				BIT_CLEAR( moves_all[n_moves_all].parameters, 1 + bit_offset );;
				BIT_CLEAR( moves_all[n_moves_all].parameters, 2 + bit_offset );;
				moves_add.push_back(moves_all[n_moves_all]);
				n_moves_all++;
			}
		}
	}
	// Castle Queen
	if( (chess_board.Parameters >> (2+bit_offset)) & 1 and
	    (not_all_pieces >> (index_king-1)) & 1 and
	    (not_all_pieces >> (index_king-2)) & 1 and
	    (not_all_pieces >> (index_king-3)) & 1 ) {
		// Square-1
		castle_through[0].bitmove = your_pieces->King;
		BIT_SET( castle_through[0].bitmove, index_king-1 );
		chess_moved = preform_move( chess_board, castle_through[0] );
		check_check( s_your_pieces->King, s_your_pieces->All, s_their_pieces, 
			     ~chess_moved.All_Pieces, i_turn, &n_checks );
		if( n_checks == 0 ) {
			// Square-2
			castle_through[0].bitmove = your_pieces->King;
			BIT_SET( castle_through[0].bitmove, index_king-2 );
			chess_moved = preform_move( chess_board, castle_through[0] );
			check_check( s_your_pieces->King, s_your_pieces->All, s_their_pieces, 
				     ~chess_moved.All_Pieces, i_turn, &n_checks );
			if( n_checks == 0 ) {
				// CAN Castle
				BIT_SET( moves_all[n_moves_all].bitmove, index_king   );
				BIT_SET( moves_all[n_moves_all].bitmove, index_king-4 );
				moves_all[n_moves_all].piece = 7;
				BIT_CLEAR( moves_all[n_moves_all].parameters, 1 + bit_offset );;
				BIT_CLEAR( moves_all[n_moves_all].parameters, 2 + bit_offset );;
				moves_add.push_back(moves_all[n_moves_all]);
				n_moves_all++;
			}
		}
	}
		
	delete[] castle_through;
	delete[] moves_all;

	return;
}
