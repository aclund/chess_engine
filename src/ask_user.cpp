#include "functions.h"

void ask_user( bool engine ) {

	bool found;

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
	if( !arg_color ) {
		string color;
		found = false;
		while( found == false ) {
			cout << "Pick a Color to Play (w/b): ";
			getline(cin,color);
			found = true;
			if(      color.find('w') != string::npos or
			         color.find('W') != string::npos ) { user_turn = 0; }
			else if( color.find('b') != string::npos or
			         color.find('B') != string::npos ) { user_turn = 1; }
			else{ cout << "Pick a Color??\n"; found = false; }
		}
		cout << "\n";
	}


	// MAX DEPTH
	if( engine && !arg_depth) {
		found = false;
		while( found == false ) {
			cout << "Ender Maximum Search Depth RECOMENDED (4-6): ";
			cin >> max_depth;
			cout << "\n";
			if( !cin.good() ) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "ERROR\n";
			 }
			else if( max_depth > 0 && max_depth < 11 ) { found = true; }
			else if( max_depth > 10 ) { cout << "Eh dont get ahead of yourself\n"; }
		}
		cin.ignore();
		cout << "\n";
	}

	return;
}
