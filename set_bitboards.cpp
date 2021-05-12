//using namespace std;

#include "global.h"
#include "functions.h"

void set_bitboards() {

	bitboards.White.Pawns = 0;
	for( int index = 8; index < 16; index++ ) {
		BIT_SET(bitboards.White.Pawns,index);
	}
	bitboards.White.Knights = 0;
	BIT_SET(bitboards.White.Knights,1);
	BIT_SET(bitboards.White.Knights,6);
	bitboards.White.Bishops = 0;
	BIT_SET(bitboards.White.Bishops,2);
	BIT_SET(bitboards.White.Bishops,5);
	bitboards.White.Rooks = 0;
	BIT_SET(bitboards.White.Rooks,0);
	BIT_SET(bitboards.White.Rooks,7);
	bitboards.White.Queens = 0;
	BIT_SET(bitboards.White.Queens,3);
	bitboards.White.King = 0;
	BIT_SET(bitboards.White.King,4);
		
	bitboards.Black.Pawns = 0;
	for( int index = 48; index < 56; index++ ) {
		BIT_SET(bitboards.Black.Pawns,index);
	}
	bitboards.Black.Knights = 0;
	BIT_SET(bitboards.Black.Knights,57);
	BIT_SET(bitboards.Black.Knights,62);
	bitboards.Black.Bishops = 0;
	BIT_SET(bitboards.Black.Bishops,58);
	BIT_SET(bitboards.Black.Bishops,61);
	bitboards.Black.Rooks = 0;
	BIT_SET(bitboards.Black.Rooks,56);
	BIT_SET(bitboards.Black.Rooks,63);
	bitboards.Black.Queens = 0;
	BIT_SET(bitboards.Black.Queens,59);
	bitboards.Black.King = 0;
	BIT_SET(bitboards.Black.King,60);

	bitboards.White.All = 0;
	for( int index = 0; index < 16; index++ ) {
		BIT_SET(bitboards.White.All,index);
	}
	bitboards.Black.All = 0;
	for( int index = 48; index < 64; index++ ) {
		BIT_SET(bitboards.Black.All,index);
	}

	bitboards.All_Pieces = 0;
	bitboards.All_Pieces |= bitboards.White.All;
	bitboards.All_Pieces |= bitboards.Black.All;


	bitboards.Parameters = 0;
	BIT_SET(bitboards.Parameters,1); // K
	BIT_SET(bitboards.Parameters,2); // Q
	BIT_SET(bitboards.Parameters,3); // k
	BIT_SET(bitboards.Parameters,4); // q
	// Turn, En Passant, # move 0

	return;
}
