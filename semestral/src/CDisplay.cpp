//
// Created by simon on 18.4.22.
//

#include "CDisplay.h"
#include "CShop.h"

#include <clocale>
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
	init_pair(1, COLOR_WHITE, COLOR_GREEN);
	// version unsupported by test bench
	// init_pair(1, COLOR_WHITE, COLOR_YELLOW + 8);

	// life
	init_pair(2, COLOR_WHITE, COLOR_RED);

	// general
	init_pair(3, COLOR_RED, COLOR_WHITE);

	// warcry
	init_pair(4, COLOR_YELLOW, COLOR_WHITE);
	init_pair(5, COLOR_WHITE, COLOR_YELLOW);

	// troop
	init_pair(6, COLOR_BLUE, COLOR_WHITE);
	init_pair(7, COLOR_WHITE, COLOR_BLUE);

	// game background (and inversion)
	init_pair(8, COLOR_WHITE, COLOR_BLACK);
	init_pair(9, COLOR_BLACK, COLOR_WHITE);
	// version unsupported by test bench
	// init_pair(8, COLOR_WHITE, COLOR_CYAN + 16);

	// info, context bars
	init_pair(10, COLOR_WHITE, COLOR_MAGENTA);

	getmaxyx(stdscr, m_scr_y, m_scr_x);

	bkgd(COLOR_PAIR(8));
}

CDisplay::~CDisplay() {
	endwin();
}

bool CDisplay::terminal_size_check() const {
	if ( m_scr_y >= 45 && m_scr_x >= 100 )
		return true;

	clear();
	refresh();
	printw("In order to play the game, upscale your terminal to size 100x45 characters and restart the game.\n");
	printw("Your current terminal size is %d x %d\n", m_scr_x, m_scr_y);
	mvprintw(3,0,"Press any key to continue.");

	getch(); // waits for any key press

	return false;
}

int CDisplay::menu() {
	return 0;
}

void CDisplay::info_bar( const string& info ) const {
	attron(COLOR_PAIR(10) | A_BOLD);
	mvprintw(m_scr_y - 1, 0, "%*s", - m_scr_x, info.c_str());
	refresh();
	attroff(COLOR_PAIR(10) | A_BOLD);
}

void CDisplay::context_bar_draw() const {
	attron(COLOR_PAIR(10) | A_BOLD);
	mvprintw(0, 0, "%*s", - m_scr_x, m_context.c_str());
	refresh();
	attroff(COLOR_PAIR(10) | A_BOLD);
}

void CDisplay::context_bar(const string &context) {
	m_context = context;
	context_bar_draw();
}

void CDisplay::refresh_board( std::shared_ptr<CPlayer> first, std::shared_ptr<CPlayer> second, CShop* shop ) {
	// distance of cards next to each other
	const int card_diff = 22;

	// shop
	shop->print_shop(6, 0); // bottom right corner 32, 20

	// generals
	first->get_general()->print_card(23, m_scr_x - 20);
	second->get_general()->print_card(2, m_scr_x - 20);

	// hand of playing player
	int y = 40, x = 0;
	for ( auto card : first->get_hand() ) {
		card->print_card(y, x);
		x += card_diff;
	}

	// table of playing player
	y = 21, x = 22;
	for ( auto card : first->get_table() ) {
		card->print_card(y, x);
		x += card_diff;
	}

	// opponents table
	y = 5, x = 22;
	for ( auto card : first->get_table() ) {
		card->print_card(y, x);
		x += card_diff;
	}

	// cards in drawing pile
	mvprintw(43, m_scr_x - 10, "IN DRAW %d", first->get_draw_count());

	info_bar("Controls of the game: ");

}

std::shared_ptr<CCard> CDisplay::card_selection( const CDeck& deck ) const {
	clear();
	refresh();

	const int y = 15, card_diff = 22;
	int x = 0;
	size_t selected = 0, selected_max = deck.count();

	for ( const auto& card : deck.cards() ) {
		card->print_card(y, x);
		x += card_diff;
	}

	mvprintw(5, 0, "Card selection:" );
	info_bar("Choose card (L/R Arrow), Select card (ENTER)" );
	context_bar_draw(); // information from where card selection was called
	refresh();

	int input = 0;

	while (true) {
		mvprintw(y - 1, (int)selected * card_diff, "Your selection:");
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
