//
// Created by simon on 15.4.22.
//

#include "CCardGeneral.h"

#include <ncurses.h>

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

	mvwprintw(card, 9, 3, "%d ️DMG %ls", m_damage, L"🗡");
	mvwprintw(card, 10, 3, "%d HEAL ️%ls", m_protection, L"🏥");
	mvwprintw(card, 11, 3, "%d CASH ️%ls", m_cash, L"🪙");

	wattron(card, COLOR_PAIR(2));
	mvwprintw(card, HEIGHT - 1, 0, "%d / %d Health %ls                  ", m_life, m_life_init, L"🤍");

	wrefresh(card);

	delwin(card);
}

bool CCardGeneral::change_life( int life ) {
	m_life += life;

	return life <= 0;
}

void CCardGeneral::restore() {
	m_life = m_life_init;
}
