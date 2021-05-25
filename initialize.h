inline Moves* newMoves( uint32_t param_bits, int n_moves ) {
	Moves* moves_create = new Moves[n_moves];
	for( int i = 0; i < n_moves; i++ ) {
		moves_create[i].bitmove = 0;
		moves_create[i].piece   = 0;
		moves_create[i].children = NULL;

                moves_create[i].parameters  = param_bits;
                moves_create[i].parameters %= 4096;       // Clear en passant
                BIT_FLIP(moves_create[i].parameters,0);   // Turn flip
                moves_create[i].parameters += 32;         // Half-Move Increment
	}
	return moves_create;
}

inline Moves_temp* newTemp( int n_moves ) {
	Moves_temp* moves_create = new Moves_temp[n_moves];
	for( int i = 0; i < n_moves; i++ ) {
		moves_create[i].bitmove = 0;
		moves_create[i].piece   = 0;
	}
	return moves_create;
}

inline void freeTree( Move_Tree *head ) {
	//for( int n = 0; n < head->n_moves; n++ ) {
	for( int n = 0; n < max_moves; n++ ) {
		if( head->moves_arr[n].children != NULL ) {
			freeTree( head->moves_arr[n].children );
		}
	}
	delete[] head->moves_arr;
	delete   head;
	return;
}
