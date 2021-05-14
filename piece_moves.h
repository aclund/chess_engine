inline int rel_rank( int i, int i_turn ) {
	return int((1-i_turn)*4.5) + (int(i/8)+1)*i_turn;
}
inline int rel_col ( int i ) {
	return i - int(i/8)*8;
}
inline void add_promotes( Moves *moves_promote ) {
	// Reset curruent piece
	int n = 0;
	moves_promote[n].piece = -1*queen;
	n++;
	// Copy to other promote pieces
	moves_promote[n].bitmove = moves_promote[n-1].bitmove;
	moves_promote[n].piece   = -1*rook;
	n++;
	moves_promote[n].bitmove = moves_promote[n-1].bitmove;
	moves_promote[n].piece   = -1*bishop;
	n++;
	moves_promote[n].bitmove = moves_promote[n-1].bitmove;
	moves_promote[n].piece   = -1*knight;
	n++;
	if( moves_promote[n-4].capture ) {
		moves_promote[n-1].capture = true;
		moves_promote[n-2].capture = true;
		moves_promote[n-3].capture = true;
	}
}

inline int pawn_moves  ( Moves *moves_add, uint64_t pawns,   uint64_t their_pieces, uint64_t not_all_pieces, uint64_t not_pinned,
                         int t_en_passant, int i_turn ) {
	int n_moves = 0;

	int indices[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
	convert_binary( pawns, indices );

	int off7 = 0 + 7*(1-i_turn)/2, off9 = 7 + 7*(i_turn-1)/2;

	int i = 0, index_update, pawn_rank, pawn_col;
	while( indices[i] != -1 ) {
		if( (not_pinned >> indices[i]) & 1 ) {
			pawn_rank = rel_rank( indices[i], i_turn );
			pawn_col  = rel_col ( indices[i] );
//cout << " pawn rank, col " << indices[i] << ":"<< pawn_rank << "  " << pawn_col <<"\n";

			index_update = indices[i] +  8*i_turn;	  // Square in front
			if( (not_all_pieces >> index_update) & 1 ) {

				BIT_SET(moves_add[n_moves].bitmove, indices[i]);
				BIT_SET(moves_add[n_moves].bitmove, index_update);
				moves_add[n_moves].piece = pawn;
				n_moves++;
				if( pawn_rank == 7 ) { // Promote
					add_promotes( &moves_add[n_moves-1] );
					n_moves += 3;
				}
			}

			if( pawn_col != off7 ) {
				index_update = indices[i] +  7*i_turn; // Capturable left
				if( (their_pieces >> index_update) & 1 ) {
//cout << " Pawn takes left " << endl;
					BIT_SET(moves_add[n_moves].bitmove, indices[i]);
					BIT_SET(moves_add[n_moves].bitmove, index_update);
					moves_add[n_moves].piece   = pawn;
					moves_add[n_moves].capture = true;
					n_moves++;
					if( pawn_rank == 7 ) { // Promote
						add_promotes( &moves_add[n_moves-1] );
						n_moves += 3;
					}
				}
			   	else if( t_en_passant != 0 and t_en_passant == index_update ) {
					BIT_SET(moves_add[n_moves].bitmove, indices[i]);
					BIT_SET(moves_add[n_moves].bitmove, index_update);
					moves_add[n_moves].piece   = en_passant;
					moves_add[n_moves].capture = true;
//cout << en_passant << "SET take en passant " << t_en_passant << endl;
					n_moves++;
					if( pawn_rank == 7 ) { // Promote
						add_promotes( &moves_add[n_moves-1] );
						n_moves += 3;
					}
				}
			}

			if( pawn_col != off9 ) {
				index_update = indices[i] +  9*i_turn; // Capturable right
				if( (their_pieces >> index_update) & 1 ) {
					BIT_SET(moves_add[n_moves].bitmove, indices[i]);
					BIT_SET(moves_add[n_moves].bitmove, index_update);
					moves_add[n_moves].piece   = pawn;
					moves_add[n_moves].capture = true;
					n_moves++;
					if( pawn_rank == 7 ) { // Promote
						add_promotes( &moves_add[n_moves-1] );
						n_moves += 3;
					}
				}
			   	else if( t_en_passant != 0 and t_en_passant == index_update ) {
					BIT_SET(moves_add[n_moves].bitmove, indices[i]);
					BIT_SET(moves_add[n_moves].bitmove, index_update);
					moves_add[n_moves].piece   = en_passant;
					moves_add[n_moves].capture = true;
//cout << en_passant << "SET take en passant " << t_en_passant << endl;
//cout << i_turn << " turn " << index_update <<endl;
					n_moves++;
					if( pawn_rank == 7 ) { // Promote
						add_promotes( &moves_add[n_moves-1] );
						n_moves += 3;
					}
				}
			}
//if( indices[i] == 51 ) { cout << " Pawn found 51... " << pawn_rank << " " << pawn_col << endl; }
//if( index_update == 58 or index_update == 60 ) { cout << index_update << "  rank:"<<pawn_rank << endl; }

			if(      pawn_rank == 2 ) {
				index_update = indices[i] + 16*i_turn; // Up two beginning 
				if( ((not_all_pieces >> index_update         ) & 1) &&
				    ((not_all_pieces >> (indices[i]+8*i_turn)) & 1) ) {

					BIT_SET(moves_add[n_moves].bitmove, indices[i]);
					BIT_SET(moves_add[n_moves].bitmove, index_update);
					moves_add[n_moves].piece = pawn;
					// Set en_passant
					int bit2 = 32, temp_passant = indices[i]+8*i_turn, i = 5;
					while( temp_passant != 0 and bit2 != 0 ) {
						if( int(temp_passant/bit2) ) {
							BIT_SET(moves_add[n_moves].parameters,i);
							temp_passant -= bit2;
						}
						i++;
						bit2 /= 2;
					}
					n_moves++;
				}
			}

		}
		i++;
	}

	return n_moves;
}

inline int knight_moves( Moves *moves_add, uint64_t knights, uint64_t their_pieces, uint64_t not_all_pieces, uint64_t not_pinned ) {
	int n_moves = 0;

	int indices[4] = {-1,-1,-1,-1};
	convert_binary( knights, indices );

	int i = 0;
	while( indices[i] != -1 ) {
		if( (not_pinned >> indices[i]) & 1 ) {
			for( int n = 0; n < n_knight_moves[indices[i]]; n++ ) {
				if( knight_squares[indices[i]][n] & not_all_pieces ) {
					moves_add[n_moves].bitmove = knight_squares[indices[i]][n] & not_all_pieces;
					BIT_SET(moves_add[n_moves].bitmove, indices[i]);
					moves_add[n_moves].piece   = knight;
					n_moves++;
				}
				else if( (knight_squares[indices[i]][n] & their_pieces) != 0 ) { // Capture
					moves_add[n_moves].bitmove = knight_squares[indices[i]][n] & their_pieces;
					BIT_SET(moves_add[n_moves].bitmove, indices[i]);
					moves_add[n_moves].piece   = knight;
					moves_add[n_moves].capture = true;
					n_moves++;
				}
			}
		}
		i++;
	}
	return n_moves;
}

inline int bishop_moves( Moves *moves_add, uint64_t bishops, uint64_t their_pieces, uint64_t not_all_pieces, uint64_t not_pinned ) {
	int n_moves = 0;

	int indices[4] = {-1,-1,-1,-1};
	convert_binary( bishops, indices );

	int i = 0, n_count = 0, index_update;
	while( indices[i] != -1 ) {
		if( (not_pinned >> indices[i]) & 1 ) {
			for( int n_direction = 4; n_direction < 8; n_direction++ ) {
				n_count = 0;
				index_update = indices[i];
				while( n_count < count_to_edge[indices[i]][n_direction] ) {
					index_update += index_directions[n_direction];
					if( (not_all_pieces >> index_update) & 1 ) { 	     // Empty
						moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,index_update);
						moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,indices[i]);
						moves_add[n_moves].piece   = bishop;
						n_moves++;
                                        	n_count++;
                                	}
                                	else if( (their_pieces >> index_update) & 1 ) {      // Capture
						moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,index_update);
						moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,indices[i]);
						moves_add[n_moves].piece   = bishop;
						moves_add[n_moves].capture = true;
						n_moves++;
                                    		n_count = 7;
                                	}
                                	else { n_count = 7; }                                // Occupado
				}
			}
		}
		i++;
	}
	return n_moves;
}

inline int rook_moves  ( Moves *moves_add, uint64_t rooks,   uint64_t their_pieces, uint64_t not_all_pieces, uint64_t not_pinned, int i_turn ) {
	int n_moves = 0;

	int indices[4] = {-1,-1,-1,-1};
	convert_binary( rooks, indices );

	int k_rook = 7 + 28*(1-i_turn);
	int q_rook = 0 + 28*(1-i_turn);
	bool rm_k_castle, rm_q_castle;
	int bit_offset = 0;
	if( i_turn == -1 ) { bit_offset = 2; }

	int i = 0, n_count = 0, index_update;
	while( indices[i] != -1 ) {
		if( (not_pinned >> indices[i]) & 1 ) {
			rm_k_castle = false, rm_q_castle = false;
			if(      indices[i] == k_rook ) { rm_k_castle = true; }
			else if( indices[i] == q_rook ) { rm_q_castle = true; }
//cout << indices[i] << " rm castling k, q " << rm_k_castle << "  " << rm_q_castle << endl;
			for( int n_direction = 0; n_direction < 4; n_direction++ ) {
				n_count = 0;
				index_update = indices[i];
				while( n_count < count_to_edge[indices[i]][n_direction] ) {
					index_update += index_directions[n_direction];
					if( (not_all_pieces >> index_update) & 1 ) { 	     // Empty
						moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,index_update);
						moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,indices[i]);
						moves_add[n_moves].piece   = rook;
						if(      rm_k_castle ) { BIT_CLEAR( moves_add[n_moves].parameters, 1+bit_offset ); }
						else if( rm_q_castle ) { BIT_CLEAR( moves_add[n_moves].parameters, 2+bit_offset ); }
						n_moves++;
                                        	n_count++;
                                	}
                                	else if( (their_pieces >> index_update) & 1 ) {      // Capture
						moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,index_update);
						moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,indices[i]);
						moves_add[n_moves].piece   = rook;
						if(      rm_k_castle ) { BIT_CLEAR( moves_add[n_moves].parameters, 1+bit_offset ); }
						else if( rm_q_castle ) { BIT_CLEAR( moves_add[n_moves].parameters, 2+bit_offset ); }
						moves_add[n_moves].capture = true;
						n_moves++;
                                        	n_count = 7;
                                	}
                                	else { n_count = 7; }                                // Occupado
				}
			}
		}
		i++;
	}
	return n_moves;
}

inline int queen_moves ( Moves *moves_add, uint64_t queens,  uint64_t their_pieces, uint64_t not_all_pieces, uint64_t not_pinned ) {
	int n_moves = 0;

	int indices[4] = {-1,-1,-1,-1};
	convert_binary( queens, indices );

	int i = 0, n_count = 0, index_update;
	while( indices[i] != -1 ) {
		if( (not_pinned >> indices[i]) & 1 ) {
			for( int n_direction = 0; n_direction < 8; n_direction++ ) {
				n_count = 0;
				index_update = indices[i];
				while( n_count < count_to_edge[indices[i]][n_direction] ) {
					index_update += index_directions[n_direction];
					if( (not_all_pieces >> index_update) & 1 ) { 	     // Empty
						moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,index_update);
						moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,indices[i]);
						moves_add[n_moves].piece   = queen;
						n_moves++;
                                        	n_count++;
                                	}
                                	else if( (their_pieces >> index_update) & 1 ) {      // Capture
						moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,index_update);
						moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,indices[i]);
						moves_add[n_moves].piece   = queen;
						moves_add[n_moves].capture = true;
						n_moves++;
                                        	n_count = 7;
                                	}
                                	else { n_count = 7; }                                // Occupado
				}
			}
		}
		i++;
	}
	return n_moves;
}

inline int piecey_pie_moves( Moves *moves_add, Pieces *your_pieces, uint64_t their_pieces, uint64_t not_all_pieces, uint64_t not_pinned,
			     int t_en_passant, int i_turn ) {

	int n_moves = 0;

        n_moves += pawn_moves  ( &moves_add[n_moves], your_pieces->Pawns,   their_pieces,
				 not_all_pieces, not_pinned, t_en_passant, i_turn );
        n_moves += knight_moves( &moves_add[n_moves], your_pieces->Knights, their_pieces,
				 not_all_pieces, not_pinned );
        n_moves += bishop_moves( &moves_add[n_moves], your_pieces->Bishops, their_pieces,
				 not_all_pieces, not_pinned );
        n_moves += rook_moves  ( &moves_add[n_moves], your_pieces->Rooks,   their_pieces,
				 not_all_pieces, not_pinned, i_turn );
        n_moves += queen_moves ( &moves_add[n_moves], your_pieces->Queens,  their_pieces,
	     			 not_all_pieces, not_pinned );

	return n_moves;
}
