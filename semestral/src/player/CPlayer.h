//
// Created by simon on 17.4.22.
//

#ifndef SEMESTRAL_CPLAYER_H
#define SEMESTRAL_CPLAYER_H

#include <utility>

#include "../CShop.h"
#include "../card/CCardGeneral.h"

// forward declaration to avoid unnecessary references
class CDisplay;

/// Abstract player class with its own set of decks and a general card. Implements various actions that move cards
/// between the decks. Contains basic gameplay methods as play_card() and play(). Inherits from std::enable_shared_from_this
/// as it needs to create own shared pointers when calling CDisplay::refresh_board().
class CPlayer : public std::enable_shared_from_this<CPlayer> {
protected:
	int 							m_cards_to_discard;
	int 							m_cash;
	std::shared_ptr<CCardGeneral> 	m_general;
	CDeck							m_drawing;
	CDeck							m_hand;
	CDeck							m_table;
	CDeck							m_discard;

	std::weak_ptr<CPlayer>			m_opponent;
	CShop*							m_shop;
	CDisplay*						m_display;
public:
	/// Constructs instance of Player with empty decks.
	/// @param[in] gen General card of Player, necessary for construction
	CPlayer( std::shared_ptr<CCardGeneral> gen, const CDeck& deck, CDisplay* display, CShop* shop )
			: m_cards_to_discard(0), m_cash(0), m_general(std::move(gen)), m_drawing(deck), m_shop(shop), m_display(display) {}
	CPlayer( const CPlayer& ) = default;
	CPlayer& operator= ( const CPlayer& ) = default;
	virtual ~CPlayer() = default;

	/// Alternative constructor loads all information about player from a CSV file.
	/// @param[in] file Stream from which the card definitions are loaded.
	CPlayer( std::istream& file, CDisplay* display, CShop* shop );

	/// Saves all information about player and his cards into a CSV file.
	/// @return True on success, False if a problem (I/O) occurred.
	bool save_player( std::ostream& file );

	/// Draws the given amount of cards from drawing pile to hand.
	void draw_cards( size_t amount );

	/// Discards the given amount of cards from hand to discard pile. Lets human player select, which cards he wants to discard.
	virtual void discard_selection() = 0;

	/// Sacrifices the given amount of cards from discard pile to /dev/null. Lets human player select, which cards he wants to discard.
	virtual void sacrifice_selection() = 0;

	/// Discards all cards from hand to discard pile. Does not throw any card selection to human player.
	void discard_all();

	/// Discards the one specific card from hand to discard pile. Used when playing warcries from hand.
	/// @exception out_of_range Throws exception if card is not in hand.
	void discard_card( std::shared_ptr<CCardDeckable> );

	/// Restores health of the referenced card and puts it from table to discard pile.
	/// @exception out_of_range Throws exception if card is not on table.
	void kill_card( std::shared_ptr<CCard> );

	/// Removes the referenced card from table, effectively losing it. Used when card is stolen by opponent.
	/// @exception out_of_range Throws exception if card is not on table.
	void destroy_card( std::shared_ptr<CCardDeckable> );

	/// Steals the referenced card from the opponents table. Card is put onto your own table with unchanged health.
	/// @exception out_of_range Throws exception if card is not on opponents table.
	void steal_card( std::shared_ptr<CCardDeckable> );

	/// Deploys the referenced card from hand to the table.
	/// @exception out_of_range Throws exception if card is not in hand.
	void deploy_card( std::shared_ptr<CCardDeckable> );

	void opponent_discard( int amount ) {
		m_opponent.lock()->m_cards_to_discard ++;
	}

	[[nodiscard]] std::shared_ptr<CCardGeneral> get_general() const {
		return m_general;
	}

	[[nodiscard]] const std::vector< std::shared_ptr<CCardDeckable> >& get_hand() const {
		return m_hand.cards();
	}

	[[nodiscard]] const std::vector< std::shared_ptr<CCardDeckable> >& get_table() const {
		return m_table.cards();
	}

	[[nodiscard]] std::shared_ptr<CCardDeckable> get_discard_top() const {
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

	void set_opponent( std::weak_ptr<CPlayer> opponent ) {
		m_opponent = std::move(opponent);
	}

	/// Returns true, if the general is dead (health <= 0) and the player has lost.
	[[nodiscard]] bool lost() const {
		return m_general->change_life(0); // life does not change, returns necessary bool
	}

	/// Virtual method for player to play his turn, either manually or automatically.
	/// @return True if game is supposed to be stopped/paused (by human player).
	virtual bool play() = 0;

	/// Method for player to play one card, based on its type and abilities.
	/// @param[in] card The referenced card that will be played.
	/// @param[in] hand True if card is played from hand, false if it already is on the table.
	void play_card(std::shared_ptr<CCard> card, bool hand);

	/// Virtual method for player to choose one card. Performed automatically by AI players.
	/// @return Selected card.
	/// @param[in] cards Cards to choose from. Undefined behavior for empty vector.
	/// @param[in] mode Action with the given cards for the AI.
	virtual std::shared_ptr<CCard> pick_card( const std::vector< std::shared_ptr<CCard> >& cards, int mode ) const = 0;
};

#endif //SEMESTRAL_CPLAYER_H
