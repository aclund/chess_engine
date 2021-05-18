#include <iostream>
using namespace std;

#include "functions.h"
#include "global.h"
#include "initialize.h"
#include "convert_binary.h"
#include "preform_move.h"

void generator( Chess_Board chess_board, Move_Tree *head, int depth ) {

	if( depth == 0 or game_over(chess_board) ) { return; }

	Chess_Board chess_moved;

	int n_possible_moves, ierr;
	for( int n = 0; n < head->n_moves; n++ ) {
		chess_moved = preform_move( chess_board, head->moves_arr[n] );

		//ierr = check_bits( chess_moved );
		//if( ierr != 0 ) { break; }

		Move_Tree *curr = new Move_Tree;
		*curr = (Move_Tree){ 0 };
		curr->moves_arr = newMoves( chess_moved.Parameters, max_moves );

		all_moves( chess_moved, curr->moves_arr, &n_possible_moves );

		curr->n_moves = n_possible_moves;
		head->moves_arr[n].children = curr;

		generator( chess_moved, curr, depth-1);
	}

	return;
}
