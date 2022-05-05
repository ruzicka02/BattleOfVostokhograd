//
// Created by simon on 5.5.22.
//

#ifndef SEMESTRAL_CPLAYERBOGO_H
#define SEMESTRAL_CPLAYERBOGO_H

#include "CPlayer.h"

/// Derived class of CPlayer that implements the most simple random AI behavior.
class CPlayerBogo : public CPlayer {
protected:
public:
	CPlayerBogo( std::shared_ptr<CCardGeneral> gen, const CDeck& deck, CDisplay* display, CShop* shop )
			: CPlayer(std::move(gen), deck, display, shop) {}

	void play() override;

	/// Virtual method for player to choose one card using the power of randomness.
	/// @return Selected card.
	/// @param[in] cards Cards to choose from.
	/// @param[in] mode Action with the given cards for the AI
	std::shared_ptr<CCard> pick_card( const std::vector< std::shared_ptr<CCard> >& cards, int mode ) const override;

	void discard_cards (int amount) override;
};


#endif //SEMESTRAL_CPLAYERBOGO_H
