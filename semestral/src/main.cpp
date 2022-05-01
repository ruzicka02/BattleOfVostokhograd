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

	mvprintw(2, 0, "Battle of Vostokhograd: The Card RPG\nSimon Ruzicka, 2022\n");

	refresh();

	CShop shop;
	ifstream input( "examples/decks/start_hand.csv" );
	shop.load_deck(input, true);
	input.close();

	CDeck deck;
	input.open( "examples/decks/start_hand.csv" );
	deck.load_deck(input, true);
	input.close();

	auto g1 = make_shared<CCardGeneral>("General 1", "This general is the best general in the world", 50, 2, 3, 4, 1, null);
	auto p1 = CPlayerHuman(g1, &init_screen, deck);
	auto g2 = make_shared<CCardGeneral>("General 2", "This general is also the best general in the world", 50, 2, 3, 4, 1, null);
	auto p2 = CPlayerHuman(g2, &init_screen, deck);

	p1.draw_cards(6);
	p1.deploy_card(p1.get_hand().at(0));
	p1.deploy_card(p1.get_hand().at(0));

	p2.draw_cards(6);
	p2.deploy_card(p2.get_hand().at(0));
	p2.deploy_card(p2.get_hand().at(0));

	init_screen.context_bar("Game board showcase");

	init_screen.refresh_board(make_shared<CPlayerHuman>(p1), make_shared<CPlayerHuman>(p2), &shop);
	getch();
cout << "hello" << endl;
	return 0;
}
