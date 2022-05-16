//
// Created by simon on 18.4.22.
//

#include <ncurses.h>
#include <filesystem>
#include <fstream>

#include "CGame.h"

#include "CPlayerHuman.h"
#include "CPlayerAI.h"
#include "CPlayerBogo.h"

using namespace std;

void CGame::start() {
	int menu_res = m_display.menu({" New PvP game", " New PvE game", " Load game", " Exit"});
	bool exit_switch = false, load_switch = false;

	switch (menu_res) {
		case 0:
			prepare_pvp();
			break;
		case 1:
			prepare_pve();
			break;
		case 2:
			load_switch = true;
			break;
		default: // option exit + all uncovered cases (should not happen)
			exit_switch = true;
	}

	if (exit_switch) {
		return;
	}

	bool ok = true;

	if (load_switch) {
		vector<string> save_games = get_saved_games();
		if ( save_games.empty() )
			return;

		int selection = m_display.menu(save_games);
		ok = load_game(save_games.at(selection));
	} else {
		ifstream shop_cards("examples/decks/standard.csv");
		ok = m_shop.load_deck(shop_cards, true);
		shop_cards.close();
	}

	if (ok) {
		play();	// main game loop
	}
}

void CGame::prepare_pve() {
	CDeck deck;
	ifstream input( "examples/decks/start_hand.csv" );
	deck.load_deck(input, true);
	input.close();

	auto g1 = make_shared<CCardGeneral>("Human General", "This general is the best general in the world", 50, 2, 3, 4, 1, null);
	m_first = make_shared<CPlayerHuman>(g1, deck, &m_display, &m_shop);

	// AI randomness
	m_display.context_bar("Select AI difficulty level.");
	int menu_res = m_display.menu({" Smart AI", " Random AI (Bogo)"});

	CDeck deck2;
	input.open( "examples/decks/start_hand.csv" );
	deck2.load_deck(input, true);
	input.close();

	auto g2 = make_shared<CCardGeneral>("General RoboCop", "This general is also the best general in the world", 50, 2, 3, 4, 1, null);
	if ( menu_res )
		m_second = make_shared<CPlayerBogo>(g2, deck2, &m_display, &m_shop);
	else
		m_second = make_shared<CPlayerAI>(g2, deck2, &m_display, &m_shop);

	m_first->set_opponent(m_second);
	m_second->set_opponent(m_first);
}

void CGame::prepare_pvp() {
	CDeck deck;
	ifstream input( "examples/decks/start_hand.csv" );
	deck.load_deck(input, true);
	input.close();

	auto g1 = make_shared<CCardGeneral>("General Alice", "This general is the best general in the world", 50, 2, 3, 4, 1, null);
	m_first = make_shared<CPlayerHuman>(g1, deck, &m_display, &m_shop);

	CDeck deck2;
	input.open( "examples/decks/start_hand.csv" );
	deck2.load_deck(input, true);
	input.close();

	auto g2 = make_shared<CCardGeneral>("General Bob", "This general is also the best general in the world", 50, 2, 3, 4, 1, null);
	m_second = make_shared<CPlayerHuman>(g2, deck2, &m_display, &m_shop);

	m_first->set_opponent(m_second);
	m_second->set_opponent(m_first);
}

void CGame::play() {
	while (! m_first->lost()) {
		m_first->draw_cards(5);
		m_first->discard_selection(); // discard up to m_cards_to_discard
		m_first->play();

		m_display.context_bar(m_second->get_general()->name() + " will be playing now.");
		getch();
		swap(m_first, m_second);
	}

	swap(m_first, m_second);
	m_display.context_bar(m_first->get_general()->name() + " has won the game!");
	m_display.info_bar("Press any key to continue.");
	getch();
}

bool CGame::save_game(std::string name) {
	return false;
}

bool CGame::load_game(std::string name) {
	return false;
}

std::vector<std::string> CGame::get_saved_games() {
	filesystem::path path("examples/saves/");
	filesystem::directory_iterator iter(path);

	vector<string> results;

	for ( auto& file : iter ) {
		results.push_back(file.path());
	}

	return results;
}
