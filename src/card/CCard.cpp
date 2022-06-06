//
// Created by simon on 15.4.22.
//

#include "CCard.h"

#include "../player/CPlayer.h"

using namespace std;

void CCard::attack( shared_ptr<CPlayer> player, shared_ptr<CCard> target ) const {
	bool killed = target->change_life(-1 * m_damage);

	if (killed)
		player->kill_card(target);
}

void CCard::protect( shared_ptr<CPlayer> player, std::shared_ptr<CCard> target ) const {
	target->change_life(m_protection);
}

void CCard::special( shared_ptr<CPlayer> player, shared_ptr<CCardDeckable> target) const {
	switch (m_special) {
		case null:
			break;
		case steal:
			player->steal_card(target);
			break;
		case draw:
			player->draw_cards(1);
			break;
		case discard:
			player->opponent_discard(1);
			break;
		case sacrifice:
			player->sacrifice_selection();
			break;
	}
}
