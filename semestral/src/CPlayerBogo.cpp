//
// Created by simon on 5.5.22.
//

#include "CPlayerBogo.h"

void CPlayerBogo::play() {

}

std::shared_ptr<CCard> CPlayerBogo::pick_card(const std::vector<std::shared_ptr<CCard>> &cards, int mode) const {
	return cards.at(0);
}

void CPlayerBogo::discard_selection() {

}

void CPlayerBogo::sacrifice_selection() {

}
