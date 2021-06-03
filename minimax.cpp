#include <iostream>
using namespace std;

#include "functions.h"
#include "global.h"
#include "convert_binary.h"
#include "preform_move.h"

inline int score(Chess_Board);

int minimax( Chess_Board chess_board, Move_Tree *head, int depth, int alpha, int beta, bool maxer, int *spot ) {

	int eval, max_eval, min_eval, point_me_there_daddy, null;

	if( depth == max_depth ) cout << " Current Score = " << score( chess_board ) << "\n\n";

	if( depth == 0 ) { return score( chess_board ); }
	else if( head->n_moves == 0 ) {
		if( chess_board.Parameters & 1 ) { return 9999; } else { return -9999; }
	}

	Chess_Board chess_moved;

	if( maxer ) {
		max_eval = -99999999;
		for( int n = 0; n < head->n_moves; n++ ) {
			chess_moved = preform_move( chess_board, head->moves_arr[n] );
			eval = minimax( chess_moved, head->moves_arr[n].children, depth-1,
					alpha, beta, false, &null );
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
					alpha, beta, true, &null );
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
inline void indexer( uint64_t pieces, int *indices ) {
	for( int i = 0; i < 9; i++ ) {
		indices[i] = -1;
	}
	convert_binary( pieces, indices );
	return;
}

inline int score( Chess_Board chess_board ) {

	int board_eval = 0, indices[9], i, table;

/*
	int i_turn;
	if( chess_board.Parameters & 1 ) { i_turn = 1; }
	else { i_turn = -1; }

	if( game_over( chess_board ) ) { return i_turn*9999; }
*/

	// Black Pieces Table Score
	for( uint64_t* piece = (uint64_t*)&chess_board.Black.Pawns, table = 0;
	    piece < (uint64_t*)((uint8_t*)&chess_board.Black.Pawns + 6*sizeof(uint64_t)); piece++, table++ ) {
		indexer( *piece, indices );
		i = 0;
		while( indices[i] != -1 ) {
			board_eval -= pst_table[table] [indices[i]];
			i++;
		}
	}
	// White Pieces Table Score
	for( uint64_t* piece = (uint64_t*)&chess_board.White.Pawns, table = 0;
	    piece < (uint64_t*)((uint8_t*)&chess_board.White.Pawns + 6*sizeof(uint64_t)); piece++, table++ ) {
		indexer( *piece, indices );
		i = 0;
		while( indices[i] != -1 ) {
			board_eval += pst_table[table] [63 - indices[i]];
			i++;
		}
	}

	return board_eval;
}
