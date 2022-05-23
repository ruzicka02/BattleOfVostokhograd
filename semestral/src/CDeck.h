//
// Created by simon on 17.4.22.
//

#ifndef SEMESTRAL_CDECK_H
#define SEMESTRAL_CDECK_H

#include <vector>
#include <memory>
#include <iostream>

#include "card/CCardDeckable.h"
#include "card/EAbility.h"

/// Container for various CCardDeckable derived objects, used on various places throughout the game. It is only recommended to
/// use in cases where all the connected methods are desirable - otherwise, only the pure vector of CCard pointers is used.
/// Contains logic for importing and exporting the card definitions to and from a CSV file.
class CDeck {
protected:
	std::vector< std::shared_ptr<CCardDeckable> > m_content;
public:
	CDeck() = default;
	CDeck( const CDeck& ) = default;
	CDeck& operator= ( const CDeck& ) = default;
	virtual ~CDeck() = default;

	/// Loads all cards from a CSV file into the deck.
	/// @return True on success, False if a problem (I/O, invalid data) occurred.
	/// @param[in] file Stream from which the card definitions are loaded.
	/// @param[in] shuffle Decides whether cards are shuffled randomly, turned off by default.
	virtual bool load_deck( std::istream& file, bool shuffle = false );

	/// Saves all cards into a CSV file from the deck.
	/// @return True on success, False if a problem (I/O) occurred.
	virtual bool save_deck( std::ostream& file );

	/// Inserts the referenced card to the top of deck.
	/// @return self
	CDeck& insert( std::shared_ptr<CCardDeckable> );

	/// Removes the referenced card from the deck.
	/// @exception out_of_range Throws exception when card is not found in the deck.
	/// @return self
	CDeck& remove( std::shared_ptr<CCardDeckable> );

	/// Removes the top card from the deck.
	/// @return The removed card. Returns nullptr for an empty deck.
	std::shared_ptr<CCardDeckable> pop_top();

	/// Looks at the top card in the deck without removing it.
	/// @return The card on top. Returns nullptr for an empty deck.
	std::shared_ptr<CCardDeckable> seek_top() const;

	/// Standard getter for cards contained in deck.
	const std::vector< std::shared_ptr<CCardDeckable> >& cards() const {
		return m_content;
	}

	/// Standard getter for count of cards contained in deck.
	size_t count() const {
		return m_content.size();
	}

	/// Shuffles the contained cards to a new, random order.
	void shuffle_cards();
};


#endif //SEMESTRAL_CDECK_H
