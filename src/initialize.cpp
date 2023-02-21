#include "functions.h"

void new_moves( Moves* set_move, int n_moves, uint32_t param_bits ) {
	for( int i = 0; i < n_moves; i++ ) {
		set_move[i].bitmove = 0;
		set_move[i].piece   = 0;
		set_move[i].children = nullptr;

		set_move[i].parameters  = param_bits;
		set_move[i].parameters %= 4096;       // Clear en passant
		BIT_FLIP(set_move[i].parameters,0);   // Turn flip
		set_move[i].parameters += 32;         // Half-Move Increment
	}
}

Moves* newMoves( uint32_t param_bits, int n_moves ) {
	Moves* moves_create = new Moves[n_moves];
	for( int i = 0; i < n_moves; i++ ) {
		moves_create[i].bitmove = 0;
		moves_create[i].piece   = 0;
		moves_create[i].children = nullptr;

                moves_create[i].parameters  = param_bits;
                moves_create[i].parameters %= 4096;       // Clear en passant
                BIT_FLIP(moves_create[i].parameters,0);   // Turn flip
                moves_create[i].parameters += 32;         // Half-Move Increment
	}
	return moves_create;
}

void freeTree( Move_Tree *head ) {
	//for( int n = 0; n < head->n_moves; n++ ) {
	for( int n = 0; n < head->moves_arr.size(); n++ ) {
		if( head->moves_arr[n].children != nullptr ) {
			freeTree( head->moves_arr[n].children );
		}
	}
	//delete[] head->moves_arr;
	delete   head;
	return;
}
