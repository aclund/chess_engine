#include <string>

#ifndef functions
#define functions

using namespace std;

#include "global.h"

void set_bitboards();
void set_moves();
void all_moves(Chess_Board,Moves*,int*);
int in_check(Moves*,Chess_Board,Moves_temp,uint64_t,int);
//int king_moves(Moves*,uint64_t,uint64_t,Pieces*,uint64_t,int);
//void check_check(uint64_t,uint64_t,Pieces*,uint64_t,uint64_t*,int*);
void random_player();
void engine();
void generator(Chess_Board,Move_Tree*,int);
int minimax(Chess_Board,Move_Tree*,int,int,int,bool,int*);
void convert2board();
void convert2bits();
void is_over(Chess_Board,int);

void write_board(int*,int*);
void move();
int valid_move(string,int*);
void index_square(string,int*,int*);
int convert_fen();
void ask_user(bool);
bool game_over( Chess_Board );

int check_bits(Chess_Board);
void print_moves(Moves*,int,uint64_t);
void last_known_board();

/*
int minimax(int**, int, int, int, bool);
int score(int*);
*/

Move_Tree* newTree(Moves*,int);
void freeTree(Move_Tree*);
void print_binary(uint64_t);

bool in_range(int,int);
int rc2index(int,int);
void index2rc(int,int*,int*);
int pawn_rel_rank(int, int);
string index2square(int);

#endif
