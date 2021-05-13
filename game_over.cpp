#include <iostream>

using namespace std;

#include "functions.h"
#include "global.h"
#include "initialize.h"
#include "convert_binary.h"
#include "piece_moves.h"
#include "check_check.h"

bool game_over( Chess_Board chess_board ) {

	int n_possible_moves = 0;
	Moves *moves_null = newMoves( chess_board.Parameters, max_moves );
	all_moves( chess_board, moves_null, &n_possible_moves );
	free( moves_null );

	if( n_possible_moves == 0 ) {
		return true;
	}

	return false;
}
