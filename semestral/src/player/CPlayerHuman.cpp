//
// Created by simon on 18.4.22.
//

#include <string>
#include <sstream>
#include <ncurses.h>


#include "../CDisplay.h"
#include "CPlayerHuman.h"

using namespace std;

bool CPlayerHuman::play() {

	bool cards_available = true;

	while (cards_available) {
		m_display->context_bar("Your turn! Select a card." );
		m_display->refresh_board(shared_from_this(), m_opponent.lock(), m_shop);

		// performs the card play itself (return value means that player wants to exit)
		if ( card_selection_ingame() )
			return true;

		if (m_opponent.lock()->lost())
			return false;

		cards_available = m_hand.count() != 0;
		for ( const auto& i : m_table.cards() )
			if (! i->played()) {
				cards_available = true;
				break;
			}
		if (! get_general()->played()) {
			cards_available = true;
		}
	}

	m_display->context_bar("Last time to go to the shop." );
	getch();
	while (	buy_card() ) {}

	// set all cards as not played
	for ( size_t i = 0; i < m_table.count(); i ++ )
		m_table.cards().at(i)->set_played(false);

	get_general()->set_played(false);
	return false;
}



void CPlayerHuman::discard_selection () {
	if ( m_cards_to_discard >= (int)m_hand.count()) {
		discard_all();
		return;
	}

	for ( int i = 0; i < m_cards_to_discard; i ++ ) {
		stringstream context;
		context << i << '/' << m_cards_to_discard << " discarded";
		m_display->context_bar(context.str());

		discard_card(m_display->card_selection_deckable(m_hand.cards()) );
	}

	m_cards_to_discard = 0;
}

void CPlayerHuman::sacrifice_selection() {
	if ( !m_discard.count() ) {
		m_display->context_bar("No card in discard pile to sacrifice" );
		return;
	}

	m_display->context_bar("Select a card from your discard pile to sacrifice/destroy.");
	m_discard.remove(m_display->card_selection_deckable(m_discard.cards()));
}

std::shared_ptr<CCard> CPlayerHuman::pick_card(const vector<std::shared_ptr<CCard>> &cards, int mode) const {
	return m_display->card_selection(cards);
}

bool CPlayerHuman::card_selection_ingame() {
	// screen is not redrawn, method must be called after refresh_board

	const int hand_count = get_hand().size(), table_count = get_table().size() + 1;

	// get info about played cards
	vector<bool> played;
	for ( const auto& card : get_table() ) {
		played.push_back(card->played());
	}

	played.push_back(get_general()->played());

	const int card_hand_y = 39, card_table_y = 20, card_gen_y = 22, card_diff_x = 22; // constants derived from CDisplay::refresh_board
	int input = 0, selected = 0, selected_max = hand_count;
	bool focus_table = (hand_count == 0), enter_press = false;

	m_display->info_bar("Choose card (Arrow keys), Confirm (Y/ENTER), Go to shop (B), Show hand (SPACE), Menu (Q)" );

	int max_scr_x = getmaxx(stdscr);

	while (true) {
		selected_max = focus_table ? table_count : hand_count;
		mvprintw(1, 0, "Selected: %d/%d", selected + 1, selected_max);
		mvprintw(2, 0, "Focus_table: %d", focus_table);

		// print selection text
		if (!focus_table)
			mvprintw(card_hand_y, selected * card_diff_x, "Your selection:"); // cards in hand
		else if (selected == selected_max - 1)
			mvprintw(card_gen_y, max_scr_x - 20, "Your selection:"); // general
		else
			mvprintw(card_table_y, (selected + 1) * card_diff_x, "Your selection:"); // cards on table

		// wait for input
		input = getch();

		// rewrite the old selection
		if (!focus_table)
			mvprintw(card_hand_y, selected * card_diff_x, "%*c", 20, ' ');
		else if (selected == selected_max - 1)
			mvprintw(card_gen_y, max_scr_x - 20, "%*c", 20, ' ');
		else
			mvprintw(card_table_y, (selected + 1) * card_diff_x, "%*c", 20, ' ');

		if (input == KEY_LEFT && selected > 0)
			selected--;

		if (input == KEY_RIGHT && selected < selected_max - 1)
			selected++;

		if (input == KEY_UP) {
			focus_table = true;
			selected = 0;
		}

		if (input == KEY_DOWN && hand_count != 0) {
			focus_table = false;
			selected = 0;
		}

		// menu; save and exit
		if (input == 'q' || input == 'Q') {
			return true;
		}

		// shop
		if (input == 'b' || input == 'B') {
			m_display->context_bar("Select a card to buy." );
			buy_card();
			return false;
		}

		if (input == ' ') {
			m_display->context_bar("Select a card from your hand to play.");
			play_card(m_display->card_selection_deckable(get_hand()), true);
			return false;
		}

		if (input == '\n' || input == 'y' || input == 'Y')
			enter_press = true;

		if (enter_press && focus_table && played.at(selected)) {
			enter_press = false;
			m_display->context_bar("This card was already played, select another card");
			continue;
		}

		if (enter_press)
			break;

	}

	m_display->context_bar("Card was successfully selected");

	if (!focus_table) {
		play_card(get_hand().at(selected), true);
	}
	else if (selected == selected_max - 1) {
		play_card(get_general(), false);
	}
	else {
		play_card(get_table().at(selected), false);
	}

	return false;
}

bool CPlayerHuman::buy_card() {

	auto available = m_shop->cards();
	bool cash_suff = false;

	// exists card cheaper than how much cash player has
	for ( const auto& card : available ) {
		if ( card->cost() <= m_cash ) {
			cash_suff = true;
			break;
		}
	}

	if ( !cash_suff ) {
		m_display->context_bar("You cannot go to shop with " + to_string(m_cash) + " cash!");
		return false;
	}

	string cash_info = "You have " + to_string(m_cash) + " cash available.";
	m_display->context_bar(cash_info);

	shared_ptr<CCardDeckable> selected;
	while (true) {
		selected = m_display->card_selection_deckable(available);

		if ( selected->cost() <= m_cash ) {
			break;
		}
		m_display->context_bar("This card is too expensive, select another one. " + cash_info);
	}

	m_cash -= selected->cost();
	m_shop->sell_card(selected);
	m_discard.insert(selected);
	m_display->context_bar("Card was bought successfully.");

	m_display->refresh_board(shared_from_this(), m_opponent.lock(), m_shop);
	return true;
}
