//
// Created by simon on 5.5.22.
//

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

void card_selection_t () {
	CDisplay screen;

	screen.context_bar("Before card selection:" );
	screen.info_bar("Press any key to continue." );

	CDeck deck;
	ifstream input( "examples/decks/start_hand.csv" );
	deck.load_deck(input);
	input.close();

	deck.pop_top()->print_card(10, 4);
	deck.pop_top()->print_card(10, 26);
	deck.pop_top()->print_card(10, 48);

	refresh();
	getch();

	CDeck selected;
	std::shared_ptr<CCard> choice;

	screen.context_bar("0/3 selected");
	choice = screen.card_selection(deck.cards());
	selected.insert( choice );
	deck.remove( choice );

	screen.context_bar("1/3 selected");
	choice = screen.card_selection(deck.cards());
	selected.insert( choice );
	deck.remove( choice );

	screen.context_bar("2/3 selected");
	choice = screen.card_selection(deck.cards());
	selected.insert( choice );
	deck.remove( choice );

	screen.context_bar("Your selected cards:" );
	screen.info_bar("Press any key to continue." );

	const int y = 10, card_diff = 22;
	int x = 4;

	for ( auto card : selected.cards() ) {
		card->print_card(y, x);
		x += card_diff;
	}

	getch();

	clear();
}

void CDeck_t () {
	CDisplay screen;
	screen.context_bar("CDeck test");

	CDeck deck;
	ifstream input( "examples/decks/start_hand.csv" );
	deck.load_deck(input);
	input.close();

	int pos = 25;
	for ( auto card : deck.cards() ) {
		card->print_card(30, pos);
		pos += 25;

		if ( pos >= 100 )
			break;
	}

//	CShop showcase
	CShop shop;

	input.open( "examples/decks/start_hand.csv" );
	shop.load_deck(input, true);
	input.close();
	shop.print_shop(5, 0);

	getch();

	clear();
	endwin();

//	cout << "Total cards in deck: " << deck.count() << endl;

	input.open( "examples/decks/start_hand.csv" );
	stringstream s_file;
	s_file << input.rdbuf();
	input.close();

	ostringstream s_processed;
	deck.save_deck(s_processed);

//	cout << s_processed.str() << endl;
//	cout << s_file.str() << endl;

	assert(s_processed.str() == s_file.str());

//	shop.save_deck(cout);
}

void CDisplay_t () {
	CDisplay screen;
	screen.context_bar("CDisplay test");
	if ( ! screen.terminal_size_check() )
		return;

	if ( can_change_color() ) printw("Can change color\n");
	if ( has_colors() ) printw("Has colors\n");
	printw("Normal non-wchar cards\n");

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

	mvprintw(22, 0, "Cards utilizing wchar capabilities\n");

	card_t.print_card_wide(25, 0);
	card_w.print_card_wide(25, 25);
	card_g.print_card_wide(25, 50);

	card_g.change_life(-8);
	card_g.print_card(25, 75);

	getch();

	clear();
}

void refresh_board_t () {
	CDisplay screen;

	CShop shop;
	ifstream input( "examples/decks/start_hand.csv" );
	shop.load_deck(input, true);
	input.close();

	CDeck deck;
	input.open( "examples/decks/start_hand.csv" );
	deck.load_deck(input, true);
	input.close();

	auto g1 = make_shared<CCardGeneral>("General 1", "This general is the best general in the world", 50, 2, 3, 4, 1, null);
	auto p1 = CPlayerHuman(g1, deck, &screen, &shop);

	deck.shuffle_cards();
	auto g2 = make_shared<CCardGeneral>("General 2", "This general is also the best general in the world", 50, 2, 3, 4, 1, null);
	auto p2 = CPlayerHuman(g2, deck, &screen, &shop);

	p1.draw_cards(6);

	p2.draw_cards(7);
	p2.deploy_card(p2.get_hand().at(0));
	p2.deploy_card(p2.get_hand().at(0));
	p2.deploy_card(p2.get_hand().at(0));

	screen.context_bar("Game board showcase - press any key to deploy a card");

	screen.refresh_board(&p1, &p2, &shop);
	getch();
	p1.deploy_card(p1.get_hand().at(2));
	screen.refresh_board(&p1, &p2, &shop);
	getch();
	p1.deploy_card(p1.get_hand().at(1));
	screen.refresh_board(&p1, &p2, &shop);
	getch();
	p1.deploy_card(p1.get_hand().at(1));
	screen.refresh_board(&p1, &p2, &shop);
	getch();
	p1.deploy_card(p1.get_hand().at(0));

	screen.context_bar("Press any key to end the test");
	screen.refresh_board(&p1, &p2, &shop);
	getch();

	clear();
}

void play_card_t () {
	CDisplay screen;

	CShop shop;
	ifstream input( "examples/decks/start_hand.csv" );
	shop.load_deck(input, true);
	input.close();

	CDeck deck;
	deck.insert(make_shared<CCardTroop>("Stealing troop", "Lorem ipsum dolor sit amet", 1, 2, 0, 0, 1, steal));
	deck.insert(make_shared<CCardTroop>("Sample troop", "Lorem ipsum dolor sit amet", 1, 2, 3, 4, 5, null));
	deck.insert(make_shared<CCardWarcry>("Sample warcry", "Lorem ipsum dolor sit amet", 1, 2, 3, 4, null));

	CDeck deck2;
	deck2.insert(make_shared<CCardTroop>("Training dummy", "Lorem ipsum dolor sit amet", 8, 2, 0, 0, 1, steal));
	deck2.insert(make_shared<CCardTroop>("Training dummy", "Lorem ipsum dolor sit amet", 8, 2, 0, 0, 1, null));
	deck2.insert(make_shared<CCardTroop>("Training dummy", "Lorem ipsum dolor sit amet", 8, 2, 0, 0, 1, null));


	auto g1 = make_shared<CCardGeneral>("General 1", "This general is the best general in the world", 50, 2, 3, 4, 1, null);
	g1->change_life(-10);
	auto p1 = CPlayerHuman(g1, deck, &screen, &shop);

	auto g2 = make_shared<CCardGeneral>("General 2", "This general is also the best general in the world", 50, 2, 3, 4, 1, null);
	auto p2 = CPlayerHuman(g2, deck2, &screen, &shop);

	p1.set_opponent(&p2);
	p2.set_opponent(&p1);

	p1.draw_cards(3);

	p2.draw_cards(3);
	p2.deploy_card(p2.get_hand().at(0));
	p2.deploy_card(p2.get_hand().at(0));
	p2.deploy_card(p2.get_hand().at(0));

	screen.refresh_board(&p1, &p2, &shop);

	p1.play();

//	while (! p1.get_hand().empty()) {
//		screen.context_bar("Card playing showcase - press any key to play a card");
//		getch();
//		p1.play_card(p1.get_hand().at(0), true);
//		screen.refresh_board(&p1, &p2, &shop);
//	}

	screen.context_bar("Press any key to end the test");
	screen.refresh_board(&p1, &p2, &shop);
	getch();

	clear();
}