//
// Created by simon on 18.4.22.
//

#include <filesystem>
#include <fstream>
#include "CGame.h"

using namespace std;

void CGame::start() {
	int menu_res = m_display.menu({" New PvP game", " New PvE game", " Load game", " Exit"});
	bool play_switch = true, load_switch = false;

	switch (menu_res) {
		case 0:
			prepare_pve();
			break;
		case 1:
			prepare_pvp();
			break;
		case 2:
			load_switch = true;
			break;
		default: // option exit + all uncovered cases (should not happen)
			play_switch = false;
	}

	if (load_switch) {
		vector<string> save_games = get_saved_games();
		int selection = m_display.menu(save_games);
		load_game(save_games.at(selection));
	}

	if (play_switch) {
		ifstream shop_cards("examples/decks/shop.csv");
		m_shop.load_deck(shop_cards, true);

		play();
	}
}

void CGame::prepare_pve() {

}

void CGame::prepare_pvp() {

}

void CGame::play() {

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
