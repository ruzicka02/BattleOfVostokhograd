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

using namespace std;

int main () {
	CDisplay init_screen;

	mvprintw(2, 0, "Battle of Vostokhograd: The Card RPG\nSimon Ruzicka, 2022\n");

	refresh();

	#include "tests/cardselection_test.cpp"

	return 0;
}
