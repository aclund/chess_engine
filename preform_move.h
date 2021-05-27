inline uint32_t clear_hbits( uint32_t param_bits ) {
	BIT_CLEAR( param_bits, 5  );
	BIT_CLEAR( param_bits, 6  );
	BIT_CLEAR( param_bits, 7  );
	BIT_CLEAR( param_bits, 8  );
	BIT_CLEAR( param_bits, 9  );
	BIT_CLEAR( param_bits, 10 );
	BIT_CLEAR( param_bits, 11 );
	return param_bits;
}

inline Chess_Board preform_move( Chess_Board chess_current, Moves preform ) {

	Chess_Board chess_next = chess_current;

	chess_next.Parameters = preform.parameters;

	Pieces *curr_pieces, *other_pieces;
	int i_turn;
	switch( chess_next.Parameters & 1 ) {
	  case 0: // White to Move
		other_pieces = &chess_next.White;
		curr_pieces  = &chess_next.Black;
		i_turn =  1;
	  break;
	  case 1: // Black to Move
		other_pieces = &chess_next.Black;
		curr_pieces  = &chess_next.White;
		i_turn = -1;
	  break;
	}
	
	// Perform Moves
	int promote_index;
	uint64_t temp;

	curr_pieces->All ^= preform.bitmove;
	chess_next.All_Pieces ^= preform.bitmove;

	if( (preform.bitmove & other_pieces->All) != 0 or (preform.piece == 12) ) {
		chess_next.Parameters = clear_hbits( chess_next.Parameters );
		if( preform.piece == 12 ) {
			temp  = preform.bitmove;
			temp &= ~curr_pieces->Pawns;
			int take_pawn;
			convert_binary( temp, &take_pawn );
			take_pawn += 8*i_turn;
			BIT_FLIP( other_pieces->Pawns, take_pawn );
			BIT_FLIP( other_pieces->All,   take_pawn );
		}
		else {
			if( (other_pieces->Rooks & preform.bitmove) != 0 ) {
				int ko_rook = 7 + 28*(1-i_turn);
				int qo_rook = 0 + 28*(1-i_turn);
				int bit_other_offset = 0;
				if( i_turn == -1 ) { bit_other_offset = 2; }
				if(      ((other_pieces->Rooks & preform.bitmove) >> ko_rook) & 1 ) {
					BIT_CLEAR( chess_next.Parameters, 1+bit_other_offset );
				}
				else if( ((other_pieces->Rooks & preform.bitmove) >> qo_rook) & 1 ) {
					BIT_CLEAR( chess_next.Parameters, 2+bit_other_offset );
				}
			}
			other_pieces->Pawns   &= ~preform.bitmove;
			other_pieces->Knights &= ~preform.bitmove;
			other_pieces->Bishops &= ~preform.bitmove;
			other_pieces->Rooks   &= ~preform.bitmove;
			other_pieces->Queens  &= ~preform.bitmove;
			other_pieces->All     &= ~preform.bitmove;
		}

		chess_next.All_Pieces  = 0;
		chess_next.All_Pieces |=  curr_pieces->All;
		chess_next.All_Pieces |= other_pieces->All;
	}
	
	//cout << " preform.piece " << preform.piece << endl;
	switch( preform.piece ) {
	  case 7: // CASTLE
		if(      (preform.bitmove >>  7) & 1 ) { // K
			BIT_FLIP( curr_pieces->King,   4 );
			BIT_FLIP( curr_pieces->Rooks,  7 );

			BIT_SET ( curr_pieces->King,   6 );
			BIT_SET ( curr_pieces->Rooks,  5 );
			BIT_SET ( curr_pieces->All,    6 );
			BIT_SET ( curr_pieces->All,    5 );
			BIT_SET ( chess_next.All_Pieces, 6 );
			BIT_SET ( chess_next.All_Pieces, 5 );
		}
		else if( (preform.bitmove >>  0) & 1 ) { // Q
			BIT_FLIP( curr_pieces->King,   4 );
			BIT_FLIP( curr_pieces->Rooks,  0 );

			BIT_SET ( curr_pieces->King,   2 );
			BIT_SET ( curr_pieces->Rooks,  3 );
			BIT_SET ( curr_pieces->All,    2 );
			BIT_SET ( curr_pieces->All,    3 );
			BIT_SET ( chess_next.All_Pieces, 2 );
			BIT_SET ( chess_next.All_Pieces, 3 );
		}
		else if( (preform.bitmove >> 63) & 1 ) { // k
			BIT_FLIP( curr_pieces->King,  60 );
			BIT_FLIP( curr_pieces->Rooks, 63 );

			BIT_SET ( curr_pieces->King,  62 );
			BIT_SET ( curr_pieces->Rooks, 61 );
			BIT_SET ( curr_pieces->All,   62 );
			BIT_SET ( curr_pieces->All,   61 );
			BIT_SET ( chess_next.All_Pieces, 62 );
			BIT_SET ( chess_next.All_Pieces, 61 );
		}
		else if( (preform.bitmove >> 56) & 1 ) { // q
			BIT_FLIP( curr_pieces->King,  60 );
			BIT_FLIP( curr_pieces->Rooks, 56 );

			BIT_SET ( curr_pieces->King,  58 );
			BIT_SET ( curr_pieces->Rooks, 59 );
			BIT_SET ( curr_pieces->All,   58 );
			BIT_SET ( curr_pieces->All,   59 );
			BIT_SET ( chess_next.All_Pieces, 58 );
			BIT_SET ( chess_next.All_Pieces, 59 );
		}
	  break;
	  case 1: // PAWN
	  case 12:// EN PASSANT
		curr_pieces->Pawns   ^=  preform.bitmove;
		chess_next.Parameters = clear_hbits( chess_next.Parameters );
	  break;
	  case 2: // KNIGHT
		curr_pieces->Knights ^=  preform.bitmove;
	  break;
	  case 3: // BISHOP
		curr_pieces->Bishops ^=  preform.bitmove;
	  break;
	  case 4: // ROOK
		curr_pieces->Rooks   ^=  preform.bitmove;
	  break;
	  case 5: // QUEEN
		curr_pieces->Queens  ^=  preform.bitmove;
	  break;
	  case 6: // KING
		curr_pieces->King    ^=  preform.bitmove;
	  break;
	  case 8:// PROMOTE
		temp = preform.bitmove;
		temp                 &= ~curr_pieces->Pawns;
		curr_pieces->Knights |=  temp; 
		curr_pieces->Pawns   &= ~preform.bitmove;
		chess_next.Parameters = clear_hbits( chess_next.Parameters );
	  break;
	  case 9:// PROMOTE
		temp = preform.bitmove;
		temp                 &= ~curr_pieces->Pawns;
		curr_pieces->Bishops |=  temp; 
		curr_pieces->Pawns   &= ~preform.bitmove;
		chess_next.Parameters = clear_hbits( chess_next.Parameters );
	  break;
	  case 10:// PROMOTE
		temp = preform.bitmove;
		temp                 &= ~curr_pieces->Pawns;
		curr_pieces->Rooks   |=  temp; 
		curr_pieces->Pawns   &= ~preform.bitmove;
		chess_next.Parameters = clear_hbits( chess_next.Parameters );
	  break;
	  case 11:// PROMOTE
		temp = preform.bitmove;
		temp                 &= ~curr_pieces->Pawns;
		curr_pieces->Queens  |=  temp; 
		curr_pieces->Pawns   &= ~preform.bitmove;
		chess_next.Parameters = clear_hbits( chess_next.Parameters );
	  break;

	  default:
		cout << "ERROR piece in preform " << preform.piece << "\n";
	  break;
	}

	return chess_next;
}
