#ifndef Globals
#define Globals

#include <inttypes.h>

/* a=target variable, b=bit number to act upon 0-n */
#define BIT_SET(a,b) ((a) |= (1ULL<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b))))        // '!!' to make sure this returns 0 or 1


struct Pieces {
	uint64_t Pawns;
	uint64_t Knights;
	uint64_t Bishops;
	uint64_t Rooks;
	uint64_t Queens;
	uint64_t King;

	uint64_t All;
};
struct Chess_Board {
	Pieces White;
	Pieces Black;

	uint64_t All_Pieces;

	uint32_t Parameters;
};
extern Chess_Board bitboards;

typedef struct Moves_s Moves;
typedef struct Move_Tree_s Move_Tree;
struct Moves_s {
	Move_Tree *children;
	//Move_Tree *parents;

	uint64_t bitmove;
	uint32_t parameters;
	uint8_t  piece;
};
struct Move_Tree_s {
	int n_moves;
	Moves *moves_arr;
};

struct Moves_temp {
	uint64_t bitmove;
	uint8_t  piece;
};

extern int user_turn, max_depth;

extern int count_to_edge[64][8], index_directions[8], row_directions[8], col_directions[8],
           n_knight_moves[64];
extern uint64_t knight_squares[64][8];

extern const int castle, en_passant;

extern int move_index, move_row, move_column, move_piece, max_moves;

extern int board[64], *params, n_params;
extern int mg_pieces[6], mg_pawn_table[64], mg_knight_table[64], mg_bishop_table[64],
	   mg_rook_table[64], mg_queen_table[64], mg_king_table[64], *mg_pst_table[6],
	   eg_pieces[6], eg_pawn_table[64], eg_knight_table[64], eg_bishop_table[64],
	   eg_rook_table[64], eg_queen_table[64], eg_king_table[64], *eg_pst_table[6],
	   piece2phase[6];
extern const uint8_t   pawn,   knight,   bishop,   rook,   queen,   king;
extern const int     w_pawn, w_knight, w_bishop, w_rook, w_queen, w_king,
		     b_pawn, b_knight, b_bishop, b_rook, b_queen, b_king;

#endif
