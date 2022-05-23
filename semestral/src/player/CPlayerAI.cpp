//
// Created by simon on 18.4.22.
//

#include "CPlayerAI.h"
#include "../CDisplay.h"

using namespace std;

bool CPlayerAI::play() {

	// play all cards in hand in sequence
	while(m_hand.count()) {
		m_display->context_bar("Opponent is currently playing." );
		m_display->pause();

		play_card(m_hand.seek_top(), true);
		m_display->refresh_board(shared_from_this(), m_opponent.lock(), m_shop);
	}

	// play all cards on table in sequence
	for ( const shared_ptr<CCardDeckable>& card : m_table.cards()) {
		if ( card->played() )
			continue;

		m_display->context_bar("Opponent is currently playing." );
		m_display->pause();

		play_card(card, false);
		m_display->refresh_board(shared_from_this(), m_opponent.lock(), m_shop);
	}

	play_card(m_general, false);

	m_display->context_bar("Opponent is currently buying new cards." );
	while (	buy_card() ) {
		m_display->pause();
	}

	// set all cards as not played
	for ( size_t i = 0; i < m_table.count(); i ++ )
		m_table.cards().at(i)->set_played(false);

	get_general()->set_played(false);
	return false;
}

std::shared_ptr<CCard> CPlayerAI::pick_card(const std::vector<std::shared_ptr<CCard>> &cards, int mode) const {
	// modes are: 1 attack, 2 protect, 3 steal

	if ( cards.empty() )
		return nullptr;

	// check the best card (the highest score) that will be picked
	int max_score = 0, max_index = 0, i = 0;
	for ( auto card : cards ) {
		int current_score = card->score();

		// change criteria of score when stealing cards... high life is desirable
		if ( mode == 3 ) {
			current_score -= 5 * (card->life().second - card->life().first); // inversion of what was added in CCardTroop
			current_score += 3 * card->life().first;
		}

		// healing card with full health is pointless
		if ( mode == 2 && (card->life().second == card->life().first))
			current_score = 0;

		// highest score
		if ( current_score > max_score ) {
			max_score = card->score();
			max_index = i;
		}

		i++;
	}

	m_display->context_bar("Card at index " + to_string(max_index) + " with score " + to_string(max_score));
	m_display->pause();

	return cards.at(max_index);
}

void CPlayerAI::discard_selection() {
	if ( m_cards_to_discard >= (int)m_hand.count()) {
		discard_all();
		return;
	}

	while ( m_cards_to_discard > 0 ) {
		// check the worst card (the lowest score) in hand that will be discarded
		int min_score = INT32_MAX, min_index = 0;
		for ( size_t i = 0; i < m_hand.count(); i ++ )
			if ( m_hand.cards().at(i)->score() < min_score ) {
				min_score = m_hand.cards().at(i)->score();
				min_index = i;
			}

		discard_card( m_hand.cards().at(min_index) );

		m_cards_to_discard --;
	}

}

void CPlayerAI::sacrifice_selection() {
	if ( !m_discard.count() ) {
		m_display->context_bar("No card in discard pile to sacrifice" );
		return;
	}

	// limit the maximal discard pile depth to be equal with CPlayerHuman
	size_t max_depth = ( m_discard.count() > 10 ) ? 10 : m_discard.count();

	// check the worst card (the lowest score) in hand that will be sacrificed
	int min_score = INT32_MAX, min_index = 0;
	for ( size_t i = 0; i < max_depth; i ++ )
		if ( m_hand.cards().at(i)->score() < min_score ) {
			min_score = m_hand.cards().at(i)->score();
			min_index = i;
		}

	m_discard.remove( m_discard.cards().at(min_index) );
}

bool CPlayerAI::buy_card() {
	auto available = m_shop->cards();

	// check the best card from those that player can afford
	int max_score = 0, max_index = 0;
	for ( size_t i = 0; i < available.size(); i ++ )
		if ( available.at(i)->cost() <= m_cash && available.at(i)->score() > max_score ) {
			max_score = available.at(i)->score();
			max_index = i;
		}

	// no card found... player cannot afford any card
	if ( max_score == 0 ) {
		return false;
	}

	shared_ptr<CCardDeckable> selected = available.at(max_index);

	m_cash -= selected->cost();
	m_shop->sell_card(selected);
	m_discard.insert(selected);

	m_display->refresh_board(shared_from_this(), m_opponent.lock(), m_shop);
	return true;
}
