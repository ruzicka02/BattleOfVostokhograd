//
// Created by simon on 5.5.22.
//

#ifndef SEMESTRAL_CPLAYERBOGO_H
#define SEMESTRAL_CPLAYERBOGO_H

#include "CPlayer.h"

/// Derived class of CPlayer that implements the most simple random AI behavior.
class CPlayerBogo : public CPlayer {
protected:
	/// Player selects a random card to buy from the shop and inserts it into the discard pile. Aborted if player has
	/// insufficient funds for this action.
	/// @return False in case no card has been bought.
	bool buy_card();
public:
	CPlayerBogo( std::shared_ptr<CCardGeneral> gen, const CDeck& deck, CDisplay* display, CShop* shop )
			: CPlayer(std::move(gen), deck, display, shop) {}
	CPlayerBogo( const CPlayerBogo& ) = default;
	CPlayerBogo& operator= ( const CPlayerBogo& ) = default;
	~CPlayerBogo() override = default;

	CPlayerBogo( std::istream& file, CDisplay* display, CShop* shop )
	: CPlayer(file, display, shop) {}

	std::string save_player_type() override {
		return "Bogo";
	}

	bool play() override;

	/// Virtual method for player to choose one card using the power of randomness.
	/// @return Selected card.
	/// @param[in] cards Cards to choose from.
	/// @param[in] mode Action with the given cards for the AI
	std::shared_ptr<CCard> pick_card( const std::vector< std::shared_ptr<CCard> >& cards, int mode ) const override;

	void discard_selection() override;
	void sacrifice_selection() override;
};


#endif //SEMESTRAL_CPLAYERBOGO_H
