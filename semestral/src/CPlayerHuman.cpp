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

	while (true) {



		return;
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
