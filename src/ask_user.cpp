#include <string>
#include <limits>
#include <iostream>

using namespace std;

#include "global.h"
#include "functions.h"

void ask_user( bool engine ) {

	bool found;

	cout << "\n WARNING: Engine may attempt to stalemate over checkmate...\n\n";

	cout << "_____________________________________________________________________\n";
	cout << "   __________                  __________   __________    __________ \n";
	cout << "  |             |          |  |            |             |           \n";
	cout << "  |             |          |  |            |             |           \n";
	cout << "  |             |          |  |            |             |           \n";
	cout << "  |             |----------|  |----------   ----------    ---------- \n";
	cout << "  |             |          |  |                       |             |\n";
	cout << "  |             |          |  |                       |             |\n";
	cout << "  |__________   |          |  |__________   __________|   __________|\n";
	cout << "_____________________________________________________________________\n\n";


	// COLOR
	string color;
	found = false;
//found = true; user_turn = -1*params[0];
	while( found == false ) {
		cout << " Pick a Color to Play\n\n";
		cin >> color;
		found = true;
		if(      color.find('w') != string::npos or 
			 color.find('W') != string::npos ) { user_turn =  1; }
		else if( color.find('b') != string::npos or 
			 color.find('B') != string::npos ) { user_turn = -1; }
		else{ cout << " Pick a Color??\n"; found = false; }
	}
	cout << "\n";


	// MAX DEPTH
	if( engine ) {
		found = false;
		while( found == false ) {
			cout << " Ender Maximum Search Depth\n";
			cout << " Current RECOMENDATION(4-6)\n\n";
			cin >> max_depth;
			cout << "\n";
			if( !cin.good() ) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << " ERROR\n";
			 }
			else if( max_depth > 0 && max_depth < 11 ) { found = true; }
			else if( max_depth > 10 ) { cout << " Eh dont get ahead of yourself\n"; }
		}
	}

	return;
}
