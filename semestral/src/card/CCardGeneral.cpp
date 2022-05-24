//
// Created by simon on 15.4.22.
//

#include "CCardGeneral.h"

#include <ncurses.h>
#include <string>
#include <sstream>

using namespace std;

void CCardGeneral::print_card( int y, int x ) {
	const int HEIGHT = 15, WIDTH = 20;

	WINDOW *card;
	card = newwin(HEIGHT, WIDTH, y, x);

	wbkgd(card, COLOR_PAIR(3));

	wattron(card, COLOR_PAIR(2));
	mvwprintw(card, 0, 0, "%*s", - WIDTH, m_name.c_str());

	wattron(card, COLOR_PAIR(3));

	mvwprintw(card, 1, 4, "= General =");
	mvwprintw(card, 3, 0, m_desc.c_str());

	mvwprintw(card, 8, 3, "%d DMG", m_damage);
	mvwprintw(card, 9, 3, "%d HEAL", m_protection);
	mvwprintw(card, 10, 3, "%d CASH", m_cash);

	if (m_special != null) {
		mvwprintw(card, 11, 3, "%s", ability_to_print_str(m_special).c_str());
	}

	if (played()) {
		mvwprintw(card, HEIGHT - 2, 6, " PLAYED ");
	}

	wattron(card, COLOR_PAIR(2));
	mvwprintw(card, HEIGHT - 1, 0, "%d / %d Health                  ", m_life, m_life_init);

	wrefresh(card);

	delwin(card);
}

void CCardGeneral::print_card_wide( int y, int x ) {
	const int HEIGHT = 15, WIDTH = 20;

	WINDOW *card;
	card = newwin(HEIGHT, WIDTH, y, x);

	wbkgd(card, COLOR_PAIR(3));

	wattron(card, COLOR_PAIR(2));
	mvwprintw(card, 0, 0, "%*s", - WIDTH, m_name.c_str());

	wattron(card, COLOR_PAIR(3));

	mvwprintw(card, 1, 4, "= General =");
	mvwprintw(card, 3, 0, m_desc.c_str());

	mvwprintw(card, 8, 3, "%d ️DMG %ls", m_damage, L"🗡");
	mvwprintw(card, 9, 3, "%d HEAL ️%ls", m_protection, L"🏥");
	mvwprintw(card, 10, 3, "%d CASH ️%ls", m_cash, L"🪙");

	if (m_special != null) {
		mvwprintw(card, 11, 3, "%s", ability_to_print_str(m_special).c_str());
	}

	if (played()) {
		mvwprintw(card, HEIGHT - 2, 6, " PLAYED ");
	}

	wattron(card, COLOR_PAIR(2));
	mvwprintw(card, HEIGHT - 1, 0, "%d / %d Health %ls                  ", m_life, m_life_init, L"🤍");

	wrefresh(card);

	delwin(card);
}

bool CCardGeneral::change_life( int life ) {
	m_life += life;

	// max life overflow
	if ( m_life > m_life_init )
		m_life = m_life_init;

	return m_life <= 0;
}

void CCardGeneral::restore() {
	m_life = m_life_init;
	m_played = false;
}

string CCardGeneral::save_card() {
	string data;
	data.append(m_name + ",")
		.append(m_desc + ",")
		.append("g,")
		.append(to_string(m_cost) + ",")
		.append(to_string(m_damage) + ",")
		.append(to_string(m_protection) + ",")
		.append(to_string(m_cash) + ",")
		.append(ability_to_str(m_special) + ",")
		.append(to_string(m_life_init));

	if ( m_life != m_life_init )
		data.append("," + to_string(m_life));

	return data;
}

// Can be deployed (troop), can attack, can protect, has special ability
std::vector<int> CCardGeneral::attributes() {
	vector<int> values;

	values.push_back(0); // general is always "deployed"
	values.push_back(m_damage);
	values.push_back(m_protection);
	values.push_back(m_special != null ? 1 : 0);

	return values;
}

shared_ptr<CCardGeneral> CCardGeneral::load_card(const string& line) {
	istringstream line_stream = istringstream( line );
	string val;
	vector<string> row;

	while(getline(line_stream, val, ','))
		row.push_back(val);

	if ( row.size() <= 8 )
		return nullptr;

	// card values
	string	name = row.at(0),
			desc = row.at(1),
			type = row.at(2),
			special_str = row.at(7);

	int cost = 0, damage = 0, heal = 0, cash = 0, life_init = 0, life = 0;
	try {
		cost = stoi(row.at(3));
		damage = stoi(row.at(4));
		heal = stoi(row.at(5));
		cash = stoi(row.at(6));
		life_init = stoi(row.at(8));
		life = life_init;

		if ( row.size() >= 10 )
			life = stoi(row.at(9));

	} catch (...) {
		// problematic numeric conversion, number out of range of 32bit int
		return nullptr;
	}

	EAbility special = str_to_ability(special_str);

	// create card based on the given type
	if ( type != "g" )
		return nullptr;
	else {
		auto card = make_shared<CCardGeneral>(name, desc, life_init, cost, damage, heal, cash, special);
		card->change_life(life - life_init);
		return card;
	}

}