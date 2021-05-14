inline Moves* newMoves( uint16_t param_bits, int n_moves ) {
	Moves* moves_create = new Moves[n_moves];
	for( int i = 0; i < n_moves; i++ ) {
		moves_create[i].bitmove =  0;
		moves_create[i].piece   = -1;

                moves_create[i].parameters  = param_bits;
                moves_create[i].parameters %= 32;
                BIT_FLIP(moves_create[i].parameters,0);
	}
	return moves_create;
}
inline Moves_temp* newTemp( int n_moves ) {
	Moves_temp* moves_create = new Moves_temp[n_moves];
	for( int i = 0; i < n_moves; i++ ) {
		moves_create[i].bitmove =  0;
		moves_create[i].piece   = -1;
	}
	return moves_create;
}

inline  Move_Tree* newTree( Moves *moves_add, int new_moves ) {
	Move_Tree* newtree = new Move_Tree;
	newtree->n_moves = new_moves;
	//newtree->moves_arr = new Moves[new_moves];
	newtree->moves_arr = moves_add;
	for( int n = 0; n < new_moves; n++ ) {
		newtree->moves_arr[n].children = nullptr;
	}

	return newtree;
}
inline void freeTree( Move_Tree *head ) {
	//for( int n = 0; n < head->n_moves; n++ ) {
	for( int n = 0; n < max_moves; n++ ) {
		if( head->moves_arr[n].children != nullptr ) {
			freeTree( head->moves_arr[n].children );
		}
	}
	free( head );
	return;
}
