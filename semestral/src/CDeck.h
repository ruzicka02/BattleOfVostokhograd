//
// Created by simon on 17.4.22.
//

#ifndef SEMESTRAL_CDECK_H
#define SEMESTRAL_CDECK_H

#include <vector>
#include "CCard.h"

class CDeck {
protected:
	std::vector< std::shared_ptr<CCard> > m_content;
public:
	CDeck() = default;
	CDeck( const CDeck& ) = default;
	CDeck& operator= ( const CDeck& ) = default;
	virtual ~CDeck() = default;

	// translation between game logic and csv files
	virtual void load_deck( std::istream& );
	virtual void save_deck( std::ostream& );

	/// Inserts the referenced card to the top of deck.
	/// @return self
	CDeck& insert( CCard& );

	/// Removes the referenced card from the deck.
	/// @return self
	CDeck& remove( std::shared_ptr<CCard> );

	/// Removes the top card from the deck.
	/// @return The removed card.
	std::shared_ptr<CCard> pop_front();

	/// Looks at the top card in the deck without removing it.
	/// @return The card on top.
	std::shared_ptr<CCard> seek_front();

	/// Standard getter for cards contained in deck.
	const std::vector< std::shared_ptr<CCard> >& cards() const {
		return m_content;
	}

	/// Shuffles the contained cards to a new, random order.
	void shuffle();
};


#endif //SEMESTRAL_CDECK_H
