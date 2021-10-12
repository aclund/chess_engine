
#include "global.h"
#include "convert_binary.h"

void reset( int *arr ) {
	for( int i = 0; i < 9; i++ ) {
		arr[i] = -1;
	}
}

// Take global bitboards -> global board[][]
void convert2board(){

	for( int n = 0; n < n_params; n++ ) {
		params[n] = 0;
	}

	if( bitboards.Parameters & 1 ) {
		params[0] = -1;
	} else {
		params[0] =  1;
	}
	for( int i = 1; i < 5; i++ ) {
		if( (bitboards.Parameters >> i) & 1 ) {
			params[i] = 1;
		}
	}
	int t_en_passant = 0, bit2 = 1;
	for( int i = 12; i < 18; i++ ) {
		if( (bitboards.Parameters >> i) & 1 ) {
			t_en_passant += bit2;
		}
		bit2 *= 2;
	}
	if( t_en_passant == 0 ) { params[5] = -1; }
	else { params[5] = t_en_passant; }


	for( int i = 0; i < 64; i++ ) {
		board[i] = 0;
	}

	int indices[9], i;
	
	reset( indices );
	convert_binary( bitboards.White.Pawns, indices );
	i = 0;
	while( indices[i] != -1 ) {
		board[indices[i]] = w_pawn;
		i++;
	}
	reset( indices );
	convert_binary( bitboards.Black.Pawns, indices );
	i = 0;
	while( indices[i] != -1 ) {
		board[indices[i]] = b_pawn;
		i++;
	}
	reset( indices );
	convert_binary( bitboards.White.Knights, indices );
	i = 0;
	while( indices[i] != -1 ) {
		board[indices[i]] = w_knight;
		i++;
	}
	reset( indices );
	convert_binary( bitboards.Black.Knights, indices );
	i = 0;
	while( indices[i] != -1 ) {
		board[indices[i]] = b_knight;
		i++;
	}
	reset( indices );
	convert_binary( bitboards.White.Bishops, indices );
	i = 0;
	while( indices[i] != -1 ) {
		board[indices[i]] = w_bishop;
		i++;
	}
	reset( indices );
	convert_binary( bitboards.Black.Bishops, indices );
	i = 0;
	while( indices[i] != -1 ) {
		board[indices[i]] = b_bishop;
		i++;
	}
	reset( indices );
	convert_binary( bitboards.White.Rooks, indices );
	i = 0;
	while( indices[i] != -1 ) {
		board[indices[i]] = w_rook;
		i++;
	}
	reset( indices );
	convert_binary( bitboards.Black.Rooks, indices );
	i = 0;
	while( indices[i] != -1 ) {
		board[indices[i]] = b_rook;
		i++;
	}
	reset( indices );
	convert_binary( bitboards.White.Queens, indices );
	i = 0;
	while( indices[i] != -1 ) {
		board[indices[i]] = w_queen;
		i++;
	}
	reset( indices );
	convert_binary( bitboards.Black.Queens, indices );
	i = 0;
	while( indices[i] != -1 ) {
		board[indices[i]] = b_queen;
		i++;
	}
	reset( indices );
	convert_binary( bitboards.White.King, indices );
	i = 0;
	while( indices[i] != -1 ) {
		board[indices[i]] = w_king;
		i++;
	}
	reset( indices );
	convert_binary( bitboards.Black.King, indices );
	i = 0;
	while( indices[i] != -1 ) {
		board[indices[i]] = b_king;
		i++;
	}

	return;
}
