#include <iostream>
using namespace std;

#include "global.h"
#include "functions.h"
#include "initialize.h"
#include "convert_binary.h"
#include "piece_moves.h"
#include "check_check.h"

int n_moves;

inline uint64_t find_pins(Moves*,uint16_t,Pieces*,Pieces*,uint64_t,Moves_temp,int,int,int);
inline int add_pin_moves(Moves*,uint16_t,uint64_t,uint64_t,Pieces*,Pieces*,uint64_t,uint64_t,uint64_t,int);

void all_moves( Chess_Board chess_board, Moves *moves_add, int *n_possible_moves ) {

	n_moves = 0;

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

	int n_checks;
	Moves_temp *check_pieces = newTemp(2);
	check_check( your_pieces->King, your_pieces->All, their_pieces, 
		     not_all_pieces, i_turn, check_pieces, &n_checks );

	// Double Check is simplest case
	if( n_checks == 2 ) {
		n_moves += king_moves  ( &moves_add[n_moves], your_pieces->King,    your_pieces->All, their_pieces, 
				 	 not_all_pieces, i_turn );
		*n_possible_moves = n_moves;
		return;
	}

	// Find Pinned Pieces
//BROKE
//cout << "Out of first check_check #" << n_checks; print_binary(check_pieces[0].bitmove);cout<<endl<<endl;
	uint64_t pinned = find_pins( &moves_add[n_moves], chess_board.Parameters, your_pieces, their_pieces, not_all_pieces,
				     check_pieces[0], n_checks, t_en_passant, i_turn );
	//cout << " Pinned = "; print_binary(pinned);cout << endl;

	// IF in CHECK
//cout << "n_checks :" << n_checks << endl;
	if( n_checks == 1 ) {
		n_moves += in_check( &moves_add[n_moves], chess_board, check_pieces[0],
				     pinned, t_en_passant );
		*n_possible_moves = n_moves;
		return;
	}

	// Add moves by each piece group
	n_moves += pawn_moves  ( &moves_add[n_moves], your_pieces->Pawns,   their_pieces->All, not_all_pieces, ~pinned,
				  t_en_passant, i_turn );
	//cout << "  Pawn   Moves = " << n_moves << endl;
	n_moves += knight_moves( &moves_add[n_moves], your_pieces->Knights, their_pieces->All, not_all_pieces, ~pinned );
	//cout << " +Knight Moves = " << n_moves << endl;
	n_moves += bishop_moves( &moves_add[n_moves], your_pieces->Bishops, their_pieces->All, not_all_pieces, ~pinned );
	//cout << " +Bishop Moves = " << n_moves << endl;
	n_moves += rook_moves  ( &moves_add[n_moves], your_pieces->Rooks,   their_pieces->All, not_all_pieces, ~pinned,
				 i_turn );
	//cout << " +Rook   Moves = " << n_moves << endl;
	n_moves += queen_moves ( &moves_add[n_moves], your_pieces->Queens,  their_pieces->All, not_all_pieces, ~pinned );
	//cout << " +Queen  Moves = " << n_moves << endl;

	n_moves += king_moves  ( &moves_add[n_moves], your_pieces->King, your_pieces->All, their_pieces, 
				 not_all_pieces, i_turn );
	//cout << " +King   Moves = " << n_moves << endl;

	// CAN Castle
	int bit_offset = 0;
	int index_king = 4;
	if( i_turn == -1 ) {
		bit_offset = 2;
		index_king = 60;
	}
	
	uint64_t castle_through;
	if( (chess_board.Parameters >> (1+bit_offset)) & 1 and
	    (not_all_pieces >> (index_king+1)) & 1 and
	    (not_all_pieces >> (index_king+2)) & 1 ) {  // Castle king
		castle_through = 0;
		BIT_SET( castle_through, index_king+1 );
		check_check( castle_through, your_pieces->All, their_pieces, 
			     not_all_pieces, i_turn, check_pieces, &n_checks );
		if( n_checks == 0 ) {
			castle_through = 0;
			BIT_SET( castle_through, index_king+2 );
			check_check( castle_through, your_pieces->All, their_pieces, 
				     not_all_pieces, i_turn, check_pieces, &n_checks );
			if( n_checks == 0 ) {
		cout << i_turn << " CAN Castle King\n";
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
		castle_through = 0;
		BIT_SET( castle_through, index_king-1 );
		check_check( castle_through, your_pieces->All, their_pieces, 
			     not_all_pieces, i_turn, check_pieces, &n_checks );
		if( n_checks == 0 ) {
			castle_through = 0;
			BIT_SET( castle_through, index_king-2 );
			check_check( castle_through, your_pieces->All, their_pieces, 
				     not_all_pieces, i_turn, check_pieces, &n_checks );
			if( n_checks == 0 ) {
		cout << i_turn << " CAN Castle Queen\n";
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

inline uint64_t find_pins( Moves *moves_add, uint16_t param_bits, Pieces *your_pieces, Pieces *their_pieces, uint64_t not_all_pieces,
		           Moves_temp existing_check, int n_checks, int t_en_passant, int i_turn ) {

	uint64_t pinned = 0;

	// Find all piece indices except king to remove
	int max_pieces = 17;
	int indices[max_pieces];
	uint64_t remove_bits = your_pieces->All;
	remove_bits ^= your_pieces->King;
	for( int i = 0; i < max_pieces; i++ ) {
		indices[i] = -1;
	}
	convert_binary( remove_bits, indices );
	remove_bits |= your_pieces->King;
/*
	for( int i = 0; i < max_pieces; i++ ) {
		cout << indices[i] << endl;
	}
	cout << endl;
*/

	int i = 0;
	int n_check_pins;
	Moves_temp *check_pieces = newTemp(5);
	uint64_t all_flip = not_all_pieces;
	//while( indices[i] != -1 or i == max_pieces - 1 ) {
	while( indices[i] != -1 ) {
		BIT_FLIP( remove_bits, indices[i] );
		BIT_FLIP( all_flip, indices[i] );
		check_check( your_pieces->King, remove_bits, their_pieces, all_flip, i_turn, check_pieces, &n_check_pins );
//cout << " Checking index " << indices[i] << " n_check_reveal = " << n_check_pins <<endl; print_binary(remove_bits);cout<<endl;

		// Pin = True
		if( n_check_pins > n_checks ) {
//cout << "FOUND PIN at " << indices[i] << endl;
			if( n_checks == 0 ) {
				uint64_t pinned_bit = 0;
				BIT_SET( pinned_bit, indices[i] );
				n_moves += add_pin_moves( &moves_add[n_moves], param_bits, pinned_bit, check_pieces[0].bitmove,
							  your_pieces, their_pieces, not_all_pieces, pinned, t_en_passant, i_turn );
			}
			BIT_SET( pinned, indices[i] );
		}

		BIT_FLIP( remove_bits, indices[i] );
		BIT_FLIP( all_flip, indices[i] );
		i++;
	}
	return pinned;
}

inline int add_pin_moves( Moves *moves_pin, uint16_t param_bits, uint64_t pinned_bit, uint64_t checker_bits, Pieces *your_pieces,
			  Pieces *their_pieces, uint64_t not_all_pieces, uint64_t pinned, uint64_t t_en_passant, int i_turn ) {

	Moves *move_sluts = newMoves( param_bits, max_moves );

	// Find Remaining moves for pinned piece
	int np_pin_sluts = 0;
	if(      (your_pieces->Pawns & pinned_bit)   != 0 ) {
		np_pin_sluts = pawn_moves  ( &move_sluts[np_pin_sluts], your_pieces->Pawns,   their_pieces->All,
					     not_all_pieces, ~pinned, t_en_passant, i_turn );
	}
	else if( (your_pieces->Knights & pinned_bit) != 0 ) {
		np_pin_sluts = knight_moves( &move_sluts[np_pin_sluts], your_pieces->Knights, their_pieces->All,
					     not_all_pieces, ~pinned );
	}
	else if( (your_pieces->Bishops & pinned_bit) != 0 ) {
		np_pin_sluts = bishop_moves( &move_sluts[np_pin_sluts], your_pieces->Bishops, their_pieces->All,
					     not_all_pieces, ~pinned );
	}
	else if( (your_pieces->Rooks & pinned_bit)   != 0 ) {
		np_pin_sluts = rook_moves  ( &move_sluts[np_pin_sluts], your_pieces->Rooks,   their_pieces->All,
					     not_all_pieces, ~pinned, i_turn );
	}
	else if( (your_pieces->Queens & pinned_bit) != 0 ) {
		np_pin_sluts = queen_moves ( &move_sluts[np_pin_sluts], your_pieces->Queens,  their_pieces->All,
					     not_all_pieces, ~pinned );
	}
/*
print_binary(checker_bits); cout << endl;
cout << " moves total pinned but do i even need to search " << np_pin_sluts << endl;
for( int i = 0; i < np_pin_sluts; i++ ) {
	print_binary(move_sluts[i].bitmove); cout << "  " << move_sluts[i].piece << endl;
}
*/

	for( int i = 0; i < np_pin_sluts; i++ ) {
		if( (move_sluts[i].bitmove & checker_bits) != 0 ) { // Capture pin
//cout << " I found you you sneaky bastard: "; print_binary(move_sluts[i].bitmove & checker_bits); cout << endl;

			moves_pin[n_moves] = move_sluts[i];
			n_moves++;

			// Move along pin
			int index_checker;
			convert_binary( checker_bits, &index_checker );
			int index_king;
			convert_binary( your_pieces->King, &index_king );
			int index_pinned;
			convert_binary( pinned_bit, &index_pinned  );
			int total_direction = index_checker - index_king;
			int piece_case = move_sluts[i].piece; 
//cout << " Piece_case :"<<piece_case << " " << total_direction << endl;
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
				if( index_king+(s+1)*dir != index_pinned ) {
					Moves along_pin = move_sluts[i];
					along_pin.bitmove = 0;
					BIT_SET( along_pin.bitmove, index_pinned );
					BIT_SET( along_pin.bitmove, index_king+(s+1)*dir );
					
//print_binary( along_pin.bitmove ); cout << endl;
					moves_pin[n_moves] = along_pin;
					n_moves++;
				}
			}

		}
	}
	free( move_sluts );

	return n_moves;
}
