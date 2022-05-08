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

	getmaxyx(stdscr, m_scr_y, m_scr_x);

	bkgd(COLOR_PAIR(8));
}

CDisplay::~CDisplay() {
	endwin();
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

int CDisplay::menu() {
	return 0;
}

void CDisplay::info_bar( const string& info ) const {
	attron(COLOR_PAIR(10) );
	mvprintw(m_scr_y - 1, 0, "%*s", - m_scr_x, info.c_str());
	refresh();
	attroff(COLOR_PAIR(10) );
}

void CDisplay::context_bar_draw() const {
	attron(COLOR_PAIR(10) );
	mvprintw(0, 0, "%*s", - m_scr_x, m_context.c_str());
	refresh();
	attroff(COLOR_PAIR(10) );
}

void CDisplay::context_bar(const string &context) {
	m_context = context;
	context_bar_draw();
}

void CDisplay::refresh_board( CPlayer* first, CPlayer* second, CShop* shop ) const {
	clear();
	refresh();

	// distance of cards next to each other
	const int card_diff = 22;

	// shop
	shop->print_shop(6, 0); // bottom right corner 37, 20

	// generals
	first->get_general()->print_card(23, m_scr_x - 20);
	second->get_general()->print_card(2, m_scr_x - 20);

	// hand of playing player
	int y = 40, x = 0, unprinted = 0;
	for ( auto card : first->get_hand() ) {
		// maximum drawable
		if ( x >= 5 * card_diff )
			unprinted ++;
		else
			card->print_card(y, x);

		x += card_diff;
	}

	// bottom right HUD
	if ( unprinted > 0 )
		mvprintw(m_scr_y - 5, m_scr_x - 12, "%d MORE CARDS", unprinted);

	mvprintw(m_scr_y - 3, m_scr_x - 7, "CASH %d", first->get_cash());
	mvprintw(m_scr_y - 2, m_scr_x - 10, "DRAWING %d", first->get_draw_count());

	// table of playing player
	y = 21, x = 22;
	unprinted = 0;
	for ( auto card : first->get_table() ) {
		// maximum drawable
		if ( x >= 3 * card_diff + 22 )
			unprinted ++;
		else
			card->print_card(y, x);

		x += card_diff;
	}
	if ( unprinted > 0 )
		mvprintw(22, m_scr_x - 22, "%d MORE CARDS", unprinted);

	// opponents table
	y = 4, x = 22;
	unprinted = 0;
	for ( auto card : second->get_table() ) {
		// maximum drawable
		if ( x >= 3 * card_diff + 22 )
			unprinted ++;
		else
			card->print_card(y, x);

		x += card_diff;
	}
	if ( unprinted > 0 )
		mvprintw(17, m_scr_x - 22, "%d MORE CARDS", unprinted);

	info_bar("Continue (ENTER)");
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
	info_bar("Choose card (L/R Arrow), Confirm (ENTER)" );
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

		if ( input == 'y' || input == '\n' )
			break;


	}

	clear();
	refresh();

	return deck.at(selected);
}

std::shared_ptr<CCard> CDisplay::card_selection_ingame(CPlayer * player, vector<bool>& played) const {
	// screen is not redrawn, method must be called after refresh_board

	const int hand_count = player->get_hand().size(), table_count = player->get_table().size() + 1;

	const int card_hand_y = 39, card_table_y = 22, card_gen_y = 20, card_diff_x = 22; // constants derived from CDisplay::refresh_board
	int input = 0, selected = 0, selected_max = hand_count;
	bool focus_table = false;

	info_bar("Choose card (Arrow keys), Confirm (ENTER), Go to shop (B)" );



//		m_display->card_selection(playable);
	while (true) {

		// print selection text
		if (!focus_table)
			mvprintw(card_hand_y, selected * card_diff_x, "Your selection:"); // cards in hand
		else if (selected == selected_max)
			mvprintw(card_gen_y, m_scr_x - 20, "Your selection:"); // general
		else
			mvprintw(card_table_y, (selected + 1) * card_diff_x, "Your selection:"); // cards on table

		// wait for input
		input = getch();

		// rewrite the old selection
		if (!focus_table)
			mvprintw(card_hand_y, selected * card_diff_x, "%*c", 20, ' ');
		else if (selected == selected_max)
			mvprintw(card_gen_y, m_scr_x - 20, "%*c", 20, ' ');
		else
			mvprintw(card_table_y, (selected + 1) * card_diff_x, "%*c", 20, ' ');

		if (input == KEY_LEFT && selected > 0)
			selected--;

		if (input == KEY_RIGHT && selected < selected_max - 1)
			selected++;

		if (input == KEY_UP && table_count != 0) {
			focus_table = true;
			selected = 0;
			selected_max = table_count;
		}

		if (input == KEY_DOWN && hand_count != 0) {
			focus_table = false;
			selected = 0;
			selected_max = hand_count;
		}

		if (input == 'y' || input == '\n')
			break;

	}

	// todo... make sure every card is played max once
	// return value
	if (!focus_table)
		return player->get_hand().at(selected);
	else if (selected == selected_max) {
		played.at(0) = true;
		return player->get_general();
	}
	else {
		played.at(selected + 1) = true;
		return player->get_table().at(selected);
	}

}
