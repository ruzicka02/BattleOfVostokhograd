//
// Created by simon on 18.4.22.
//

#include "CPlayerAI.h"

bool CPlayerAI::play() {

}

std::shared_ptr<CCard> CPlayerAI::pick_card(const std::vector<std::shared_ptr<CCard>> &cards, int mode) const {
	return cards.at(0);
}

void CPlayerAI::discard_selection() {

}

void CPlayerAI::sacrifice_selection() {

}
