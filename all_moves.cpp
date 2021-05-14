#include <iostream>
using namespace std;

#include "global.h"
#include "functions.h"
#include "initialize.h"
#include "convert_binary.h"
#include "piece_moves.h"
#include "check_check.h"
#include "preform_move.h"

void all_moves( Chess_Board chess_board, Moves *moves_add, int *n_possible_moves ) {

	int n_moves = 0;

	Pieces *your_pieces, *their_pieces;
	int i_turn;
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
	//cout << "i_turn =" << i_turn << endl;

        int t_en_passant = 0, bit2 = 32;
        for( int i = 5; i < 11; i++ ) {
                if( (chess_board.Parameters >> i) & 1 ) {
                        t_en_passant += bit2;
                }
                bit2 /= 2;
        }
	//cout << t_en_passant << " t_en_passant\n";

	uint64_t not_all_pieces = ~chess_board.All_Pieces;

	uint64_t null_pinned = 0;
	int n_moves_all = 0;
	Moves *moves_all = newMoves( chess_board.Parameters, max_moves );
	n_moves_all += piecey_pie_moves( &moves_all[n_moves_all], your_pieces, their_pieces->All,
					 not_all_pieces, ~null_pinned, t_en_passant, i_turn );
	n_moves_all += king_moves  ( &moves_all[n_moves_all], your_pieces->King, your_pieces->All, their_pieces, 
				 not_all_pieces, i_turn );
	//cout << " +King   Moves = " << n_moves << endl;

//print_moves( moves_all, n_moves_all, your_pieces->All );

	Moves_temp *check_pieces = newTemp(2);
	Chess_Board chess_moved;
	Pieces *s_your_pieces, *s_their_pieces;
	switch( chess_board.Parameters & 1 ) {
	  case 0: // White to Move
		s_your_pieces  = &chess_moved.White;
		s_their_pieces = &chess_moved.Black;
	  break;
	  case 1: // Black to Move
		s_your_pieces  = &chess_moved.Black;
		s_their_pieces = &chess_moved.White;
	  break;
	}

	int n_checks;
	for( int n = 0; n < n_moves_all; n++ ) {
		chess_moved = preform_move( chess_board, moves_all[n] );
		check_check( s_your_pieces->King, s_your_pieces->All, s_their_pieces, 
			     ~chess_moved.All_Pieces, i_turn, check_pieces, &n_checks );
//cout << " # checks = " << n_checks << " move piece " << moves_all[n].piece << endl;
		if( n_checks == 0 ) {
			moves_add[n_moves] = moves_all[n];
			n_moves++;
		}
	}

	check_check( your_pieces->King, your_pieces->All, their_pieces, 
		     ~chess_board.All_Pieces, i_turn, check_pieces, &n_checks );
	if( n_checks != 0 ) { *n_possible_moves = n_moves; return; }
	// CAN Castle
	int bit_offset = 0;
	int index_king = 4;
	if( i_turn == -1 ) {
		bit_offset = 2;
		index_king = 60;
	}
	
	//uint64_t castle_through;
	Moves *castle_through = newMoves( chess_board.Parameters, 1 );
	castle_through[0].piece = king;
	
	if( (chess_board.Parameters >> (1+bit_offset)) & 1 and
	    (not_all_pieces >> (index_king+1)) & 1 and
	    (not_all_pieces >> (index_king+2)) & 1 ) {  // Castle king
		castle_through[0].bitmove = your_pieces->King;
		BIT_SET( castle_through[0].bitmove, index_king+1 );
		chess_moved = preform_move( chess_board, castle_through[0] );
		check_check( s_your_pieces->King, s_your_pieces->All, s_their_pieces, 
			     ~chess_moved.All_Pieces, i_turn, check_pieces, &n_checks );
		if( n_checks == 0 ) {
			castle_through[0].bitmove = your_pieces->King;
			BIT_SET( castle_through[0].bitmove, index_king+2 );
			chess_moved = preform_move( chess_board, castle_through[0] );
			check_check( s_your_pieces->King, s_your_pieces->All, s_their_pieces, 
				     ~chess_moved.All_Pieces, i_turn, check_pieces, &n_checks );
			if( n_checks == 0 ) {
		//cout << i_turn << " CAN Castle King\n";
				BIT_SET( moves_add[n_moves].bitmove, index_king   );
				BIT_SET( moves_add[n_moves].bitmove, index_king+3 );
				moves_add[n_moves].piece = 0;
				BIT_CLEAR( moves_add[n_moves].parameters, 1 + bit_offset );;
				BIT_CLEAR( moves_add[n_moves].parameters, 2 + bit_offset );;
				n_moves++;
			}
		}
	}
	if( (chess_board.Parameters >> (2+bit_offset)) & 1 and
	    (not_all_pieces >> (index_king-1)) & 1 and
	    (not_all_pieces >> (index_king-2)) & 1 and
	    (not_all_pieces >> (index_king-3)) & 1 ) {  // Castle queen
		castle_through[0].bitmove = your_pieces->King;
		BIT_SET( castle_through[0].bitmove, index_king-1 );
		chess_moved = preform_move( chess_board, castle_through[0] );
		check_check( s_your_pieces->King, s_your_pieces->All, s_their_pieces, 
			     ~chess_moved.All_Pieces, i_turn, check_pieces, &n_checks );
		if( n_checks == 0 ) {
			castle_through[0].bitmove = your_pieces->King;
			BIT_SET( castle_through[0].bitmove, index_king-2 );
			chess_moved = preform_move( chess_board, castle_through[0] );
			check_check( s_your_pieces->King, s_your_pieces->All, s_their_pieces, 
				     ~chess_moved.All_Pieces, i_turn, check_pieces, &n_checks );
			if( n_checks == 0 ) {
		//cout << i_turn << " CAN Castle Queen\n";
				BIT_SET( moves_add[n_moves].bitmove, index_king   );
				BIT_SET( moves_add[n_moves].bitmove, index_king-4 );
				moves_add[n_moves].piece = 0;
				BIT_CLEAR( moves_add[n_moves].parameters, 1 + bit_offset );;
				BIT_CLEAR( moves_add[n_moves].parameters, 2 + bit_offset );;
				n_moves++;
			}
		}
	}
		

	//cout << " # Possible Moves = " << n_moves << endl;
/*
	for( int n = 0; n < n_moves; n++ ) {
		print_binary(moves_add[n].bitmove); cout<<endl;
	}
*/
	*n_possible_moves = n_moves;
	return;
}
