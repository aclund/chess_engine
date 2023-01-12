#include "functions.h"

bool game_over( Chess_Board chess_board, Hash history ) {

	// 3 fold repetition
	if( history.rep3fold() ) { return true; }

	// 50 move rule
	uint32_t half_clock = chess_board.Parameters;
	half_clock %= 4096;
	BIT_CLEAR( half_clock, 0 );
	BIT_CLEAR( half_clock, 1 );
	BIT_CLEAR( half_clock, 2 );
	BIT_CLEAR( half_clock, 3 );
	BIT_CLEAR( half_clock, 4 );
	if( half_clock >= 3200 ) { return true; }

	// Stalemate
	vector<Moves> moves_null;
	all_moves( chess_board, moves_null );
	if( moves_null.size() == 0 ) { return true; }

	return false;
}
