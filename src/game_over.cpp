#include <iostream>

using namespace std;

#include "functions.h"
#include "global.h"
#include "initialize.h"
#include "convert_binary.h"
#include "piece_moves.h"
#include "check_check.h"

bool game_over( Chess_Board chess_board ) {

	uint32_t half_clock = chess_board.Parameters;
	half_clock %= 4096;
	BIT_CLEAR( half_clock, 0 );
	BIT_CLEAR( half_clock, 1 );
	BIT_CLEAR( half_clock, 2 );
	BIT_CLEAR( half_clock, 3 );
	BIT_CLEAR( half_clock, 4 );
	if( half_clock >= 3200 ) { return true; }

	int n_possible_moves = 0;
	Moves *moves_null = newMoves( chess_board.Parameters, max_moves );
	all_moves( chess_board, moves_null, &n_possible_moves );
	delete[] moves_null;

	if( n_possible_moves == 0 ) {
		return true;
	}

	return false;
}
