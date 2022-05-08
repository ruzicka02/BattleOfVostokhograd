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
	m_display->context_bar("Your turn!" );

//	vector<bool> in_hand;
//	auto playable = get_hand();
//	for ( auto card : get_hand() ) {
//		in_hand.emplace_back(true);
//	}
//
//
//	for ( auto card : get_table() ) {
//		playable.emplace_back(card);
//		in_hand.emplace_back(false);
//	}

	int input = 0;
	bool focus_table = false;

	vector<bool> played;
	for ( int i = 0; i <= m_table.count(); i ++ )
		played.emplace_back(false);

	bool cards_available = true;

	while (cards_available) {
		m_display->refresh_board(this, m_opponent, m_shop);
		m_display->info_bar("Choose card (Arrow keys), Confirm (ENTER), Go to shop (B)" );

//		m_display->card_selection(playable);

		// todo... select card from player's table

		cards_available = m_hand.count() != 0;
		for ( auto x : played )
			if (!x) {
				cards_available = true;
				break;
			}
	}
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
