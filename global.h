#ifndef Globals
#define Globals

extern int user_turn, max_depth;

extern int move_index, move_row, move_column, from_index, from_row, from_column, move_piece, turn,
           n_possible_moves, en_passant;
extern int board[8][8];
extern int knight_moves[64][8], n_knight_moves[64], count_to_edge[64][8], index_directions[8],
           row_directions[8], col_directions[8];;
extern const int   pawn,   knight,   bishop,   rook,   queen,   king,
		 w_pawn, w_knight, w_bishop, w_rook, w_queen, w_king,
		 b_pawn, b_knight, b_bishop, b_rook, b_queen, b_king;

#endif
