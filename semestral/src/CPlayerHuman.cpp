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

	vector<bool> played;
	for ( size_t i = 0; i <= m_table.count(); i ++ )
		played.emplace_back(false);

	bool cards_available;

	do {
		m_display->refresh_board(this, m_opponent, m_shop);
		m_display->card_selection_ingame(this, played);

		cards_available = m_hand.count() != 0;
		for ( size_t i = 0; i <= played.size(); i ++ )
			if (!played.at(i)) {
				cards_available = true;
				break;
			}

	} while (cards_available);
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
