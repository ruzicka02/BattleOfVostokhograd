//
// Created by simon on 17.4.22.
//

#ifndef SEMESTRAL_CPLAYER_H
#define SEMESTRAL_CPLAYER_H

#include "CDeck.h"
#include "CShop.h"
#include "CCardGeneral.h"

// forward declaration because of calling certain CDisplay methods
class CDisplay;

class CPlayer {
protected:
	int 							m_cash;
	std::shared_ptr<CCardGeneral> 	m_general;
	CDeck							m_drawing;
	CDeck							m_hand;
	CDeck							m_table;
	CDeck							m_discard;

	CPlayer*						m_opponent;
	CShop*							m_shop;
	CDisplay*						m_display;
public:
	/// Constructs instance of Player with empty decks.
	/// @param[in] gen General card of Player, necessary for construction
	CPlayer( std::shared_ptr<CCardGeneral> gen, const CDeck& deck, CDisplay* display, CShop* shop )
		: m_cash(0), m_general(std::move(gen)), m_drawing(deck), m_opponent(nullptr), m_shop(shop), m_display(display) {}
	CPlayer( const CPlayer& ) = default;
	CPlayer& operator= ( const CPlayer& ) = default;
	virtual ~CPlayer() {
		m_opponent = nullptr;
	}

	/// Draws the given amount of cards from drawing pile to hand.
	void draw_cards( int amount );

	/// Discards the given amount of cards from hand to discard pile. Lets human player select, which cards he wants to discard.
	virtual void discard_cards( int amount ) = 0;

	/// Discards all cards from hand to discard pile. Does not throw any card selection to human player.
	void discard_all();

	/// Restores health of the referenced card and puts it from table to discard pile.
	/// @exception out_of_range Throws exception if card is not on table.
	void kill_card( std::shared_ptr<CCard> );

	/// Removes the referenced card from table, effectively losing it. Used when card is stolen by opponent.
	/// @exception out_of_range Throws exception if card is not on table.
	void destroy_card( std::shared_ptr<CCard> );

	/// Steals the referenced card from the opponents table. Card is put onto your own table with unchanged health.
	/// @exception out_of_range Throws exception if card is not on opponents table.
	void steal_card( std::shared_ptr<CCard> );

	/// Buys the referenced card from shop and puts it into discard pile.
	void buy_card( std::shared_ptr<CCard> );

	/// Deploys the referenced card from hand to the table.
	/// @exception out_of_range Throws exception if card is not in hand.
	void deploy_card( std::shared_ptr<CCard> );

	[[nodiscard]] std::shared_ptr<CCardGeneral> get_general() const {
		return m_general;
	}

	[[nodiscard]] const std::vector< std::shared_ptr<CCard> >& get_hand() const {
		return m_hand.cards();
	}

	[[nodiscard]] const std::vector< std::shared_ptr<CCard> >& get_table() const {
		return m_table.cards();
	}

	[[nodiscard]] std::shared_ptr<CCard> get_discard_top() const {
		return m_discard.seek_top();
	}

	[[nodiscard]] size_t get_draw_count() const {
		return m_drawing.count();
	}

	[[nodiscard]] int get_cash() const {
		return m_cash;
	}

	/// Virtual method for player to play his turn, either manually or automatically.
	virtual void play() = 0;

	/// Virtual method for player to play one card, either manually or automatically.
	/// @param[in] card The referenced card that will be played.
	/// @param[in] hand True if card is played from hand, false if it already is on the table.
	virtual void play_card(std::shared_ptr<CCard> card, bool hand) = 0;
};


#endif //SEMESTRAL_CPLAYER_H
