//
// Created by simon on 18.4.22.
//

#include <string>
#include <sstream>
#include <ncurses.h>


#include "CDisplay.h"
#include "CPlayerHuman.h"

using namespace std;

void CPlayerHuman::play() {

	bool cards_available = true;

	while (cards_available) {
		m_display->context_bar("Your turn! Select a card." );
		m_display->refresh_board(this, m_opponent, m_shop);
		m_display->card_selection_ingame(this);

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
}



void CPlayerHuman::discard_selection (int amount) {

	for ( int i = 0; i < amount; i ++ ) {
		stringstream context;
		context << i << '/' << amount << " discarded";
		m_display->context_bar(context.str());
		m_hand.remove( m_display->card_selection(m_hand.cards()) );
	}

}

std::shared_ptr<CCard> CPlayerHuman::pick_card(const vector<std::shared_ptr<CCard>> &cards, int mode) const {
	return m_display->card_selection(cards);
}

bool CPlayerHuman::buy_card() {

	auto available = m_shop->cards();
	bool cash_suff = false;

	for ( auto card : available ) {
		if ( card->cost() <= m_cash ) {
			cash_suff = true;
			break;
		}
	}

	if ( !cash_suff ) {
		m_display->context_bar("You cannot go to shop with " + to_string(m_cash) + " cash!");
		return false;
	}

	shared_ptr<CCard> selected;
	while (true) {
		m_display->context_bar("You have " + to_string(m_cash) + " cash available.");
		selected = m_display->card_selection(available);

		if ( selected->cost() <= m_cash ) {
			break;
		}
		m_display->context_bar("This card is not expensive, only you have too little money, select another one.");
	}

	m_cash -= selected->cost();
	m_shop->sell_card(selected);
	m_discard.insert(selected);

	m_display->refresh_board(this, m_opponent, m_shop);
	return true;
}
