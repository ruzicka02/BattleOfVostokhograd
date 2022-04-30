//
// Created by simon on 17.4.22.
//

#ifndef SEMESTRAL_CDECK_H
#define SEMESTRAL_CDECK_H

#include <vector>
#include <memory>

#include "CCard.h"

class CDeck {
protected:
	std::vector< std::shared_ptr<CCard> > m_content;
public:
	CDeck() = default;
	CDeck( const CDeck& ) = default;
	CDeck& operator= ( const CDeck& ) = default;
	virtual ~CDeck() = default;

	/// Loads all cards from a csv file into the deck. Card order is shuffled randomly.
	/// @return True on success, False if a problem (I/O, invalid data) occurred.
	virtual bool load_deck( std::istream& );

	/// Saves all cards into a csv file from the deck.
	/// @return True on success, False if a problem (I/O) occurred.
	virtual bool save_deck( std::ostream& );

	/// Inserts the referenced card to the top of deck.
	/// @return self
	CDeck& insert( std::shared_ptr<CCard> );

	/// Removes the referenced card from the deck.
	/// @exception out_of_range Throws exception when card is not found in the deck.
	/// @return self
	CDeck& remove( std::shared_ptr<CCard> );

	/// Removes the top card from the deck.
	/// @return The removed card. Returns nullptr for an empty deck.
	std::shared_ptr<CCard> pop_top();

	/// Looks at the top card in the deck without removing it.
	/// @return The card on top. Returns nullptr for an empty deck.
	std::shared_ptr<CCard> seek_top() const;

	/// Standard getter for cards contained in deck.
	const std::vector< std::shared_ptr<CCard> >& cards() const {
		return m_content;
	}

	/// Shuffles the contained cards to a new, random order.
	void shuffle_cards();
};


#endif //SEMESTRAL_CDECK_H
