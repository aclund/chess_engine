#include <iostream>

using namespace std;

#include "functions.h"
#include "global.h"
#include "initialize.h"
#include "convert_binary.h"
#include "preform_move.h"

void generator( Chess_Board chess_board, Move_Tree *head, int depth ) {

	if( depth == 0 or game_over(chess_board) ) { return; }
	//if( depth == 0 ) { return; }
//cout << " Depth : " << max_depth - depth + 1;
//cout <<" Turn = "; print_binary( head->moves_arr[0].parameters & 1 ); cout << endl;

	Move_Tree *curr;
	Chess_Board chess_moved;

	int n_possible_moves, ierr;
	for( int n = 0; n < head->n_moves; n++ ) {
		chess_moved = preform_move( chess_board, head->moves_arr[n] );

		ierr = check_bits( chess_moved );
		if( ierr != 0 ) { break; }
//cout <<"  ";
//print_binary(chess_moved.Parameters);cout<<endl;

		Moves *moves_add = newMoves( chess_moved.Parameters, max_moves );
		n_possible_moves = 0;
		all_moves( chess_moved, moves_add, &n_possible_moves );
//print_binary( moves_add[n].bitmove ); cout<<endl<<endl;

		curr = newTree( moves_add, n_possible_moves );

		head->moves_arr[n].children = curr;

		//int p = 0;
		for( int p = 0; p < n_possible_moves; p++ ) {
			generator( chess_moved, curr, depth-1);
		}
		free( moves_add );
	}

	return;
}
