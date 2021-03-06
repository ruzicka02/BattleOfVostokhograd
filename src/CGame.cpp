//
// Created by simon on 18.4.22.
//

#include <ncurses.h>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>

#include "CGame.h"

#include "player/CPlayerHuman.h"
#include "player/CPlayerAI.h"
#include "player/CPlayerBogo.h"

using namespace std;

CGame::CGame(bool start) {
	if ( !start )
		return;

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

	// detection of IO issues from reading external files
	if (ok) {
		play(load_switch);	// main game loop
	} else {
		endwin();
		cout << "Problems occurred while reading game definition files and the game terminated." << endl;
		initscr();
	}
}

void CGame::prepare_pve() {
	CDeck deck;
	ifstream input( "examples/decks/start_hand.csv" );
	deck.load_deck(input, true);
	input.close();

	auto g1 = make_shared<CCardGeneral>("Human General", "This general is the best general in the world", 50, 0, 1, 0, 1, null);
	m_first = make_shared<CPlayerHuman>(g1, deck, &m_display, &m_shop);

	// AI randomness
	m_display.context_bar("Select AI difficulty level.");
	int menu_res = m_display.menu({" Smart AI", " Random AI (Bogo)"});

	CDeck deck2;
	input.open( "examples/decks/start_hand.csv" );
	deck2.load_deck(input, true);
	input.close();

	auto g2 = make_shared<CCardGeneral>("General RoboCop", "EX-TER-MI-NA-TE!", 50, 0, 1, 0, 1, null);
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

	auto g1 = make_shared<CCardGeneral>("General Alice", "Using the power of weapons to crush her opponent", 50, 0, 1, 0, 1, null);
	m_first = make_shared<CPlayerHuman>(g1, deck, &m_display, &m_shop);

	CDeck deck2;
	input.open( "examples/decks/start_hand.csv" );
	deck2.load_deck(input, true);
	input.close();

	auto g2 = make_shared<CCardGeneral>("General Bob", "Using the weapons of power to crush his opponent", 50, 0, 1, 0, 1, null);
	m_second = make_shared<CPlayerHuman>(g2, deck2, &m_display, &m_shop);

	m_first->set_opponent(m_second);
	m_second->set_opponent(m_first);
}

void CGame::play(bool no_draw) {
	while (! m_first->lost()) {
		if ( !no_draw ) {
			m_first->draw_cards(5);
			m_first->discard_selection(); // discard up to m_cards_to_discard
		} else {
			no_draw = false;
		}

		if ( m_first->play() ) { // ingame menu; save and exit
			save_game();
			return;
		}

		if ( m_second->lost() )
			break;

		m_display.context_bar(m_second->get_general()->name() + " will be playing now.");
		m_display.pause(0);
		swap(m_first, m_second);
	}

	m_display.context_bar(m_first->get_general()->name() + " has won the game!");
	m_display.info_bar("Press any key to continue.");
	m_display.pause(0);
}

bool CGame::save_game(string name) {
	// unexpected nullptr
	if ( ! m_first || ! m_second )
		return false;

	ofstream file;

	// default name... timestamp
	if ( name == "" ) {
		stringstream name_stream;
		time_t t = time(nullptr);
		tm tm = *localtime(&t);
		name_stream << "examples/saves/" << put_time(&tm, "%Y-%m-%d_%H:%M:%S") << ".csv";

		file.open(name_stream.str());
	} else {
		file.open(name);
	}

	if ( ! file.good() )
		return false;

	m_first->save_player(file);
	file << '\n';
	m_second->save_player(file);
	file << '\n';
	m_shop.save_deck(file);
	file << '\n';

	return file.good();
}

bool CGame::load_game(std::string name) {
	ifstream file(name);
	if ( ! file.good() ) {
		return false;
	}


	string player_type;

	try {
		m_first = CPlayer::load_player(file, &m_display, &m_shop);
		m_second = CPlayer::load_player(file, &m_display, &m_shop);
	} catch (invalid_argument& exc) { // exception called from CPlayer constructor
		return false;
	}

	// nullptr check of players, loading shop deck
	if ( ! m_first || ! m_second || ! m_shop.load_deck(file, false) ) {
		return false;
	}


	m_first->set_opponent(m_second);
	m_second->set_opponent(m_first);

	return file.good();
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
