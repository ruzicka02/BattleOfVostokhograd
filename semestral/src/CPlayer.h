//
// Created by simon on 17.4.22.
//

#ifndef SEMESTRAL_CPLAYER_H
#define SEMESTRAL_CPLAYER_H

#include "CDeck.h"
#include "CCardGeneral.h"

class CPlayer {
protected:
	CCardGeneral 	m_general;
	CDeck			m_drawing;
	CDeck			m_hand;
	CDeck			m_table;
	CDeck			m_discard;
public:
	/// Constructs instance of Player with empty decks.
	/// @param[in] gen General card of Player, necessary for construction
	explicit CPlayer(CCardGeneral gen) : m_general(std::move(gen)) {}
	CPlayer(const CPlayer&) = default;
	CPlayer& operator= (const CPlayer&) = default;
	virtual ~CPlayer() = default;

	/// Draws the given amount of cards from drawing pile to hand.
	void draw_cards (int amount);

	/// Discards the given amount of cards from hand to discard pile. Discards all cards when left without parameter.
	void discard_cards (int amount = 0);

	/// Buys the referenced card from shop and puts it into discard pile.
	void buy_card ( std::shared_ptr<CCard> );

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
		return m_discard.seek_front();
	}

	/// Virtual method for player to do stuff, either manually or automatically.
	virtual void play() = 0;
};


#endif //SEMESTRAL_CPLAYER_H
