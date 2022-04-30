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

	CDeck deck;
	ifstream input( "examples/decks/start_hand.csv" );
	deck.load_deck(input);
	input.close();

	init_screen.card_selection(deck);

	return 0;
}
