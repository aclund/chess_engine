#include <time.h>
#include "functions.h"

void engine( Chess_Board *bitboards, Hash hash_history ) {

        clock_t start = clock();
	cout << " Calculating... \n";

	// Find depth 0 for current(root) position
	Move_Tree *root = new Move_Tree;
	all_moves( *bitboards, root->moves_arr );

	// Set maximizer and pieces to exclude in print
	bool l_turn;
	uint64_t print_pieces;
	if( bitboards->Parameters & 1 ) { 
		l_turn = false;
		print_pieces = bitboards->Black.All;
	}
	else {
		l_turn = true;
		print_pieces = bitboards->White.All;
	}

	// Minimax algorithm with alpha-beta pruning
	Search minimaxed = minimax( *bitboards, root, hash_history, max_depth, -99999, 99999, l_turn );

	cout << " Time used: " << (clock()-start)/(double) CLOCKS_PER_SEC << "\n\n";

	// Write and preform best move
	print_moves( &root->moves_arr[minimaxed.best_move], 1, print_pieces );
	*bitboards = preform_move( *bitboards, root->moves_arr[minimaxed.best_move] );

#ifdef DEBUG
	cout << "\n ** Eval Score ** = " << minimaxed.eval << "\n\n";

	// Write best moves order
	cout << " Continuation:\n";
	Move_Tree  *tmp       = root;
	Chess_Board tmp_board = *bitboards;
	int depth  = 2;
	bool white = !l_turn;
	while( tmp->best->children != nullptr && tmp->best->children->best != nullptr ) {
		tmp = tmp->best->children;

		if( white ) { print_pieces = tmp_board.White.All; }
		else 	    { print_pieces = tmp_board.Black.All; }
		print_moves( tmp->best, 1, print_pieces );
		tmp_board = preform_move( tmp_board, *tmp->best );

		depth++;
		white = !white;
	}
#endif

	// Delete game tree
	freeTree( root );

	return;
}
