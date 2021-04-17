#include "global.h"

int pawn_counter = 0, knight_counter = 0, bishop_counter = 0, rook_counter = 0, queen_counter = 0, king_counter = 0;

int user_turn = 1, max_depth;

int move_index, move_row, move_column, from_index, from_row, from_column, move_piece, turn,
    n_possible_moves, en_passant;

const int pawn   =  1;
const int knight =  2;
const int bishop =  3;
const int rook   =  4;
const int queen  =  5;
const int king   =  6;

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

int piece_score[12] = { -9999, -800, -500, -300, -300, -100, 100, 300, 300, 500, 800, 9999 };
// b_king, b_queen, b_rook, b_bishop, b_knight, b_pawn, w_pawn, w_knight, w_bishop, w_rook, w_queen, w_king

int board[8][8] = { {w_rook, w_knight, w_bishop, w_queen, w_king, w_bishop, w_knight, w_rook},
		    {w_pawn, w_pawn,   w_pawn,   w_pawn,  w_pawn, w_pawn,   w_pawn,   w_pawn},
		    {0, 0, 0, 0, 0, 0, 0, 0},
		    {0, 0, 0, 0, 0, 0, 0, 0},
		    {0, 0, 0, 0, 0, 0, 0, 0},
		    {0, 0, 0, 0, 0, 0, 0, 0},
		    {b_pawn, b_pawn,   b_pawn,   b_pawn,  b_pawn, b_pawn,   b_pawn,   b_pawn},
		    {b_rook, b_knight, b_bishop, b_queen, b_king, b_bishop, b_knight, b_rook} };

int index_directions[8] = {  8,  1, -8, -1,  9, -7, -9,  7 };
int row_directions[8]   = {  1,  0, -1,  0,  1, -1, -1,  1 };
int col_directions[8]   = {  0,  1,  0, -1,  1,  1, -1, -1 };
int knight_moves[64][8], n_knight_moves[64], count_to_edge[64][8];
int n_params = 6;
int *params;
