#include "functions.h"

void random_player( Chess_Board *bitboards ) {

        // Find possible moves
	vector<Moves> moves_arr;
        all_moves( *bitboards, moves_arr );
	if( moves_arr.size() == 0 ) { return; }

	int rand = (int)rand_64::get();
	int rando_board = rand % moves_arr.size();

	uint64_t print_pieces;
	if( bitboards->Parameters & 1 ) { print_pieces = bitboards->Black.All; }
	else 				{ print_pieces = bitboards->White.All; }
	print_moves( &moves_arr[rando_board], 1, print_pieces );
	*bitboards = preform_move( *bitboards, moves_arr[rando_board] );

	return;
}
