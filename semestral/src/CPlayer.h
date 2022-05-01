//
// Created by simon on 17.4.22.
//

#ifndef SEMESTRAL_CPLAYER_H
#define SEMESTRAL_CPLAYER_H

#include "CDeck.h"
#include "CCardGeneral.h"

// forward declaration because of calling certain CDisplay methods
class CDisplay;

class CPlayer {
protected:
	CCardGeneral 	m_general;
	CDeck			m_drawing;
	CDeck			m_hand;
	CDeck			m_table;
	CDeck			m_discard;

	CPlayer*		m_opponent;
	CDisplay*		m_display;
public:
	/// Constructs instance of Player with empty decks.
	/// @param[in] gen General card of Player, necessary for construction
	CPlayer( CCardGeneral gen, CDisplay* display )
		: m_general(std::move(gen)), m_opponent(nullptr), m_display(display) {}
	CPlayer( const CPlayer& ) = default;
	CPlayer& operator= ( const CPlayer& ) = default;
	virtual ~CPlayer() = default;

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
	void destroy_card( std::shared_ptr<CCard> );

	/// Steals the referenced card from the opponents table. Card is put onto your own table with unchanged health.
	void steal_card( std::shared_ptr<CCard> );

	/// Buys the referenced card from shop and puts it into discard pile.
	void buy_card( std::shared_ptr<CCard> );

	const CCardGeneral &get_general() const {
		return m_general;
	}

	const std::vector< std::shared_ptr<CCard> >& get_hand() const {
		return m_hand.cards();
	}

	const std::vector< std::shared_ptr<CCard> >& get_table() const {
		return m_table.cards();
	}

	const std::shared_ptr<CCard> get_discard_top() const {
		return m_discard.seek_top();
	}

	/// Virtual method for player to do stuff, either manually or automatically.
	virtual void play() = 0;
};


#endif //SEMESTRAL_CPLAYER_H
