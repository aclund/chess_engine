#include <iostream>
using namespace std;

#include "functions.h"
#include "global.h"
#include "convert_binary.h"
#include "preform_move.h"

inline int score(Chess_Board);

int minimax( Chess_Board chess_board, Move_Tree *head, int depth, int alpha, int beta, bool maxer, int *spot ) {

	int eval, max_eval, min_eval, point_me_there_daddy, *null;

	if( depth == 0 or head->n_moves == 0 ) { return score( chess_board ); }

	Chess_Board chess_moved;

	if( maxer ) {
		max_eval = -99999999;
		for( int n = 0; n < head->n_moves; n++ ) {
			chess_moved = preform_move( chess_board, head->moves_arr[n] );
			eval = minimax( chess_moved, head->moves_arr[n].children, depth-1,
					alpha, beta, false, null );
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
					alpha, beta, true, null );
			if( eval < min_eval ) { point_me_there_daddy = n; }
			min_eval = min(	min_eval, eval );
			beta     = min( beta,     eval );
			if( beta <= alpha ) break;
		}
		*spot = point_me_there_daddy;
		return min_eval;
	}

	return 0;
}

inline int countSetBits( uint64_t in ) {
	int count = 0;
	while( in ) {
		in &= (in - 1);
		count++;
	}
	return count;
}

inline int score( Chess_Board chess_board ) {

	int board_eval = 0;

	int i_turn;
	switch( chess_board.Parameters & 1 ) {
	  case 0: // White to Move
		//your_pieces  = &chess_board.White;
		//their_pieces = &chess_board.Black;
		i_turn = -1;
	  break;
	  case 1: // Black to Move
		//your_pieces  = &chess_board.Black;
		//their_pieces = &chess_board.White;
		i_turn =  1;
	  break;
	}

	if( game_over( chess_board ) ) { return i_turn*9999; }

	board_eval = piece_score[ 0]*countSetBits( chess_board.Black.King    ) +
		     piece_score[ 1]*countSetBits( chess_board.Black.Queens  ) +
		     piece_score[ 2]*countSetBits( chess_board.Black.Rooks   ) +
		     piece_score[ 3]*countSetBits( chess_board.Black.Bishops ) +
		     piece_score[ 4]*countSetBits( chess_board.Black.Knights ) +
		     piece_score[ 5]*countSetBits( chess_board.Black.Pawns   ) +
		     piece_score[ 6]*countSetBits( chess_board.White.Pawns   ) +
		     piece_score[ 7]*countSetBits( chess_board.White.Knights ) +
		     piece_score[ 8]*countSetBits( chess_board.White.Bishops ) +
		     piece_score[ 9]*countSetBits( chess_board.White.Rooks   ) +
		     piece_score[10]*countSetBits( chess_board.White.Queens  ) +
		     piece_score[11]*countSetBits( chess_board.White.King    );

	//cout << board_eval << endl;

	return board_eval;
}
