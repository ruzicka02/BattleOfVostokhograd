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

/// Abstract player class with its own set of decks and a general card. Implements various actions that move cards
/// between the decks. Contains basic gameplay methods as play_card() and play().
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
	virtual void discard_selection(int amount ) = 0;

	/// Discards all cards from hand to discard pile. Does not throw any card selection to human player.
	void discard_all();

	/// Discards the one specific card from hand to discard pile. Used when playing warcries from hand.
	/// @exception out_of_range Throws exception if card is not in hand.
	virtual void discard_card( std::shared_ptr<CCard> );

	/// Restores health of the referenced card and puts it from table to discard pile.
	/// @exception out_of_range Throws exception if card is not on table.
	void kill_card( std::shared_ptr<CCard> );

	/// Removes the referenced card from table, effectively losing it. Used when card is stolen by opponent.
	/// @exception out_of_range Throws exception if card is not on table.
	void destroy_card( std::shared_ptr<CCard> );

	/// Steals the referenced card from the opponents table. Card is put onto your own table with unchanged health.
	/// @exception out_of_range Throws exception if card is not on opponents table.
	void steal_card( std::shared_ptr<CCard> );

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

	[[nodiscard]] size_t get_discard_count() const {
		return m_discard.count();
	}

	[[nodiscard]] int get_cash() const {
		return m_cash;
	}

	void set_opponent( CPlayer* opponent ) {
		m_opponent = opponent;
	}

	/// Returns true, if the general is dead (health <= 0) and the player has lost.
	[[nodiscard]] bool lost() const {
		return m_general->change_life(0); // life does not change, returns necessary bool
	}

	/// Virtual method for player to play his turn, either manually or automatically.
	virtual void play() = 0;

	/// Method for player to play one card, based on its type and abilities.
	/// @param[in] card The referenced card that will be played.
	/// @param[in] hand True if card is played from hand, false if it already is on the table.
	void play_card(std::shared_ptr<CCard> card, bool hand);

	/// Virtual method for player to choose one card. Performed automatically by AI players.
	/// @return Selected card.
	/// @param[in] cards Cards to choose from.
	/// @param[in] mode Action with the given cards for the AI
	virtual std::shared_ptr<CCard> pick_card( const std::vector< std::shared_ptr<CCard> >& cards, int mode ) const = 0;

	/// Virtual method for player to select and buy a card from shop and put it into discard pile.
	virtual bool buy_card() = 0;
};


#endif //SEMESTRAL_CPLAYER_H
