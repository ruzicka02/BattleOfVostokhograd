//
// Created by simon on 17.4.22.
//

#include <ncurses.h>

#include "CPlayer.h"
#include "CDisplay.h"

using namespace std;

void CPlayer::draw_cards(size_t amount) {
	if (amount > m_drawing.count() + m_discard.count())
		amount = m_drawing.count() + m_discard.count();

	for ( size_t i = 0; i < amount; i++ ) {
		if (! m_drawing.count()) { // refill the drawing pile from discard pile
			m_discard.shuffle_cards();
			while ( m_discard.count() ) {
				m_drawing.insert(m_discard.pop_top());
			}
		}

		shared_ptr<CCard> card = m_drawing.pop_top();
		m_hand.insert(card);
	}

}

void CPlayer::discard_all() {
	while ( m_hand.count() )
		m_discard.insert(m_hand.pop_top());
}

void CPlayer::discard_card(std::shared_ptr <CCard> target) {
	m_hand.remove(target);
	m_discard.insert(target);
}


void CPlayer::kill_card(std::shared_ptr <CCard> target) {
	// do nothing in case general is dead (game will terminate soon)
	if ( target == m_general )
		return;

	target->restore();
	m_table.remove(target);
	m_discard.insert(target);
}

void CPlayer::destroy_card(std::shared_ptr <CCard> target) {
	m_table.remove(target);
}

void CPlayer::steal_card(std::shared_ptr <CCard> target) {
	if ( ! m_opponent.lock() ) // opponent not set/deallocated
		return;

	m_opponent.lock()->destroy_card(target);

	m_table.insert(target);
	target->set_played(true);
}

void CPlayer::deploy_card(std::shared_ptr<CCard> target) {
	m_hand.remove(target);
	m_table.insert(target);
}

void CPlayer::play_card(std::shared_ptr<CCard> card, bool hand) {
	// automatically goes through the phases
	halfdelay(10);

	// Can be deployed (troop), can attack, can protect, has special ability
	vector<int> attr = card->attributes();

	// deploy the card from the hand
	if ( attr[0] && hand ) {
		deploy_card(card);
		m_display->context_bar("Troop has been deployed." );
		m_display->refresh_board(shared_from_this(), m_opponent.lock(), m_shop);
		getch();
	}

	// must be warcry in hand... discard the card from hand
	if ( ! attr[0] && hand ) {
		discard_card(card);
	}

	// attack
	if ( attr[1] ) {
		auto choice = m_opponent.lock()->get_table();
		choice.push_back(m_opponent.lock()->get_general());

		m_display->context_bar("Select an opponents card to attack. DMG = " + to_string(attr[1]) );
		auto selected = pick_card(choice, 1);

		card->attack(m_opponent.lock(), selected);
	}

	// protect
	if ( attr[2] ) {
		auto choice = get_table();
		choice.push_back(get_general());

		m_display->context_bar("Select a friendly card to protect/heal. HEAL = " + to_string(attr[2]) );
		auto selected = pick_card(choice, 2);

		card->protect(shared_from_this(), selected);
	}

	// special
	if ( attr[3] ) {
		EAbility ability = card->special_get();

		if ( ability == steal ) {
			m_display->context_bar("Select an opponents card to steal." );
			auto selected = pick_card(m_opponent.lock()->get_table(), 3);

			card->special(shared_from_this(), selected);
		} else {
			m_display->context_bar(ability_to_print_str(ability));
			card->special(shared_from_this()); // using the default nullptr value as a selected card
		}

		m_display->refresh_board(shared_from_this(), m_opponent.lock(), m_shop);
		getch();
	}

	// cash
	if ( card->cash() > 0 ) {
		m_cash += card->cash();
		m_display->context_bar("Cash added to your stockpile.");
		m_display->refresh_board(shared_from_this(), m_opponent.lock(), m_shop);
		getch();
	}

	card->set_played(true);

	nocbreak(); // turn off half delay mode
	cbreak();
}