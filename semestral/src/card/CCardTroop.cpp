//
// Created by simon on 15.4.22.
//

#include "CCardTroop.h"

#include <ncurses.h>
#include <string>

using namespace std;

void CCardTroop::print_card(int y, int x) {
	const int HEIGHT = 15, WIDTH = 20;

	WINDOW *card;
	card = newwin(HEIGHT, WIDTH, y, x);

	wbkgd(card, COLOR_PAIR(6));

	wattron(card, COLOR_PAIR(7));
	mvwprintw(card, 0, 0, "%*s", 1 - WIDTH, m_name.c_str());

	wattron(card, COLOR_PAIR(1));
	mvwprintw(card, 0, WIDTH - 2, "%2d", m_cost );

	wattron(card, COLOR_PAIR(6));

	mvwprintw(card, 1, 5, "= Troop =");

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

void CCardTroop::print_card_wide(int y, int x) {
	const int HEIGHT = 15, WIDTH = 20;

	WINDOW *card;
	card = newwin(HEIGHT, WIDTH, y, x);

	wbkgd(card, COLOR_PAIR(6));

	wattron(card, COLOR_PAIR(7));
	mvwprintw(card, 0, 0, "%*s", 1 - WIDTH, m_name.c_str());

	wattron(card, COLOR_PAIR(1));
	mvwprintw(card, 0, WIDTH - 2, "%2d", m_cost );

	wattron(card, COLOR_PAIR(6));

	mvwprintw(card, 1, 5, "= Troop =");
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

bool CCardTroop::change_life(int life) {
	m_life += life;

	// max life overflow
	if ( m_life > m_life_init )
		m_life = m_life_init;

	return m_life <= 0;
}

void CCardTroop::restore() {
	m_life = m_life_init;
	m_played = false;
}

string CCardTroop::save_card() {
	string data;
	data.append(m_name + ",")
		.append(m_desc + ",")
		.append("t,")
		.append(to_string(m_cost) + ",")
		.append(to_string(m_damage) + ",")
		.append(to_string(m_protection) + ",")
		.append(to_string(m_cash) + ",")
		.append(ability_to_str(m_special) + ",")
		.append(to_string(m_life_init));

	return data;
}

// Can be deployed (troop), can attack, can protect, has special ability
std::vector<int> CCardTroop::attributes() {
	vector<int> values;

	values.push_back(1); // can be deployed when in hand, value ignored when already on table
	values.push_back(m_damage);
	values.push_back(m_protection);
	values.push_back(m_special != null ? 1 : 0);

	return values;
}
