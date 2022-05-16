//
// Created by simon on 5.5.22.
//

#include <random>
#include <ncurses.h>

#include "CPlayerBogo.h"
#include "CDisplay.h"

using namespace std;

void CPlayerBogo::play() {

	// play all cards in hand in random order
	m_hand.shuffle_cards();
	while(m_hand.count()) {
		m_display->context_bar("Opponent is currently playing." );
		halfdelay(10);
		getch();

		play_card(m_hand.seek_top(), true);
		m_display->refresh_board(shared_from_this(), m_opponent.lock(), m_shop);
	}

	// play all cards on table in random order
	m_table.shuffle_cards();
	for ( shared_ptr<CCard> card : m_table.cards()) {
		if ( card->played() )
			continue;

		m_display->context_bar("Opponent is currently playing." );
		halfdelay(10);
		getch();

		play_card(card, false);
		m_display->refresh_board(shared_from_this(), m_opponent.lock(), m_shop);
	}

	play_card(m_general, false);

	m_display->context_bar("Opponent is currently buying new cards." );
	while (	buy_card() ) {
		halfdelay(10);
		getch();
	}

	// set all cards as not played
	for ( size_t i = 0; i < m_table.count(); i ++ )
		m_table.cards().at(i)->set_played(false);

	get_general()->set_played(false);

	nocbreak(); // turn off half delay mode
	cbreak();
}

std::shared_ptr<CCard> CPlayerBogo::pick_card(const std::vector<std::shared_ptr<CCard>> &cards, int mode) const {
	uniform_int_distribution<size_t> dist(0, cards.size() - 1);
	random_device rand("/dev/urandom");
	return cards.at(dist(rand));
}

void CPlayerBogo::discard_selection() {
	if ( m_cards_to_discard >= (int)m_hand.count()) {
		discard_all();
		return;
	}

	for ( int i = 0; i < m_cards_to_discard; i ++ ) {
		uniform_int_distribution<size_t> dist(0, m_hand.count() - 1);
		random_device rand("/dev/urandom");
		discard_card( m_hand.cards().at(dist(rand)) );
	}

	m_cards_to_discard = 0;
}

void CPlayerBogo::sacrifice_selection() {
	uniform_int_distribution<size_t> dist(0, m_discard.count() - 1);
	random_device rand("/dev/urandom");
	m_discard.remove( m_discard.cards().at(dist(rand)) );
}

bool CPlayerBogo::buy_card() {

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
		return false;
	}

	uniform_int_distribution<size_t> dist(0, available.size() - 1);
	random_device rand("/dev/urandom");
	shared_ptr<CCard> selected;
	while (true) {
		selected = available.at(dist(rand));

		if ( selected->cost() <= m_cash )
			break;
	}

	m_cash -= selected->cost();
	m_shop->sell_card(selected);
	m_discard.insert(selected);
	m_display->context_bar("Card was bought successfully.");

	m_display->refresh_board(shared_from_this(), m_opponent.lock(), m_shop);
	return true;
}
