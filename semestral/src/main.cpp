#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstring>
#include <csignal>

#include "Test.h"

#include "EAbility.h"
#include "CCardTroop.h"
#include "CCardWarcry.h"
#include "CCardGeneral.h"

#include "CDisplay.h"
#include "CShop.h"
#include "CPlayerHuman.h"

using namespace std;

void sigint_handler( int num ) {
	endwin(); // shut down ncurses

	cout << "Interrupt signal called, game was terminated automatically";
	exit(0);
}

int main ( int argc, char* argv[] ) {
	signal(SIGINT, sigint_handler);

	CDisplay init_screen;
	init_screen.context_bar("Initial test");
	if ( ! init_screen.terminal_size_check() )
		return 1;

	mvprintw(1, 0, "Battle of Vostokhograd: The Card RPG\nSimon Ruzicka, 2022\n");

	refresh();

	// tests
	if ( argc > 1 && ! strcmp( argv[1], "--debug") ) {
		endwin();

		play_card_t();
		CDisplay_t();
		CDeck_t();
		refresh_board_t();
		card_selection_t();
	}

	// reduces the amount of ncurses mem leaks, does not work on testing Docker
	// exit_curses(0);
	return 0;
}
