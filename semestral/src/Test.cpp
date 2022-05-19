//
// Created by simon on 5.5.22.
//

#include "Test.h"

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

	for ( const auto& card : selected.cards() ) {
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
	for ( const auto& card : deck.cards() ) {
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

	input.open( "examples/decks/start_hand.csv" );
	stringstream s_file;
	s_file << input.rdbuf();
	input.close();

	ostringstream s_processed;
	deck.save_deck(s_processed);

	assert(s_processed.str() == s_file.str());
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
	card_g.set_played(true);
	card_g.print_card(5, 75);

	mvprintw(22, 0, "Cards utilizing wchar capabilities\n");

	card_t.print_card_wide(25, 0);
	card_w.print_card_wide(25, 25);
	card_g.print_card_wide(25, 75);

	card_g.change_life(+8);
	card_g.set_played(false);
	card_g.print_card_wide(25, 50);

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
	auto p1 = make_shared<CPlayerHuman>(g1, deck, &screen, &shop);

	deck.shuffle_cards();
	auto g2 = make_shared<CCardGeneral>("General 2", "This general is also the best general in the world", 50, 2, 3, 4, 1, null);
	auto p2 = make_shared<CPlayerHuman>(g2, deck, &screen, &shop);

	p1->draw_cards(6);

	p2->draw_cards(7);
	p2->deploy_card(p2->get_hand().at(0));
	p2->deploy_card(p2->get_hand().at(0));
	p2->deploy_card(p2->get_hand().at(0));

	screen.context_bar("Game board showcase - press any key to deploy a card");

	screen.refresh_board(p1, p2, &shop);
	getch();
	p1->deploy_card(p1->get_hand().at(2));
	screen.refresh_board(p1, p2, &shop);
	getch();
	p1->deploy_card(p1->get_hand().at(1));
	screen.refresh_board(p1, p2, &shop);
	getch();
	p1->deploy_card(p1->get_hand().at(1));
	screen.refresh_board(p1, p2, &shop);
	getch();
	p1->deploy_card(p1->get_hand().at(0));

	screen.context_bar("Press any key to end the test");
	screen.refresh_board(p1, p2, &shop);
	getch();

	clear();
}

void play_card_t () {
	CDisplay screen;

	CShop shop;
	ifstream input( "examples/decks/shop.csv" );
	shop.load_deck(input, true);
	input.close();

	CDeck deck;
	deck.insert(make_shared<CCardTroop>("Stealing troop", "Lorem ipsum dolor sit amet", 1, 2, 0, 0, 1, steal));
	deck.insert(make_shared<CCardTroop>("Sample troop", "Lorem ipsum dolor sit amet", 1, 2, 3, 4, 5, null));
	deck.insert(make_shared<CCardWarcry>("Sample warcry", "Lorem ipsum dolor sit amet", 1, 2, 3, 4, null));
	deck.insert(make_shared<CCardWarcry>("Sample warcry", "Lorem ipsum dolor sit amet", 1, 2, 3, 4, draw));
	deck.insert(make_shared<CCardWarcry>("Sample warcry", "Lorem ipsum dolor sit amet", 1, 2, 3, 4, discard));
	deck.insert(make_shared<CCardWarcry>("Sample warcry", "Lorem ipsum dolor sit amet", 1, 2, 3, 4, sacrifice));

	CDeck deck2;
	deck2.insert(make_shared<CCardTroop>("Training dummy", "Lorem ipsum dolor sit amet", 8, 2, 0, 0, 1, null));
	deck2.insert(make_shared<CCardTroop>("Training dummy", "Lorem ipsum dolor sit amet", 8, 2, 0, 0, 1, null));
	deck2.insert(make_shared<CCardTroop>("Training dummy", "Lorem ipsum dolor sit amet", 8, 2, 0, 0, 1, null));
	deck2.insert(make_shared<CCardTroop>("Training dummy", "Lorem ipsum dolor sit amet", 8, 2, 0, 0, 1, null));


	auto g1 = make_shared<CCardGeneral>("General 1", "This general is the best general in the world", 50, 2, 3, 4, 1, null);
	g1->change_life(-10);
	auto p1 = make_shared<CPlayerHuman>(g1, deck, &screen, &shop);

	auto g2 = make_shared<CCardGeneral>("General 2", "This general is also the best general in the world", 50, 2, 3, 4, 1, null);
	auto p2 = make_shared<CPlayerHuman>(g2, deck2, &screen, &shop);

	p1->set_opponent(p2);
	p2->set_opponent(p1);

	p1->draw_cards(5);

	p2->draw_cards(3);
	p2->deploy_card(p2->get_hand().at(0));
	p2->deploy_card(p2->get_hand().at(0));
	p2->deploy_card(p2->get_hand().at(0));

	screen.refresh_board(p1, p2, &shop);

	p1->play();

	screen.context_bar("Press any key to end the test");
	screen.refresh_board(p1, p2, &shop);
	getch();

	clear();
}