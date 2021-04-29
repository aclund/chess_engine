#include <string>

#ifndef functions
#define functions

using namespace std;

void write_board();
void move();
int valid_move(string,int);
void index_square(string,int*,int*);
void convert_fen();
void set_moves();
void ask_user(bool);
void all_moves(int*, int*, int**, int**);
void piece_moves(int*, int*, int**, int, int*, int*);
void check_check(int, int*, int*, int*, int*);
void in_check(int*, int*, int*, int, int*, int*, int*);
void random_player();
void engine();
int minimax(int**, int, int, int, bool);
int score(int*);
bool game_over();

bool in_range(int,int);
int rc2index(int,int);
void index2rc(int,int*,int*);
int pawn_rel_rank(int, int);
void write_from2d(int**,bool);


#endif
