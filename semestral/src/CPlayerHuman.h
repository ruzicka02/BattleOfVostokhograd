//
// Created by simon on 18.4.22.
//

#ifndef SEMESTRAL_CPLAYERHUMAN_H
#define SEMESTRAL_CPLAYERHUMAN_H

#include "CPlayer.h"

/// Derived class of CPlayer that implements player interaction with the game. Calls CDisplay::card_selection to choose
/// cards for needed actions.
class CPlayerHuman : public CPlayer {
protected:

	/// Lets player choose one card from his hand, table or his general. Used when selecting a card to play. Card is
	/// then played directly from this function.
	void card_selection_ingame();

	/// Lets player select a card to buy from the shop and inserts it into the discard pile. Aborted if player has
	/// insufficient funds for this action.
	/// @return False in case no card has been bought.
	bool buy_card();
public:
	CPlayerHuman( std::shared_ptr<CCardGeneral> gen, const CDeck& deck, CDisplay* display, CShop* shop )
			: CPlayer(std::move(gen), deck, display, shop) {}
	CPlayerHuman( const CPlayerHuman& ) = default;
	CPlayerHuman& operator= ( const CPlayerHuman& ) = default;
	~CPlayerHuman() override = default;

	void play() override;

	/// Virtual method for player to choose one card using CDisplay::card_selection()
	/// @return Selected card.
	/// @param[in] cards Cards to choose from.
	/// @param[in] mode Action with the given cards for the AI
	[[nodiscard]] std::shared_ptr<CCard> pick_card( const std::vector< std::shared_ptr<CCard> >& cards, int mode ) const override;

	void discard_selection (int amount) override;

};


#endif //SEMESTRAL_CPLAYERHUMAN_H
