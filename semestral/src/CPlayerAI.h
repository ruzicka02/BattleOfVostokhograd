//
// Created by simon on 18.4.22.
//

#ifndef SEMESTRAL_CPLAYERAI_H
#define SEMESTRAL_CPLAYERAI_H

#include "CPlayer.h"

class CPlayerAI : public CPlayer {
protected:
public:
	CPlayerAI( std::shared_ptr<CCardGeneral> gen, const CDeck& deck, CDisplay* display, CShop* shop )
			: CPlayer(std::move(gen), deck, display, shop) {}

	void play() override;

	/// Virtual method for player to choose one card using CDisplay::card_selection()
	/// @return Selected card.
	/// @param[in] cards Cards to choose from.
	/// @param[in] mode Action with the given cards for the AI
	std::shared_ptr<CCard> pick_card( const std::vector< std::shared_ptr<CCard> >& cards, int mode ) const override;

	void discard_cards (int amount) override;
};

#endif //SEMESTRAL_CPLAYERAI_H
