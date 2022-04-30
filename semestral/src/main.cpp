#include <ncurses.h>
#include <fstream>
#include <iostream>

#include "EAbility.h"
#include "CCardTroop.h"
#include "CCardWarcry.h"
#include "CCardGeneral.h"

#include "CDisplay.h"
#include "CShop.h"

using namespace std;

int main () {
	CDisplay init_screen;

	printw("Battle of Vostokhograd: The Card RPG\nSimon Ruzicka, 2022\n");

	refresh();

	#include "../tests/cdeck_test.cpp"

	return 0;
}
