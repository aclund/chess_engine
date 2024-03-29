#include "global.h"

void convert2bits( int board[64], int params[6], Chess_Board *bitboards ) {

	// Params
	bitboards->Parameters    = 0;
	if( params[0] == -1 ) {
		BIT_SET( bitboards->Parameters, 0 );
	}
	for( int i = 1; i < 5; i++ ) {
		if( params[i] == 1 ) {
			BIT_SET( bitboards->Parameters, i );
		}
	}
	int t_en_passant = params[5], bit2 = 32;
	if( t_en_passant != -1 ) {
		for( int i = 17; i > 11; i-- ) {
			if( int(t_en_passant/bit2) == 1 ) {
				BIT_SET( bitboards->Parameters, i );
				t_en_passant -= bit2;
			}
			bit2 /= 2;
		}
		if( t_en_passant != 0 ) { std::cout << " ERROR en passant conversion in convert2bits!\n"; }
	}
	

	bitboards->White.Pawns   = 0;
	bitboards->White.Knights = 0;
	bitboards->White.Bishops = 0;
	bitboards->White.Rooks   = 0;
	bitboards->White.Queens  = 0;
	bitboards->White.King    = 0;
	bitboards->White.All     = 0;

	bitboards->Black.Pawns   = 0;
	bitboards->Black.Knights = 0;
	bitboards->Black.Bishops = 0;
	bitboards->Black.Rooks   = 0;
	bitboards->Black.Queens  = 0;
	bitboards->Black.King    = 0;
	bitboards->Black.All     = 0;

	for( int i = 0; i < 64; i++ ) {
		if( board[i] != 0 ) {
			switch( board[i] ) {
			  case  1: // w_pawn
				BIT_SET( bitboards->White.Pawns,   i );
				BIT_SET( bitboards->White.All,     i );
			  break;
			  case  2: // w_knight
				BIT_SET( bitboards->White.Knights, i );
				BIT_SET( bitboards->White.All,     i );
			  break;
			  case  3: // w_bishop
				BIT_SET( bitboards->White.Bishops, i );
				BIT_SET( bitboards->White.All,     i );
			  break;
			  case  4: // w_rook
				BIT_SET( bitboards->White.Rooks,   i );
				BIT_SET( bitboards->White.All,     i );
			  break;
			  case  5: // w_queen
				BIT_SET( bitboards->White.Queens,  i );
				BIT_SET( bitboards->White.All,     i );
			  break;
			  case  6: // w_king
				BIT_SET( bitboards->White.King,    i );
				BIT_SET( bitboards->White.All,     i );
			  break;

			  case -1: // b_pawn
				BIT_SET( bitboards->Black.Pawns,   i );
				BIT_SET( bitboards->Black.All,     i );
			  break;
			  case -2: // b_knight
				BIT_SET( bitboards->Black.Knights, i );
				BIT_SET( bitboards->Black.All,     i );
			  break;
			  case -3: // b_bishop
				BIT_SET( bitboards->Black.Bishops, i );
				BIT_SET( bitboards->Black.All,     i );
			  break;
			  case -4: // b_rook
				BIT_SET( bitboards->Black.Rooks,   i );
				BIT_SET( bitboards->Black.All,     i );
			  break;
			  case -5: // b_queen
				BIT_SET( bitboards->Black.Queens,  i );
				BIT_SET( bitboards->Black.All,     i );
			  break;
			  case -6: // b_king
				BIT_SET( bitboards->Black.King,    i );
				BIT_SET( bitboards->Black.All,     i );
			  break;
			}
		}
	}

	bitboards->All_Pieces    = 0;
	bitboards->All_Pieces   |= bitboards->White.All;
	bitboards->All_Pieces   |= bitboards->Black.All;

	return;
}
