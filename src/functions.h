#ifndef functions
#define functions

#include "global.h"

void setup_mpi(int,char**);
void command_args(int,char**);
void stop_on_error(int);
void initial_position(Chess_Board*);
int convert_fen(Chess_Board*);
void set_moves();
void all_moves(Chess_Board,vector<Moves>&);
Chess_Board preform_move(Chess_Board,Moves);
void check_check(uint64_t,uint64_t,Pieces*,uint64_t,int,int*);
bool in_check(Chess_Board);
void random_player(Chess_Board*);
void engine(Chess_Board*,Hash);
void generator(Chess_Board,Move_Tree*,Hash,int);
Search minimax     (Chess_Board,vector<Moves>,Hash,int,int,int,bool);
Search minimax_tree(Chess_Board,Move_Tree*,   Hash,int,int,int,bool);
void convert2board(Chess_Board,int*,int*);
void convert2bits(int*,int*,Chess_Board*);
void is_over(Chess_Board,Hash,int);
Moves* newMoves(uint32_t,int);
void new_moves(Moves*,int,uint32_t);
void freeTree(Move_Tree*);

void write_board(Chess_Board);
void move(Chess_Board*);
int valid_move(Chess_Board,string,vector<Moves>,int*);
void index_square(string,int*,int*);
void ask_user(bool);
bool game_over(Chess_Board,Hash);

int check_bits(Chess_Board);
void print_binary(uint64_t);
void bits2squares(uint64_t);
void print_moves(Moves*,int,uint64_t);
void last_known_board(Chess_Board);

bool in_range(int,int);
int rc2index(int,int);
void index2rc(int,int*,int*);
int pawn_rel_rank(int, int);
string index2square(int);

#endif
