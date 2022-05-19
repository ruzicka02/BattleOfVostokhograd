#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <csignal>

#include "Test.h"

#include "CGame.h"

using namespace std;

void sigint_handler( int num ) {
	endwin(); // shut down ncurses

	cout << "Interrupt signal called, game was terminated automatically";
	exit(0);
}

int main ( int argc, char* argv[] ) {
	signal(SIGINT, sigint_handler);

	// tests
	if ( argc > 1 && ! strcmp( argv[1], "--debug") ) {
		play_card_t();
		CDisplay_t();
		CDeck_t();
		refresh_board_t();
		card_selection_t();
	}

	CGame game; // all game actions started from this constructor

	return 0;
}
