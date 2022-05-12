//
// Created by simon on 18.4.22.
//

#include <fstream>
#include "CGame.h"

using namespace std;

CGame::CGame() {
	// display, shop... auto created from default constructors

	ifstream shop_cards("examples/decks/shop.csv");
	m_shop.load_deck(shop_cards, true);
}

void CGame::start() {
	int menu_res = m_display.menu();
	bool play_game = true;

	switch (menu_res) {
		case 0:
			prepare_pve();
			break;
		case 1:
			prepare_pvp();
			break;
		case 2:
			load_game("default");
			break;
		case 3:
			play_game = false;
	}

	if (play_game)
		play();
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
	return std::vector<std::string>();
}
