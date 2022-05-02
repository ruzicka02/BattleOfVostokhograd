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

void CPlayerHuman::play_card(std::shared_ptr<CCard> card, bool hand) {
	// Can be deployed (troop), can attack, can protect, has special ability
	vector<bool> attr = card->attributes();

	// deploy the card from the hand
	if ( attr[0] && hand ) {
		deploy_card(card);
		m_display->context_bar("Troop has been deployed." );
		m_display->refresh_board(this, m_opponent, m_shop);
		getch();
	}

	// attack
	if ( attr[1] ) {
		auto choice = m_opponent->get_table();
		choice.push_back(m_opponent->get_general());

		m_display->context_bar("Select an opponents card to attack." );
		auto selected = m_display->card_selection(choice);

		card->attack(m_opponent, selected);
	}

	// protect
	if ( attr[2] ) {
		auto choice = get_table();
		choice.push_back(get_general());

		m_display->context_bar("Select a friendly card to protect/heal." );
		auto selected = m_display->card_selection(choice);

		card->protect(this, selected);
	}

	// special
	if ( attr[3] ) {
		EAbility ability = card->special_get();

		if ( ability == steal ) {
			m_display->context_bar("Select an opponents card to steal." );
			auto selected = m_display->card_selection(m_opponent->get_table());

			card->special(m_opponent, selected);
		} else {
			card->special(m_opponent); // using the default nullptr value as a selected card
		}

	}

	// cash
	m_cash += card->cash();

}

void CPlayerHuman::discard_cards (int amount) {

	for ( int i = 0; i < amount; i ++ ) {
		stringstream context;
		context << i << '/' << amount << " discarded";
		m_display->context_bar(context.str());
		m_hand.remove( m_display->card_selection(m_hand.cards()) );
	}


}
