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

	/// Inserts the referenced card to the deck.
	CDeck& insert( CCard& );

	/// Removes the referenced card from the deck.
	CDeck& remove( std::shared_ptr<CCard> );

	CDeck& pop_front();

	void shuffle();
};


#endif //SEMESTRAL_CDECK_H
