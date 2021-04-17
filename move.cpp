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

	int ierr = 1;
	string move_AN;
	while( ierr != 0 ) {
		cout << "Enter move\n";
		cin >> move_AN;
		move_AN = removeSpaces(move_AN);
	
		n_possible_moves = -1;
		ierr = valid_move(move_AN,ierr);

		if( n_possible_moves == 0 ) { return; }

		if( ierr != 0 ) {
			//cout << "Ima stupid cunt\n";
			move_AN.clear();
		}
		cout << "\n";
	}

	return;
}
