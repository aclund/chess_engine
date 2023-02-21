#include "functions.h"

inline int score(Chess_Board);

Search minimax_tree( Chess_Board chess_board, Move_Tree *head, Hash history, int depth, int alpha, int beta, bool maxer ) {

	int max_eval, min_eval;
	Search found;

	// Check hash history for 3-fold repetition
	if( history.rep3fold() ) {
		found.eval = 0;
		return found;
	}

	// Max depth evaluation
	if( depth == 0 ) {
		found.eval = score( chess_board );
		return found;
	}

	// Game over
	if( head->moves_arr.size() == 0 ) {
		if( in_check(chess_board) ) {
			if( maxer ) { found.eval = -9990 - depth; }
			else 	    { found.eval =  9990 + depth; }
		}
		else { found.eval = 0; }
		return found;
	}

	Chess_Board chess_moved;

	if( maxer ) {
		max_eval = -99999999;
		for( int n = 0; n < head->moves_arr.size(); n++ ) {
			chess_moved = preform_move( chess_board, head->moves_arr[n] );

			// Hash update
			Hash track = history;
			track.append( chess_moved );

			// Find moves at next depth
			Move_Tree *curr = new Move_Tree;
			if( depth != 1 ) {
				all_moves( chess_moved, curr->moves_arr );
				head->moves_arr[n].children = curr;
			}

			Search search = minimax_tree( chess_moved, head->moves_arr[n].children, track, depth-1,
						 alpha, beta, false );
			if( search.eval > max_eval ) { found.best_move = n; head->best = &head->moves_arr[n]; }
			max_eval = max(	max_eval, search.eval );
			alpha    = max( alpha,    search.eval );
			if( beta <= alpha ) break;
		}
		found.eval = max_eval;
		return found;
	}
	else {
		min_eval =  99999999;
		for( int n = 0; n < head->moves_arr.size(); n++ ) {
			chess_moved = preform_move( chess_board, head->moves_arr[n] );

			// Hash history
			Hash track = history;
			track.append( chess_moved );

			// Find moves at next depth
			Move_Tree *curr = new Move_Tree;
			if( depth != 1 ) {
				all_moves( chess_moved, curr->moves_arr );
				head->moves_arr[n].children = curr;
			}

			Search search = minimax_tree( chess_moved, head->moves_arr[n].children, track, depth-1,
						 alpha, beta, true );
			if( search.eval < min_eval ) { found.best_move = n; head->best = &head->moves_arr[n]; }
			min_eval = min(	min_eval, search.eval );
			beta     = min( beta,     search.eval );
			if( beta <= alpha ) break;
		}
		found.eval = min_eval;
		return found;
	}

}

inline void indexer( uint64_t pieces, int *indices ) {
	for( int i = 0; i < 9; i++ ) {
		indices[i] = -1;
	}
	convert_binary( pieces, indices );
	return;
}

inline int score( Chess_Board chess_board ) {

	int mg_eval = 0, eg_eval = 0, game_phase = 0;
	int indices[9], i;

	// White Pieces Table Score
	for( uint64_t* piece = (uint64_t*)&chess_board.White.Pawns, table = 0;
	    piece < (uint64_t*)((uint8_t*)&chess_board.White.Pawns + 6*sizeof(uint64_t)); piece++, table++ ) {

		indexer( *piece, indices );
		i = 0;
		while( indices[i] != -1 ) {
			mg_eval += mg_pst_table[table] [indices[i]^56];
			eg_eval += eg_pst_table[table] [indices[i]^56];
			game_phase += piece2phase[table];
			i++;
		}
	}
	// Black Pieces Table Score
	for( uint64_t* piece = (uint64_t*)&chess_board.Black.Pawns, table = 0;
	    piece < (uint64_t*)((uint8_t*)&chess_board.Black.Pawns + 6*sizeof(uint64_t)); piece++, table++ ) {

		indexer( *piece, indices );
		i = 0;
		while( indices[i] != -1 ) {
			mg_eval -= mg_pst_table[table] [indices[i]];
			eg_eval -= eg_pst_table[table] [indices[i]];
			game_phase += piece2phase[table];
			i++;
		}
	}

	game_phase = max( game_phase, 24 );

	return ( mg_eval*game_phase + eg_eval*(24-game_phase) ) / 24;
}
