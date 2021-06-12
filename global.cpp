#include "global.h"
#include "functions.h"

Chess_Board bitboards;

//int pawn_counter = 0, knight_counter = 0, bishop_counter = 0, rook_counter = 0, queen_counter = 0, king_counter = 0;

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

int n_params = 6;
int  *params = new int[n_params];

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

int board[64] = { w_rook, w_knight, w_bishop, w_queen, w_king, w_bishop, w_knight, w_rook,
		  w_pawn, w_pawn,   w_pawn,   w_pawn,  w_pawn, w_pawn,   w_pawn,   w_pawn,
		  0, 0, 0, 0, 0, 0, 0, 0,
		  0, 0, 0, 0, 0, 0, 0, 0,
		  0, 0, 0, 0, 0, 0, 0, 0,
		  0, 0, 0, 0, 0, 0, 0, 0,
		  b_pawn, b_pawn,   b_pawn,   b_pawn,  b_pawn, b_pawn,   b_pawn,   b_pawn,
		  b_rook, b_knight, b_bishop, b_queen, b_king, b_bishop, b_knight, b_rook };
