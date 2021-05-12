#include <iostream>

using namespace std;

#include "functions.h"
#include "global.h"
#include "initialize.h"
#include "convert_binary.h"
#include "piece_moves.h"
#include "check_check.h"

bool game_over( Chess_Board chess_board ) {

	bool is_over = false;

	int n_possible_moves = 0;
	Moves *moves_null = newMoves( chess_board.Parameters, max_moves );
	all_moves( chess_board, moves_null, &n_possible_moves );
	free( moves_null );

	if( n_possible_moves == 0 ) {
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

		is_over = true;
		convert2board();
		write_board( board, params );

		int n_checks = 0;
		Moves_temp *check_pieces = newTemp(2);
		check_check( your_pieces->King, your_pieces->All, their_pieces, 
			     ~chess_board.All_Pieces, i_turn, check_pieces, &n_checks );

		if( n_checks == 0 ) {
			cout << " STALEMATE! \n";
		}
		else {
			cout << " CHECKMATE! \n";
		}
	}

	return is_over;
}
