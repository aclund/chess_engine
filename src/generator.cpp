#include "functions.h"

void generator( Chess_Board chess_board, Move_Tree *head, Hash history, int depth ) {

	if( depth == 0 or game_over( chess_board, history ) ) { return; }

	Chess_Board chess_moved;

	for( int n = 0; n < head->moves_arr.size(); n++ ) {
		chess_moved = preform_move( chess_board, head->moves_arr[n] );
		Hash track = history;
		track.append( chess_moved );

		//int ierr = check_bits( chess_moved ); if( ierr != 0 ) { break; }

		Move_Tree *curr = new Move_Tree;
		if( depth != 1 ) {
			all_moves( chess_moved, curr->moves_arr );
			head->moves_arr[n].children = curr;
		}

		generator( chess_moved, curr, track, depth-1);
	}

	return;
}
