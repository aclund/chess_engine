#include "global.h"

Hash::Hash() {
	for( int i=0; i<64; i++ ) {
		for( int n=0; n<12; n++ ) {
			hash_table[i][n] = rand_64::get();
		}
	}
	hash_table_b2m = rand_64::get();
}
void Hash::print() {
	for( int i=0; i<hash_list.size(); i++ ) {
		cout << hash_list[i] << "\n";
	}
}
void Hash::append( Chess_Board chess_board ) {
	uint64_t new_hash = 0Ull;
	int piece_ref = 0;
	for( uint64_t* piece = (uint64_t*)&chess_board.White.Pawns;
    		       piece < (uint64_t*)((uint8_t*)&chess_board.White.Pawns + 6*sizeof(uint64_t)); piece++ ) {
		int index[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
		convert_binary( *piece, index );
		int i = 0;
		while( index[i] != -1 ) {
			new_hash ^= hash_table[index[i]][piece_ref];
			i++;
		}
		piece_ref++;
	}
	for( uint64_t* piece = (uint64_t*)&chess_board.Black.Pawns;
    		       piece < (uint64_t*)((uint8_t*)&chess_board.Black.Pawns + 6*sizeof(uint64_t)); piece++ ) {
		int index[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
		convert_binary( *piece, index );
		int i = 0;
		while( index[i] != -1 ) {
			new_hash ^= hash_table[index[i]][piece_ref];
			i++;
		}
		piece_ref++;
	}
	if( !(chess_board.Parameters & 1) ) {
		new_hash ^= hash_table_b2m;
	}
	hash_list.push_back( new_hash );
}
bool Hash::rep3fold() {
	if( hash_list.size() == 0 ) return false;
	uint64_t current = hash_list.back();
	int repeat = 0;
	for( int i=hash_list.size()-2; i>=0; i-- ) {
		if( hash_list[i] == current ) {
			repeat++;
			if( repeat == 2 ) return true;
		}
	}
	return false;
}

int num_procs, myid, i_root = 0;
bool l_root;

bool arg_color = false, arg_depth = false, basic = false, read_fen = false, random_moves = false, run = true;

int user_turn, max_depth;

//                     pawns, knights, bishops, rooks, queens, king
int piece_scores[6] = { 100, 340, 350, 525, 1000, 9999 };

int index_directions[8] = {  8,  1, -8, -1,  9, -7, -9,  7 };
int row_directions[8]   = {  1,  0, -1,  0,  1, -1, -1,  1 };
int col_directions[8]   = {  0,  1,  0, -1,  1,  1, -1, -1 };
int count_to_edge[64][8], n_knight_moves[64];
uint64_t knight_squares[64][8];


const int castle     =  7;
const int en_passant = 12;

int move_index, move_row, move_column, move_piece, max_moves = 111;

const uint8_t pawn   =  1;
const uint8_t knight =  2;
const uint8_t bishop =  3;
const uint8_t rook   =  4;
const uint8_t queen  =  5;
const uint8_t king   =  6;

const int w_pawn   =  pawn;
const int w_knight =  knight;
const int w_bishop =  bishop;
const int w_rook   =  rook;
const int w_queen  =  queen;
const int w_king   =  king;
const int b_pawn   = -pawn;
const int b_knight = -knight;
const int b_bishop = -bishop;
const int b_rook   = -rook;
const int b_queen  = -queen;
const int b_king   = -king;
