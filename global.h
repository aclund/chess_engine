#ifndef Globals
#define Globals

extern int pawn_counter, knight_counter, bishop_counter, rook_counter, queen_counter, king_counter;


extern int user_turn, max_depth;

extern int move_index, move_row, move_column, from_index, from_row, from_column, move_piece, turn,
           n_possible_moves, en_passant, n_params;
extern int board[8][8], *params, piece_score[12];
extern int knight_moves[64][8], n_knight_moves[64], count_to_edge[64][8], index_directions[8],
           row_directions[8], col_directions[8];
extern const int   pawn,   knight,   bishop,   rook,   queen,   king,
		 w_pawn, w_knight, w_bishop, w_rook, w_queen, w_king,
		 b_pawn, b_knight, b_bishop, b_rook, b_queen, b_king;

#endif
