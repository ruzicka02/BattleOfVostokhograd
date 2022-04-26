//
// Created by simon on 15.4.22.
//

#include <ncurses.h>

#include "CCardTroop.h"

void CCardTroop::print_card(int y, int x) {
	const int HEIGHT = 15, WIDTH = 20;

	WINDOW *card;
	card = newwin(HEIGHT, WIDTH, y, x);

	init_pair(1, COLOR_RED, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_RED);

	wbkgd(card, COLOR_PAIR(1));

	wattron(card, COLOR_PAIR(2));
	mvwprintw(card, 0, 0, "%*s", 1 - WIDTH, m_name.c_str());
	mvwprintw(card, 0, WIDTH - 1, "%d", m_cost );
	wattroff(card, COLOR_PAIR(2));
	wattron(card, COLOR_PAIR(1));

	mvwprintw(card, 1, 0, m_desc.c_str());

	mvwprintw(card, 9, 3, "%d ️DMG %ls", m_damage, L"🗡");
	mvwprintw(card, 10, 3, "%d HEAL ️%ls", m_protection, L"🏥");
	mvwprintw(card, 11, 3, "%d CASH ️%ls", m_cash, L"🪙");

	wattroff(card, COLOR_PAIR(1));
	wattron(card, COLOR_PAIR(2));
	mvwprintw(card, HEIGHT - 1, 0, "%d / %d Health %ls                  ", m_life, m_life_init, L"🤍");

	wrefresh(card);

	delwin(card);

}

bool CCardTroop::change_life(int life) {
	m_life += life;

	return life <= 0;
}

void CCardTroop::restore() {
	m_life = m_life_init;
}
