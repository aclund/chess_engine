#include <time.h>
#include "functions.h"

void engine( Chess_Board *bitboards, Hash hash_history ) {

	clock_t start = clock();
	if( l_root ) { cout << " Calculating... \n"; }

	// Set maximizer and pieces to exclude in print
	bool maxer;
	uint64_t print_pieces;
	if( bitboards->Parameters & 1 ) { 
		maxer = false;
		print_pieces = bitboards->Black.All;
	}
	else {
		maxer = true;
		print_pieces = bitboards->White.All;
	}

	// Find depth 0 for current(root) position
	Move_Tree *root_node = new Move_Tree;
	all_moves( *bitboards, root_node->moves_arr );

	// Split root moves across processors
	Move_Tree *split = new Move_Tree;
	for( int n=0; n<root_node->moves_arr.size(); n++ ) {
		int rel_id = n % num_procs;
		if( myid == rel_id ) { split->moves_arr.push_back( root_node->moves_arr[n] ); }
	}

	// Minimax algorithm with alpha-beta pruning
#ifdef DEBUG
	Search minimaxed = minimax_tree( *bitboards, split,            hash_history, max_depth, -99999, 99999, maxer );
#else
	Search minimaxed = minimax     ( *bitboards, split->moves_arr, hash_history, max_depth, -99999, 99999, maxer );
#endif

	// Determine global best
	int best_proc, root_best_move;
#ifdef MPI_ON
	int size_Search = 2;
	Search all_minimaxed[num_procs];
	MPI_Gather( &minimaxed, size_Search, MPI_INT, all_minimaxed, size_Search, MPI_INT, i_root, MPI_COMM_WORLD );

	if( l_root ) {
		// Determine best_proc from all_minimaxed[].eval
		best_proc = 0;
		int best_eval = all_minimaxed[best_proc].eval;
		for( int i=1; i<num_procs; i++ ) {
			if(       maxer && all_minimaxed[i].eval > best_eval ) {
				best_proc = i;
				best_eval = all_minimaxed[i].eval;
			}
			else if( !maxer && all_minimaxed[i].eval < best_eval ) {
				best_proc = i;
				best_eval = all_minimaxed[i].eval;
			}
		}

		// Use best proc to get root_best_move
		int best_move = all_minimaxed[best_proc].best_move;
		int count = 0;
		for( int n=0; n<root_node->moves_arr.size(); n++ ) {
			int rel_id = n % num_procs;
			if( best_proc == rel_id ) {
				if( count == best_move ) {
					root_best_move = n;
				}
				count++;
			}
		}
	}
	MPI_Bcast( &root_best_move, 1, MPI_INT, i_root, MPI_COMM_WORLD );
	MPI_Bcast( &best_proc     , 1, MPI_INT, i_root, MPI_COMM_WORLD );
#else
	best_proc = myid;
	root_best_move = minimaxed.best_move;
#endif

	if( myid == best_proc ) {
		cout << " Time used: " << (clock()-start)/(double) CLOCKS_PER_SEC << "\n\n";
		print_moves( &root_node->moves_arr[root_best_move], 1, print_pieces );
	}

	// Preform move
	*bitboards = preform_move( *bitboards, root_node->moves_arr[root_best_move] );

#ifdef DEBUG
	if( myid == best_proc ) {
		cout << "\n ** Eval Score ** = " << minimaxed.eval << "\n\n";

		// Write best moves order
		cout << " Continuation:\n";
		Move_Tree  *tmp       = split;
		Chess_Board tmp_board = *bitboards;
		int depth  = 2;
		bool white = !maxer;
		while( tmp->best->children != nullptr && tmp->best->children->best != nullptr ) {
			tmp = tmp->best->children;

			if( white ) { print_pieces = tmp_board.White.All; }
			else        { print_pieces = tmp_board.Black.All; }
			print_moves( tmp->best, 1, print_pieces );
			tmp_board = preform_move( tmp_board, *tmp->best );

			depth++;
			white = !white;
		}
	}
#endif

	// Delete game tree
	freeTree( root_node );
	freeTree( split );

	return;
}
