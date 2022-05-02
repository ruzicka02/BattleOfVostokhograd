//
// Created by simon on 18.4.22.
//

#ifndef SEMESTRAL_CPLAYERHUMAN_H
#define SEMESTRAL_CPLAYERHUMAN_H

#include "CPlayer.h"

class CPlayerHuman : public CPlayer {
protected:
public:
	CPlayerHuman( std::shared_ptr<CCardGeneral> gen, const CDeck& deck, CDisplay* display, CShop* shop )
			: CPlayer(std::move(gen), deck, display, shop) {}

	void play() override;
	void play_card(std::shared_ptr<CCard> card, bool hand) override;

	void discard_cards (int amount) override;
};


#endif //SEMESTRAL_CPLAYERHUMAN_H
