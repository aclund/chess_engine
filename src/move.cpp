#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#include "functions.h"
#include "global.h"

string removeSpaces(string str)  
{ 
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
    str.erase(remove(str.begin(), str.end(), 'x'), str.end()); 
    return str; 
} 

void move( ) {

	string move_AN;
	int ierr = 1;
	while( ierr != 0 ) {
		cout << "Enter move\n\n";
		cin  >> move_AN;
		cout << "\n";
		move_AN = removeSpaces(move_AN);
	
		int n_possible_moves;
		ierr = valid_move( move_AN, &n_possible_moves );

		if( ierr != 0 ) {
			cout << "Either I suck at coding or you've forgotten the rules of CHESS!\n\n";
			cout << "Enter move in Algebraic Notation:\n";
			cout << "   nf3  Qd1  o-o  rfd1\n\n\n";
			move_AN.clear();
		}
		else if( n_possible_moves == 0 ) { return; }
	}

	return;
}
