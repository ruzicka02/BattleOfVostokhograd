#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cassert>

#include "EAbility.h"
#include "CCardTroop.h"
#include "CCardWarcry.h"
#include "CCardGeneral.h"

#include "CDisplay.h"
#include "CShop.h"
#include "CPlayerHuman.h"

using namespace std;

int main () {
	CDisplay init_screen;
	init_screen.context_bar("Initial test");
	if ( ! init_screen.terminal_size_check() )
		return 1;

	mvprintw(1, 0, "Battle of Vostokhograd: The Card RPG\nSimon Ruzicka, 2022\n");

	refresh();


#include "tests/cardselection_test.cpp"

	return 0;
}
