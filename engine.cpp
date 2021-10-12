#include <iostream>
#include <time.h>

using namespace std;

#include "functions.h"
#include "global.h"
#include "initialize.h"
#include "convert_binary.h"
#include "preform_move.h"

void engine( ) {

        clock_t start = clock();

	cout << " Calculating... \n";

	Move_Tree *root = new Move_Tree;
	*root = (Move_Tree){ 0 };

	//Find Depth 0
	root->moves_arr = newMoves( bitboards.Parameters, max_moves );
	int n_possible_moves = 0;
	all_moves( bitboards, root->moves_arr, &n_possible_moves );
	root->n_moves = n_possible_moves;

	bool l_turn;
	uint64_t n_print_pieces;
	if( bitboards.Parameters & 1 ) { 
		l_turn = false;
		n_print_pieces = bitboards.Black.All;
	}
	else {
		l_turn = true;
		n_print_pieces = bitboards.White.All;
	}
	int mmm_tasty_spot;
	int minimaxed = minimax(  bitboards, root, max_depth,
				  numeric_limits<int>::min(),
				  numeric_limits<int>::max(),
				  l_turn, &mmm_tasty_spot );
	cout << " ** Eval Score ** = " << minimaxed << "\n\n";
	cout << " Time used:  " << ( clock() - start ) / (double) CLOCKS_PER_SEC << "\n\n";


	print_moves( &root->moves_arr[mmm_tasty_spot], 1, n_print_pieces );
	bitboards = preform_move( bitboards, root->moves_arr[mmm_tasty_spot] );

	freeTree( root );

	return;
}
