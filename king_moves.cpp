#include "iostream"
using namespace std;

#include "functions.h"
#include "global.h"
#include "initialize.h"
#include "convert_binary.h"
#include "piece_moves.h"
#include "check_check.h"

int king_moves  ( Moves *moves_add, uint64_t Sr_king, uint64_t your_pieces, Pieces *their_pieces, uint64_t not_all_pieces,
                  int i_turn ) {
	int spot = 0;

	int index_curr = -1;
	convert_binary( Sr_king, &index_curr );

	int bit_offset = 0;
	if( i_turn == -1 ) { bit_offset = 2; }

	int n_checks, index_update;
	uint64_t Sr_peak;
	Moves_temp *check_pieces = newTemp(2);
	for( int n_direction = 0; n_direction < 8; n_direction++ ) {
		index_update = index_curr + index_directions[n_direction];
		if( count_to_edge[index_curr][n_direction] != 0 ) {
			if( (not_all_pieces >> index_update) & 1 ) {			     // Empty
				Sr_peak = 0;
				BIT_SET( Sr_peak, index_update );
//cout << " I spy with my little eye an open square " << index_update<<endl << king<<endl;
				check_check( Sr_peak, your_pieces, their_pieces, not_all_pieces, i_turn, 
					     check_pieces, &n_checks );
				if( n_checks == 0 ) {
//cout << " K @:" << index_curr << " heading to free lands @:" << index_update<<endl;
					moves_add[spot].bitmove = BIT_SET(moves_add[spot].bitmove,index_update);
					moves_add[spot].bitmove = BIT_SET(moves_add[spot].bitmove,index_curr);
					moves_add[spot].piece   = king;
					BIT_CLEAR( moves_add[spot].parameters, 1 + bit_offset );
					BIT_CLEAR( moves_add[spot].parameters, 2 + bit_offset );
					spot++;
				}
			}
			else if( (their_pieces->All >> index_update) & 1 ) {         	     // Capture
				Sr_peak = 0;
				BIT_SET( Sr_peak, index_update );
				Pieces *temp = their_pieces;
				temp->Pawns   &= ~Sr_peak;
				temp->Knights &= ~Sr_peak;
				temp->Bishops &= ~Sr_peak;
				temp->Rooks   &= ~Sr_peak;
				temp->Queens  &= ~Sr_peak;
				check_check( Sr_peak, your_pieces, temp, not_all_pieces, i_turn, 
					     check_pieces, &n_checks );
				if( n_checks == 0 ) {
cout << " K @:" << index_curr << " heading to absolutely demolish @:" << index_update<<endl;
					moves_add[spot].bitmove = BIT_SET(moves_add[spot].bitmove,index_update);
					moves_add[spot].bitmove = BIT_SET(moves_add[spot].bitmove,index_curr);
					moves_add[spot].piece   = king;
					BIT_CLEAR( moves_add[spot].parameters, 1 + bit_offset );
					BIT_CLEAR( moves_add[spot].parameters, 2 + bit_offset );
					spot++;
				}
			}
		}
	}
	return spot;
}

