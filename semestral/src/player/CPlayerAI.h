//
// Created by simon on 18.4.22.
//

#ifndef SEMESTRAL_CPLAYERAI_H
#define SEMESTRAL_CPLAYERAI_H

#include "CPlayer.h"

/// Derived class of CPlayer that implements the smarter AI behavior. From the given cards to buy, attack etc.
/// it selects the most adequate one, using internal heuristics.
class CPlayerAI : public CPlayer {
protected:
	/// Player selects the best fitted card to buy from the shop and inserts it into the discard pile. Aborted if player
	/// has insufficient funds for this action.
	/// @return False in case no card has been bought.
	bool buy_card();
public:
	CPlayerAI( std::shared_ptr<CCardGeneral> gen, const CDeck& deck, CDisplay* display, CShop* shop )
			: CPlayer(std::move(gen), deck, display, shop) {}
	CPlayerAI( const CPlayerAI& ) = default;
	CPlayerAI& operator= ( const CPlayerAI& ) = default;
	~CPlayerAI() override = default;

	bool play() override;

	/// Virtual method for player to choose one card using smart heuristics.
	/// @return Selected card.
	/// @param[in] cards Cards to choose from.
	/// @param[in] mode Action with the given cards for the AI
	std::shared_ptr<CCard> pick_card( const std::vector< std::shared_ptr<CCard> >& cards, int mode ) const override;

	void discard_selection() override;
	void sacrifice_selection() override;
};

#endif //SEMESTRAL_CPLAYERAI_H
