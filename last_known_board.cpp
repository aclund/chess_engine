#include <fstream>
#include <iostream>
using namespace std;

#include "global.h"
#include "functions.h"

void last_known_board( ) {

	ofstream fenfile;
	fenfile.open( "last_known_position.fen", ofstream::out | ofstream::trunc );

	

	fenfile.close();
	return;
}
