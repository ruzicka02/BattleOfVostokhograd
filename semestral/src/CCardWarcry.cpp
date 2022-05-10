//
// Created by simon on 15.4.22.
//

#include "CCardWarcry.h"

#include <ncurses.h>
#include <string>

using namespace std;

void CCardWarcry::print_card(int y, int x) {
	const int HEIGHT = 15, WIDTH = 20;

	WINDOW *card;
	card = newwin(HEIGHT, WIDTH, y, x);

	wbkgd(card, COLOR_PAIR(4));

	wattron(card, COLOR_PAIR(5));
	mvwprintw(card, 0, 0, "%*s", 1 - WIDTH, m_name.c_str());

	wattron(card, COLOR_PAIR(1));
	mvwprintw(card, 0, WIDTH - 2, "%2d", m_cost );

	wattron(card, COLOR_PAIR(4));

	mvwprintw(card, 1, 5, "= Warcry =");
	mvwprintw(card, 3, 0, m_desc.c_str());

	mvwprintw(card, 8, 3, "%d DMG", m_damage);
	mvwprintw(card, 9, 3, "%d HEAL", m_protection);
	mvwprintw(card, 10, 3, "%d CASH", m_cash);

	if (m_special != null) {
		mvwprintw(card, 11, 3, "%s", ability_str(m_special).c_str());
	}

	wrefresh(card);

	delwin(card);

}

void CCardWarcry::print_card_wide(int y, int x) {
	const int HEIGHT = 15, WIDTH = 20;

	WINDOW *card;
	card = newwin(HEIGHT, WIDTH, y, x);

	wbkgd(card, COLOR_PAIR(4));

	wattron(card, COLOR_PAIR(5));
	mvwprintw(card, 0, 0, "%*s", 1 - WIDTH, m_name.c_str());

	wattron(card, COLOR_PAIR(1));
	mvwprintw(card, 0, WIDTH - 2, "%2d", m_cost );

	wattron(card, COLOR_PAIR(4));

	mvwprintw(card, 1, 5, "= Warcry =");
	mvwprintw(card, 3, 0, m_desc.c_str());

	mvwprintw(card, 8, 3, "%d ️DMG %ls", m_damage, L"🗡");
	mvwprintw(card, 9, 3, "%d HEAL ️%ls", m_protection, L"🏥");
	mvwprintw(card, 10, 3, "%d CASH ️%ls", m_cash, L"🪙");

	if (m_special != null) {
		mvwprintw(card, 11, 3, "%s", ability_str(m_special).c_str());
	}

	wrefresh(card);

	delwin(card);

}

string CCardWarcry::save_card() {
	string data;
	data.append(m_name)
			.append(",")
			.append(m_desc)
			.append(",w,0,")
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
std::vector<int> CCardWarcry::attributes() {
	vector<int> values;

	values.push_back(0); // is a warcry, cannot be deployed
	values.push_back(m_damage);
	values.push_back(m_protection);
	values.push_back(m_special != null ? 1 : 0);

	return values;
}
