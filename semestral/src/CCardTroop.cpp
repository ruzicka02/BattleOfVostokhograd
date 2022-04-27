//
// Created by simon on 15.4.22.
//

#include "CCardTroop.h"

#include <ncurses.h>

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

	mvwprintw(card, 9, 3, "%d ️DMG %ls", m_damage, L"🗡");
	mvwprintw(card, 10, 3, "%d HEAL ️%ls", m_protection, L"🏥");
	mvwprintw(card, 11, 3, "%d CASH ️%ls", m_cash, L"🪙");

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
