#include <ncurses.h>
#include <fstream>
#include <iostream>

#include "EAbility.h"
#include "CCardTroop.h"
#include "CCardWarcry.h"
#include "CCardGeneral.h"

#include "CDisplay.h"

using namespace std;

int main () {
	CDisplay screen;

	printw("Battle of Vostokhograd: The Card RPG\nSimon Ruzicka, 2022\n");
	if ( can_change_color() ) printw("Can change color\n");
	if ( has_colors() ) printw("Has colors\n");

	refresh();

	// CCard showcase
	auto card_t = CCardTroop("Name", "Sample description", 1, 2, 3, 4, 5, null);
	auto card_w = CCardWarcry("Warcry Name", "Another sample\ndescription", 1, 2, 3, 4, steal);
	auto card_g = CCardGeneral("General Windishgratz", "This general is the best general in the world", 50, 2, 3, 4, 1, null);

	card_t.print_card(5, 0);
	card_w.print_card(5, 25);
	card_g.print_card(5, 50);

	card_g.change_life(-8);
	card_g.print_card(5, 75);

	getch();

	// CDeck showcase
	CDeck deck;
	ifstream input( "examples/decks/start_hand.csv" );
	deck.load_deck(input);


	deck.pop_top()->print_card(5, 0);
	deck.pop_top()->print_card(5, 25);
	deck.pop_top()->print_card(5, 50);
	deck.pop_top()->print_card(5, 75);


	getch();
	endwin();

	// fixme... cards not scanned
	cout << deck.cards().size() << endl;

	return 0;
}
