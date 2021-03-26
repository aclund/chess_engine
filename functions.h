
#ifndef functions
#define functions

using namespace std;

void write_board();
void move();
int valid_move(string,int);
void index_square(string,int*,int*);
void convert_fen();
void set_moves();
void ask_user();
void all_moves(int*, int**);
void random_player();
void engine();

bool in_range(int,int);
int rc2index(int,int);
void index2rc(int,int*,int*);


#endif
