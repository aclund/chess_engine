#include "global.h"
inline int rel_rank( int i, int i_turn ) {
	return int((1-i_turn)*4.5) + (int(i/8)+1)*i_turn;
}
inline int rel_col ( int i ) {
	return i - int(i/8)*8;
}
inline void add_promotes( Moves *moves_promote ) {
	// Reset curruent piece
	int n = 0;
	moves_promote[n].piece = queen + 6;
	n++;
	// Copy to other promote pieces
	moves_promote[n].bitmove = moves_promote[n-1].bitmove;
	moves_promote[n].piece   = rook + 6;
	n++;
	moves_promote[n].bitmove = moves_promote[n-1].bitmove;
	moves_promote[n].piece   = bishop + 6;
	n++;
	moves_promote[n].bitmove = moves_promote[n-1].bitmove;
	moves_promote[n].piece   = knight + 6;
	n++;
}

inline int pawn_moves  ( Moves *moves_add, uint64_t pawns,   uint64_t their_pieces, uint64_t not_all_pieces,
                         int t_en_passant, int i_turn ) {
	int n_moves = 0;

	int indices[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
	convert_binary( pawns, indices );

	int off7 = 0 + 7*(1-i_turn)/2, off9 = 7 + 7*(i_turn-1)/2;

	int i = 0, index_update, pawn_rank, pawn_col;
	while( indices[i] != -1 ) {
		pawn_rank = rel_rank( indices[i], i_turn );
		pawn_col  = rel_col ( indices[i] );
		//cout << " pawn rank, col " << indices[i] << ":"<< pawn_rank << "  " << pawn_col <<"\n";

		if( pawn_col != off7 ) {
			index_update = indices[i] +  7*i_turn; // Capturable left
			if( (their_pieces >> index_update) & 1 ) {
				BIT_SET(moves_add[n_moves].bitmove, indices[i]);
				BIT_SET(moves_add[n_moves].bitmove, index_update);
				moves_add[n_moves].piece   = pawn;
				n_moves++;
				if( pawn_rank == 7 ) { // Promote
					add_promotes( &moves_add[n_moves-1] );
					n_moves += 3;
				}
			}
		   	else if( t_en_passant == index_update ) {
				BIT_SET(moves_add[n_moves].bitmove, indices[i]);
				BIT_SET(moves_add[n_moves].bitmove, index_update);
				moves_add[n_moves].piece   = 12;
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
				n_moves++;
				if( pawn_rank == 7 ) { // Promote
					add_promotes( &moves_add[n_moves-1] );
					n_moves += 3;
				}
			}
		   	else if( t_en_passant == index_update ) {
				BIT_SET(moves_add[n_moves].bitmove, indices[i]);
				BIT_SET(moves_add[n_moves].bitmove, index_update);
				moves_add[n_moves].piece   = 12;
				n_moves++;
				if( pawn_rank == 7 ) { // Promote
					add_promotes( &moves_add[n_moves-1] );
					n_moves += 3;
				}
			}
		}

		if( pawn_rank == 2 ) {
			index_update = indices[i] + 16*i_turn; // Up two beginning 
			if( ((not_all_pieces >> index_update         ) & 1) &&
			    ((not_all_pieces >> (indices[i]+8*i_turn)) & 1) ) {

				BIT_SET(moves_add[n_moves].bitmove, indices[i]);
				BIT_SET(moves_add[n_moves].bitmove, index_update);
				moves_add[n_moves].piece = pawn;
				// Set en_passant
				int bit2 = 32, temp_passant = indices[i]+8*i_turn, ii = 17;
				while( temp_passant != 0 and bit2 != 0 ) {
					if( int(temp_passant/bit2) ) {
						BIT_SET(moves_add[n_moves].parameters,ii);
						temp_passant -= bit2;
					}
					ii--;
					bit2 /= 2;
				}
				n_moves++;
			}
		}

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

		i++;
	}

	return n_moves;
}

inline int knight_moves( Moves *moves_add, uint64_t knights, uint64_t not_your_pieces ) {
	int n_moves = 0;

	int indices[4] = {-1,-1,-1,-1};
	convert_binary( knights, indices );

	int i = 0;
	while( indices[i] != -1 ) {
		for( int n = 0; n < n_knight_moves[indices[i]]; n++ ) {
			if( (knight_squares[indices[i]][n] & not_your_pieces) != 0 ) {
				moves_add[n_moves].bitmove = knight_squares[indices[i]][n];
				BIT_SET(moves_add[n_moves].bitmove, indices[i]);
				moves_add[n_moves].piece   = knight;
				n_moves++;
			}
		}
		i++;
	}
	return n_moves;
}

inline int bishop_moves( Moves *moves_add, uint64_t bishops, uint64_t their_pieces, uint64_t not_all_pieces ) {
	int n_moves = 0;

	int indices[4] = {-1,-1,-1,-1};
	convert_binary( bishops, indices );

	int i = 0, n_count = 0, index_update;
	while( indices[i] != -1 ) {
		for( int n_direction = 4; n_direction < 8; n_direction++ ) {
			n_count = 0;
			index_update = indices[i];
			while( n_count < count_to_edge[indices[i]][n_direction] ) {
				index_update += index_directions[n_direction];
                                if( (their_pieces >> index_update) & 1 ) {	     // Capture
					moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,index_update);
					moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,indices[i]);
					moves_add[n_moves].piece   = bishop;
					n_moves++;
					n_count = 7;
                                }
				else if( (not_all_pieces >> index_update) & 1 ) {    // Empty
					moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,index_update);
					moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,indices[i]);
					moves_add[n_moves].piece   = bishop;
					n_moves++;
					n_count++;
                                }
                                else { n_count = 7; }                                // Occupado
			}
		}
		i++;
	}
	return n_moves;
}

inline int rook_moves  ( Moves *moves_add, uint64_t rooks,   uint64_t their_pieces, uint64_t not_all_pieces, int i_turn ) {
	int n_moves = 0;

	int indices[4] = {-1,-1,-1,-1};
	convert_binary( rooks, indices );

	int k_rook = 7 + 28*(1-i_turn);
	int q_rook = 0 + 28*(1-i_turn);
	bool rm_k_castle, rm_q_castle;
	int bit_offset = 0 + (1-i_turn);

	int i = 0, n_count = 0, index_update;
	while( indices[i] != -1 ) {
		rm_k_castle = false, rm_q_castle = false;
		if(      indices[i] == k_rook ) { rm_k_castle = true; }
		else if( indices[i] == q_rook ) { rm_q_castle = true; }
//cout << indices[i] << " rm castling k, q " << rm_k_castle << "  " << rm_q_castle << endl;
		for( int n_direction = 0; n_direction < 4; n_direction++ ) {
			n_count = 0;
			index_update = indices[i];
			while( n_count < count_to_edge[indices[i]][n_direction] ) {
				index_update += index_directions[n_direction];
                                if( (their_pieces >> index_update) & 1 ) {	     // Capture
					moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,index_update);
					moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,indices[i]);
					moves_add[n_moves].piece   = rook;
					if(      rm_k_castle ) { BIT_CLEAR( moves_add[n_moves].parameters, 1+bit_offset ); }
					else if( rm_q_castle ) { BIT_CLEAR( moves_add[n_moves].parameters, 2+bit_offset ); }
					n_moves++;
                                        n_count = 7;
                                }
				else if( (not_all_pieces >> index_update) & 1 ) {    // Empty
					moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,index_update);
					moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,indices[i]);
					moves_add[n_moves].piece   = rook;
					if(      rm_k_castle ) { BIT_CLEAR( moves_add[n_moves].parameters, 1+bit_offset ); }
					else if( rm_q_castle ) { BIT_CLEAR( moves_add[n_moves].parameters, 2+bit_offset ); }
					n_moves++;
                                        n_count++;
                                }
                                else { n_count = 7; }                                // Occupado
			}
		}
		i++;
	}
	return n_moves;
}

inline int queen_moves ( Moves *moves_add, uint64_t queens,  uint64_t their_pieces, uint64_t not_all_pieces ) {
	int n_moves = 0;

	int indices[4] = {-1,-1,-1,-1};
	convert_binary( queens, indices );

	int i = 0, n_count = 0, index_update;
	while( indices[i] != -1 ) {
		for( int n_direction = 0; n_direction < 8; n_direction++ ) {
			n_count = 0;
			index_update = indices[i];
			while( n_count < count_to_edge[indices[i]][n_direction] ) {
				index_update += index_directions[n_direction];
                                if( (their_pieces >> index_update) & 1 ) {	     // Capture
					moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,index_update);
					moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,indices[i]);
					moves_add[n_moves].piece   = queen;
					n_moves++;
                                        n_count = 7;
                                }
				else if( (not_all_pieces >> index_update) & 1 ) {    // Empty
					moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,index_update);
					moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,indices[i]);
					moves_add[n_moves].piece   = queen;
					n_moves++;
                                        n_count++;
                                }
                                else { n_count = 7; }                                // Occupado
			}
		}
		i++;
	}
	return n_moves;
}

inline int king_moves  ( Moves *moves_add, uint64_t Sr_king, uint64_t your_pieces, uint64_t their_pieces, uint64_t not_all_pieces,
			 int i_turn ) {
        int n_moves = 0;

        int index_curr = -1;
        convert_binary( Sr_king, &index_curr );

        int bit_offset = 0 + (1-i_turn);

        int index_update;
        for( int n_direction = 0; n_direction < 8; n_direction++ ) {
                index_update = index_curr + index_directions[n_direction];
                if( count_to_edge[index_curr][n_direction] != 0 ) {
                        if( !((your_pieces >> index_update) & 1) ) {
                                moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,index_update);
                                moves_add[n_moves].bitmove = BIT_SET(moves_add[n_moves].bitmove,index_curr);
                                moves_add[n_moves].piece   = king;
                                BIT_CLEAR( moves_add[n_moves].parameters, 1 + bit_offset );
                                BIT_CLEAR( moves_add[n_moves].parameters, 2 + bit_offset );
                                n_moves++;
			}
		}
	}
	return n_moves;
}

inline int piecey_pie_moves( Moves *moves_add, Pieces *your_pieces, uint64_t their_pieces, uint64_t not_all_pieces,
			     int t_en_passant, int i_turn ) {

	int n_moves = 0;

        n_moves += pawn_moves  ( &moves_add[n_moves], your_pieces->Pawns,   their_pieces,
				 not_all_pieces, t_en_passant, i_turn );
        n_moves += knight_moves( &moves_add[n_moves], your_pieces->Knights, ~your_pieces->All );
        n_moves += bishop_moves( &moves_add[n_moves], your_pieces->Bishops, their_pieces,
				 not_all_pieces );
        n_moves += rook_moves  ( &moves_add[n_moves], your_pieces->Rooks,   their_pieces,
				 not_all_pieces, i_turn );
        n_moves += queen_moves ( &moves_add[n_moves], your_pieces->Queens,  their_pieces,
	     			 not_all_pieces );
        n_moves += king_moves  ( &moves_add[n_moves], your_pieces->King, your_pieces->All, their_pieces,
	     			 not_all_pieces, i_turn );

	return n_moves;
}
