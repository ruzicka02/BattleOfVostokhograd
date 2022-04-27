//
// Created by simon on 15.4.22.
//

#include "CCardWarcry.h"

#include <ncurses.h>

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

	mvwprintw(card, 9, 3,  "%d ️DMG %ls", m_damage, L"🗡");
	mvwprintw(card, 10, 3, "%d HEAL %ls", m_protection, L"🏥");
	mvwprintw(card, 11, 3, "%d CASH %ls", m_cash, L"🪙");

	wrefresh(card);

	delwin(card);

}
