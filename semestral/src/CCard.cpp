//
// Created by simon on 15.4.22.
//

#include "CCard.h"
#include "CPlayer.h"

#include <memory>

void CCard::attack( CPlayer& player, std::shared_ptr<CCard> target ) {
	bool killed = target->change_life(-1 * m_damage);

	if (killed)
		player.kill_card(target);
}

void CCard::protect( CPlayer& player, std::shared_ptr<CCard> target ) {
	target->change_life(m_protection);
}

void CCard::special( CPlayer &player, std::shared_ptr <CCard> target) {
	switch (m_special) {
		case null:
			break;
		case steal:
			player.steal_card(target);
			break;
		case draw:
			player.draw_cards(1);
			break;
	}
}
