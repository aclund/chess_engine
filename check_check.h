
inline void check_check( uint64_t your_king, uint64_t your_pieces, Pieces *their_pieces, uint64_t not_all_pieces,
			 //int i_turn, Moves_temp *bad_boys, int *n_checks ) {
			 int i_turn, int *n_checks ) {

	uint16_t param_bits = 0;
	Moves *moves_check = newMoves( param_bits, max_moves);

        //cout << moves_check[0].piece << " is trying to merk you"<<endl;print_binary(moves_check[0].bitmove);cout<<endl;
	int n_count = 0;

	// Move all their pieces to see if capture king
	int n_moves_null = 0, null_passant = 0;
	uint64_t null_pinned = 0;

	n_moves_null = piecey_pie_moves( moves_check, their_pieces, your_pieces,
					 not_all_pieces, ~null_pinned, null_passant, -1*i_turn );
/*
        n_moves_null += pawn_moves  ( &moves_check[n_moves], their_pieces->Pawns,   your_pieces,
				     not_all_pieces, ~null_pinned, null_passant, -1*i_turn );
        n_moves_null += knight_moves( &moves_check[n_moves], their_pieces->Knights, your_pieces,
				     not_all_pieces, ~null_pinned );
        n_moves_null += bishop_moves( &moves_check[n_moves], their_pieces->Bishops, your_pieces,
				     not_all_pieces, ~null_pinned );
        n_moves_null += rook_moves  ( &moves_check[n_moves], their_pieces->Rooks,   your_pieces,
				     not_all_pieces, ~null_pinned, -1*i_turn );
        n_moves_null += queen_moves ( &moves_check[n_moves], their_pieces->Queens,  your_pieces,
				     not_all_pieces, ~null_pinned );
*/
//print_moves( moves_check, n_moves_null, their_pieces->All );

	for( int n = 0; n < n_moves_null; n++ ) {
		if( (your_king & moves_check[n].bitmove) != 0 ) {
	//cout << moves_check[n].piece << " is trying to merk you"<<endl;
			//bad_boys[n_count].bitmove  = moves_check[n].bitmove;
			//bad_boys[n_count].bitmove ^= your_king;
			//bad_boys[n_count].piece    = moves_check[n].piece;
			n_count++;
			if(  moves_check[n].piece < 0 ) { n+=3; }
		}
	}
	delete[] moves_check;

	*n_checks = n_count;

	return;
}
