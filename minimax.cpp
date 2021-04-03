#include <iostream>

using namespace std;

#include "functions.h"
#include "global.h"

int minimax( int **possible_boards, int depth, int alpha, int beta, bool maxer ) {

	int eval, max_eval, min_eval;
	int i_start = 0, i_end = 0;

	bool game_over = false;
	if( depth == 0 or game_over ) return score(possible_boards[0]);

	if( maxer ) {
		max_eval = -99999999;
		for( int i = i_start; i < i_end; i++ ) {
			eval = minimax( possible_boards, depth - 1, alpha, beta, false );
			max_eval = max(	max_eval, eval );
			alpha    = max( alpha,    eval );
			if( beta <= alpha ) break;
		}
		return max_eval;
	}
	else {
		min_eval =  99999999;
		for( int i = i_start; i < i_end; i++ ) {
			eval = minimax( possible_boards, depth - 1, alpha, beta, true );
			min_eval = min(	min_eval, eval );
			beta     = min( beta,     eval );
			if( alpha <= beta ) break;
		}
		return min_eval;
	}

	return 0;
}
