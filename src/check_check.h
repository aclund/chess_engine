inline void check_check( uint64_t your_king, uint64_t your_pieces, Pieces *their_pieces, uint64_t not_all_pieces,
			 int i_turn, int *n_checks ) {

	int n_count = 0;

	// Move all their pieces to see if capture king
	uint32_t null_params = 0;
	Moves *moves_check = newMoves( null_params, max_moves);

	int n_moves_null = 0, null_passant = -1;
	n_moves_null = piecey_pie_moves( moves_check, their_pieces, your_pieces, not_all_pieces,
					 null_passant, -1*i_turn );

	for( int n = 0; n < n_moves_null; n++ ) {
		if( (your_king & moves_check[n].bitmove) != 0 ) {
			n_count++;
		}
	}
	delete[] moves_check;

	*n_checks = n_count;

	return;
}
