#include <string>
#include <iostream>

using namespace std;

#include "global.h"
#include "functions.h"

void ask_user( bool engine ) {

	bool found;

	cout << "_____________________________________________________\n\n";
	cout << "  Welcome to SHIT Chess \n\n";
	cout << "  The only chess program worse than you!\n";
	cout << "  I would wish you luck but the rules are faulty SO\n";
	cout << "  GO FUCK YOURSELF\n\n";


	// COLOR
	string color;
	found = false;
found = true; user_turn = -1*turn;
	while( found == false ) {
		cout << " Pick a Color to Play (w/b)\n";
		cin >> color;
		found = true;
		if(      color.find('w') != string::npos or 
			 color.find('W') != string::npos ) { user_turn =  1; }
		else if( color.find('b') != string::npos or 
			 color.find('B') != string::npos ) { user_turn = -1; }
		else{ cout << " Pick a Color??\n"; found = false; }
	}


	// MAX DEPTH
	if( engine ) {
		found = false;
		while( found == false ) {
			cout << " Ender Maximum Search Depth\n";
			cin >> max_depth;
			if( max_depth >= 0 && max_depth < 11 ) { found = true; }
			else if( max_depth > 10 ) { cout << " Eh dont get ahead of yourself\n"; }
			else { cout << " ERROR\n"; }
		}
	}

	return;
}
