#include <iostream>
using namespace std;

#include "functions.h"
#include "global.h"
#include "convert_binary.h"
#include "preform_move.h"

inline int score(Chess_Board);

int minimax( Chess_Board chess_board, Move_Tree *head, int depth, int alpha, int beta, bool maxer, int *spot ) {

	int eval, max_eval, min_eval, point_me_there_daddy = -1;

	if( depth == 0 or head->n_moves == 0 ) { return score( chess_board ); }

	Chess_Board chess_moved;

	if( maxer ) {
		max_eval = -99999999;
		for( int n = 0; n < head->n_moves; n++ ) {
			chess_moved = preform_move( chess_board, head->moves_arr[n] );
			eval = minimax( chess_moved, head->moves_arr[n].children, depth-1,
					alpha, beta, false, &point_me_there_daddy );
			if( eval > max_eval ) { point_me_there_daddy = n; }
			max_eval = max(	max_eval, eval );
			alpha    = max( alpha,    eval );
			if( beta <= alpha ) break;
		}
		*spot = point_me_there_daddy;
		return max_eval;
	}
	else {
		min_eval =  99999999;
		for( int n = 0; n < head->n_moves; n++ ) {
			chess_moved = preform_move( chess_board, head->moves_arr[n] );
			eval = minimax( chess_moved, head->moves_arr[n].children, depth-1,
					alpha, beta, true, &point_me_there_daddy );
			min_eval = min(	min_eval, eval );
			beta     = min( beta,     eval );
			if( beta <= alpha ) break;
		}
		return min_eval;
	}

	return 0;
}

inline int score( Chess_Board chess_board ) {

	int board_eval = 0;

	//if( game_over( chess_board ) ) { board_eval = 1; cout << " It is here asshole\n";}
	if( game_over( chess_board ) ) { board_eval = 1;}

	return board_eval;
}
