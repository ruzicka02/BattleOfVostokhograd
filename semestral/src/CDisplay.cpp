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
	init_pair(10, COLOR_BLACK, COLOR_CYAN);
	init_pair(11, COLOR_CYAN, COLOR_BLACK);

	getmaxyx(stdscr, m_scr_y, m_scr_x);

	bkgd(COLOR_PAIR(8));
}

CDisplay::~CDisplay() {
	endwin();
}

void CDisplay::context_bar_draw() const {
	attron(COLOR_PAIR(10) );
	mvprintw(0, 0, "%*s", - m_scr_x, m_context.c_str());
	refresh();
	attroff(COLOR_PAIR(10) );
}

int CDisplay::print_cards( const std::vector<std::shared_ptr<CCard>>& cards, int y, int x, int max ) const {
	const int card_diff = 22; // distance of cards next to each other
	int counter = 0, unprinted = 0;

	for ( const auto& card : cards ) {
		// maximum drawable
		if ( counter >= max )
			unprinted ++;
		else
			card->print_card(y, x);

		x += card_diff;
		counter ++;
	}

	return unprinted;
}

bool CDisplay::terminal_size_check() const {
	if ( m_scr_y >= 45 && m_scr_x >= 120 )
		return true;

	clear();
	refresh();
	printw("In order to play the game, upscale your terminal to size 120x45 characters and restart the game.\n");
	printw("Your current terminal size is %d x %d\n", m_scr_x, m_scr_y);
	mvprintw(3,0,"Press any key to continue.");

	getch(); // waits for any key press

	return false;
}

int CDisplay::menu(vector<string> options) {

	if ( ! terminal_size_check() )
		return 3; // exit

	mvprintw(1, 0, "Simon Ruzicka, 2022\n");

	attron(COLOR_PAIR(11));
	mvprintw(3, 0, "       ____        _   _   _               __  __      __       _        _    _                               _ \n"
				   "      |  _ \\      | | | | | |             / _| \\ \\    / /      | |      | |  | |                             | |\n"
				   "      | |_) | __ _| |_| |_| | ___    ___ | |_   \\ \\  / ___  ___| |_ ___ | | _| |__   ___   __ _ _ __ __ _  __| |\n"
				   "      |  _ < / _` | __| __| |/ _ \\  / _ \\|  _|   \\ \\/ / _ \\/ __| __/ _ \\| |/ | '_ \\ / _ \\ / _` | '__/ _` |/ _` |\n"
				   "      | |_) | (_| | |_| |_| |  __/ | (_) | |      \\  | (_) \\__ | || (_) |   <| | | | (_) | (_| | | | (_| | (_| |\n"
				   "      |____/ \\__,_|\\__|\\__|_|\\___|  \\___/|_|___    \\/ \\___/|___/\\__\\___/|_|\\_|_|_|_|\\___/ \\__, |_|  \\__,_|\\__,_|\n"
				   "                   |__   __| |           / ____|            | | |  __ \\|  __ \\ / ____|     __/ |                \n"
				   "                      | |  | |__   ___  | |     __ _ _ __ __| | | |__) | |__) | |  __     |___/                 \n"
				   "                      | |  | '_ \\ / _ \\ | |    / _` | '__/ _` | |  _  /|  ___/| | |_ |                          \n"
				   "                      | |  | | | |  __/ | |___| (_| | | | (_| | | | \\ \\| |    | |__| |                          \n"
				   "                      |_|  |_| |_|\\___|  \\_____\\__,_|_|  \\__,_| |_|  \\_|_|     \\_____|                          \n");
	attroff(COLOR_PAIR(11));

	int selected = 0, input = 0, y_init = 15;

	while (true) {

		// clean the selection text
		move(y_init, 0);
		clrtobot();

		for ( int i = 0; i < (int)options.size(); i ++ ) {
			if (i == selected) attron(COLOR_PAIR(9));
			mvprintw(y_init + 2 * i, 5, "%-15s", options.at(i).c_str());
			if (i == selected) attroff(COLOR_PAIR(9));
		}

		info_bar("Choose option (Arrow keys), Confirm (Y/ENTER)" );

		// wait for input
		input = getch();

		if ( input == KEY_UP && selected > 0 )
			selected --;

		if ( input == KEY_DOWN && selected < (int)options.size() - 1 )
			selected ++;

		if ( input == 'y' || input == 'Y' || input == '\n' )
			break;


	}

	return selected;
}

void CDisplay::info_bar( const string& info ) const {
	attron(COLOR_PAIR(10) );
	mvprintw(m_scr_y - 1, 0, "%*s", - m_scr_x, info.c_str());
	refresh();
	attroff(COLOR_PAIR(10) );
}

void CDisplay::context_bar(const string &context) {
	m_context = context;
	context_bar_draw();
}

void CDisplay::refresh_board( shared_ptr<CPlayer> first, shared_ptr<CPlayer> second, CShop* shop ) const {
	clear();
	refresh();

	// shop
	shop->print_shop(6, 0); // bottom right corner 37, 20

	// generals
	first->get_general()->print_card(23, m_scr_x - 20);
	second->get_general()->print_card(2, m_scr_x - 20);

	// hand of playing player
	int unprinted = print_cards(first->get_hand(), 40, 0, 5);

	// bottom right HUD
	if ( unprinted > 0 )
		mvprintw(m_scr_y - 5, m_scr_x - 12, "%d MORE CARDS", unprinted);

	mvprintw(m_scr_y - 3, m_scr_x - 8, "CASH %d", first->get_cash());
	mvprintw(m_scr_y - 2, m_scr_x - 11, "CARDS %d/%d", first->get_draw_count(), first->get_discard_count());

	// table of playing player
	unprinted = print_cards(first->get_table(), 21, 22, 3);
	if ( unprinted > 0 )
		mvprintw(22, m_scr_x - 22, "%d MORE CARDS", unprinted);

	// opponents table
	unprinted = print_cards(second->get_table(), 4, 22, 3);
	if ( unprinted > 0 )
		mvprintw(17, m_scr_x - 22, "%d MORE CARDS", unprinted);

	info_bar("Continue (Y/ENTER)");
	context_bar_draw();

}

std::shared_ptr<CCard> CDisplay::card_selection( const std::vector< std::shared_ptr<CCard> >& deck ) const {
	clear();
	refresh();

	const int card_diff_y = 17, card_diff_x = 22, y_init = 12, x_init = 4;
	int y = y_init, x = x_init, selected = 0, selected_max = (int)deck.size();

	for ( const auto& card : deck ) {
		card->print_card(y, x);
		x += card_diff_x;

		if ( x >= 5 * card_diff_x ) {
			x -= 5 * card_diff_x;
			y += card_diff_y;
		}
	}

	mvprintw(1, 0, "Select a card!" );
	info_bar("Choose card (L/R Arrow), Confirm (Y/ENTER)" );
	context_bar_draw(); // information from where card selection was called
	refresh();

	int input = 0;

	while (true) {
		if ( selected < 5 )
			mvprintw(y_init - 1, selected * card_diff_x + x_init, "Your selection:");
		else
			mvprintw(y_init + card_diff_y - 1, (selected - 5) * card_diff_x + x_init, "Your selection:");

		mvprintw(2, 0, "Your choice is card Nr %d / %d max", selected + 1, selected_max );

		// wait for input
		input = getch();

		// clean the selection text
		mvprintw(y_init - 1, 0, "%*s", m_scr_x, "");
		mvprintw(y_init + card_diff_y - 1, 0, "%*s", m_scr_x, "");

		if ( input == KEY_LEFT && selected > 0 )
			selected --;

		if ( input == KEY_RIGHT && selected < selected_max - 1 )
			selected ++;

		if ( input == KEY_UP && selected >= 5 )
			selected -= 5;

		if ( input == KEY_DOWN && selected <= selected_max - 6 )
			selected += 5;

		if ( input == 'y' || input == 'Y' || input == '\n' )
			break;


	}

	clear();
	refresh();

	return deck.at(selected);
}
