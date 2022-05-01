//
// Created by simon on 18.4.22.
//

#include "CDisplay.h"

#include <locale.h>
#include <ncurses.h>

using namespace std;

CDisplay::CDisplay() {
	setlocale(LC_ALL, "");
	initscr();
	start_color();

	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	curs_set(0);

	// gold
	init_pair(1, COLOR_WHITE, COLOR_YELLOW);
	// version unsupported by test bench
	// init_pair(1, COLOR_WHITE, COLOR_YELLOW + 8);

	// life
	init_pair(2, COLOR_WHITE, COLOR_RED);

	// general
	init_pair(3, COLOR_RED, COLOR_WHITE);

	// warcry
	init_pair(4, COLOR_GREEN, COLOR_WHITE);
	init_pair(5, COLOR_WHITE, COLOR_GREEN);

	// troop
	init_pair(6, COLOR_BLUE, COLOR_WHITE);
	init_pair(7, COLOR_WHITE, COLOR_BLUE);

	// game background (and inversion)
	init_pair(8, COLOR_WHITE, COLOR_BLACK);
	init_pair(9, COLOR_BLACK, COLOR_WHITE);
	// version unsupported by test bench
	// init_pair(8, COLOR_WHITE, COLOR_CYAN + 16);

	getmaxyx(stdscr, m_scr_y, m_scr_x);

	bkgd(COLOR_PAIR(8));
}

CDisplay::~CDisplay() {
	endwin();
}

int CDisplay::menu() {
	return 0;
}

void CDisplay::info_bar( const string& info ) {
	attron(COLOR_PAIR(9));
	mvprintw(m_scr_y - 1, 0, "%*s", - m_scr_x, info.c_str());
	refresh();
	attroff(COLOR_PAIR(9));
}

void CDisplay::context_bar_draw() {
	attron(COLOR_PAIR(9));
	mvprintw(0, 0, "%*s", - m_scr_x, m_context.c_str());
	refresh();
	attroff(COLOR_PAIR(9));
}

void CDisplay::context_bar(const string &context) {
	m_context = context;
	context_bar_draw();
}

void CDisplay::refresh_board( std::shared_ptr<CPlayer> first, std::shared_ptr<CPlayer> second ) {

}

std::shared_ptr<CCard> CDisplay::card_selection( const CDeck& deck ) {
	clear();
	refresh();
//	endwin();
//	initscr();


	const int y = 15, card_diff = 22;
	int x = 0, selected = 0, selected_max = deck.cards().size();

	for ( auto card : deck.cards() ) {
		card->print_card(y, x);
		x += card_diff;
	}

	mvprintw(5, 0, "Card selection:" );
	info_bar("Choose card (L/R Arrow), Select card (ENTER)" );
	context_bar_draw();
	refresh();

	int input = 0;
	// halfdelay(1);

	while (true) {
		mvprintw(y - 1, selected * card_diff, "Your selection:");
		mvprintw(10, 0, "Selected nr: %d", selected );
		input = getch();
		mvprintw(y - 1, 0, "%*s", m_scr_x, "");

		if ( input == KEY_LEFT && selected > 0 )
			selected --;

		if ( input == KEY_RIGHT && selected < selected_max - 1 )
			selected ++;

		if ( input == 'y' || input == '\n' )
			break;


	}

	clear();
	refresh();

	return deck.cards().at(selected);
}