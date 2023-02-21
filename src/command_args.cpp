#include "functions.h"

bool is_number(char number[]) {
    for (int i=0; number[i] != 0; i++) {
        if( !isdigit(number[i]) ) return false;
    }
    return true;
}

void command_args( int argc, char *argv[] ) {
	for( int i = 1; i < argc; i++ ) {
		if(      strcmp(argv[i], "--fen"    ) == 0 ) { read_fen = true; }
		else if( strcmp(argv[i], "-r"       ) == 0 ||
		         strcmp(argv[i], "--random" ) == 0 ) { run = false; random_moves = true; }
		else if( strcmp(argv[i], "--off"    ) == 0 ) { run = false; }
		else if( strcmp(argv[i], "-b"       ) == 0 ||
		         strcmp(argv[i], "--basic"  ) == 0 ) { basic = true; }
		else if( strcmp(argv[i], "-c"       ) == 0 ||
		         strcmp(argv[i], "--color"  ) == 0 ) {
			if( i+1 == argc ) break;
			arg_color = true;
			string color = argv[i+1];
			if(      color.find('w') != string::npos or
			         color.find('W') != string::npos ) { user_turn = 0; }
			else if( color.find('b') != string::npos or
			         color.find('B') != string::npos ) { user_turn = 1; }
			else { arg_color = false; }
		}
		else if( strcmp(argv[i], "-d"       ) == 0 ||
		         strcmp(argv[i], "--depth"  ) == 0 ) {
			if( i+1 == argc ) break;
			arg_depth = true;
			if( is_number(argv[i+1]) ) {
				max_depth = stoi(argv[i+1]);
				if( max_depth <= 0 && max_depth > 10 ) { arg_depth = false; }
			}
			else { arg_depth = false; }
		}
	}
}
