//
// Created by simon on 17.4.22.
//

#include "CPlayer.h"

void CPlayer::draw_cards(int amount) {
	for ( int i = 0; i < amount; i++ )
		m_hand.insert(m_drawing.pop_top());
}

void CPlayer::discard_all() {
	while ( m_hand.seek_top() )
		m_discard.insert(m_hand.pop_top());
}

void CPlayer::kill_card(std::shared_ptr <CCard> target) {
	target->restore();
	m_table.remove(target);
	m_discard.insert(target);
}

void CPlayer::destroy_card(std::shared_ptr <CCard> target) {
	m_table.remove(target);
}

void CPlayer::steal_card(std::shared_ptr <CCard> target) {
	m_opponent->destroy_card(target);

	m_table.insert(target);
}

void CPlayer::buy_card(std::shared_ptr <CCard> target) {
	m_discard.insert(target);
}

void CPlayer::deploy_card(std::shared_ptr<CCard> target) {
	m_hand.remove(target);
	m_table.insert(target);
}
