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

	printw("Battle of Vostokhograd: The Card RPG\nSimon Ruzicka, 2022\n");

	refresh();

#include "../tests/cdeck_test.cpp"

//	CDeck deck;
//	ifstream input( "examples/decks/start_hand.csv" );
//	deck.load_deck(input);
//	input.close();

//	init_screen.card_selection(deck);

	return 0;
}
