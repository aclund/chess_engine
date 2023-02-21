#ifndef Globals
#define Globals

#include <iostream>
#include <cstring>
#include <inttypes.h>
#include <vector>
#include <random>

#ifdef MPI_ON
#include <mpi.h>
#endif

using namespace std;

/* a=target variable, b=bit number to act upon 0-n */
#define BIT_SET(a,b) ((a) |= (1ULL<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b))))        // '!!' to make sure this returns 0 or 1

inline void convert_binary( uint64_t bit, int *indices ) {
	int offset;
	int i = 0;
	while( bit ) {
		offset = __builtin_clzll(bit);
		indices[i] = 63-offset;
		BIT_FLIP(bit,63-offset);
		i++;
	}
	return;
}

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

struct rand_64 {
private:
    static mt19937_64 rng;
public:
    static void seed(uint64_t new_seed = mt19937_64::default_seed) {
        rng.seed(new_seed);
    }
    static uint64_t get() {
        return rng();
    }
};

struct Hash {
private:
	vector<uint64_t> hash_list;
	uint64_t hash_table[64][12];
	uint64_t hash_table_b2m;
public:
	Hash();
	void print( );
	void append( Chess_Board );
	bool rep3fold( );
};

typedef struct Moves_s Moves;
typedef struct Move_Tree_s Move_Tree;
struct Moves_s {
	Move_Tree *children;

	uint64_t bitmove;
	uint32_t parameters;
	uint8_t  piece;
};
struct Move_Tree_s {
	vector<Moves> moves_arr;
	Moves *best;
	Move_Tree_s() { best = nullptr; }
};

struct Search {
	int eval;
	int best_move;
};

extern int num_procs, myid, i_root;
extern bool l_root;

extern bool arg_color, arg_depth, basic, run, random_moves, read_fen;

extern int user_turn, max_depth;

extern int count_to_edge[64][8], index_directions[8], row_directions[8], col_directions[8],
           n_knight_moves[64];
extern uint64_t knight_squares[64][8];

extern const int castle, en_passant;

extern int move_index, move_row, move_column, move_piece, max_moves;

extern int mg_pieces[6], mg_pawn_table[64], mg_knight_table[64], mg_bishop_table[64],
	   mg_rook_table[64], mg_queen_table[64], mg_king_table[64], *mg_pst_table[6],
	   eg_pieces[6], eg_pawn_table[64], eg_knight_table[64], eg_bishop_table[64],
	   eg_rook_table[64], eg_queen_table[64], eg_king_table[64], *eg_pst_table[6],
	   piece2phase[6];
extern const uint8_t   pawn,   knight,   bishop,   rook,   queen,   king;
extern const int     w_pawn, w_knight, w_bishop, w_rook, w_queen, w_king,
		     b_pawn, b_knight, b_bishop, b_rook, b_queen, b_king;

#endif
