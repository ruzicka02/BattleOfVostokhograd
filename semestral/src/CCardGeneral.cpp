//
// Created by simon on 15.4.22.
//

#include "CCardGeneral.h"

#include <ncurses.h>
#include <string>

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
		mvwprintw(card, 11, 3, "%s", ability_str(m_special).c_str());
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
		mvwprintw(card, 11, 3, "%s", ability_str(m_special).c_str());
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
	data.append(m_name)
		.append(",")
		.append(m_desc)
		.append(",g,")
		.append(to_string(m_life)) // only stores the current life value, set as new maximum
		.append(",")
		.append(to_string(m_cost))
		.append(",")
		.append(to_string(m_damage))
		.append(",")
		.append(to_string(m_protection))
		.append(",")
		.append(to_string(m_cash))
		.append(",");

	if ( m_special == steal)
		data.append("steal");
	else if ( m_special == draw )
		data.append("draw");
	else
		data.append("null");

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