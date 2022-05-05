//
// Created by simon on 17.4.22.
//

#ifndef SEMESTRAL_CSHOP_H
#define SEMESTRAL_CSHOP_H

#include "CDeck.h"

/// Derived class from CDeck representing the in-game card shop. It is actually represented by two decks, where cards
/// in the "main deck" are visible by the print_shop() method, and the secondary m_drawing deck refills the main one.
class CShop : public CDeck {
protected:
	CDeck m_drawing;
public:
	CShop() = default;
	CShop( const CShop& ) = default;
	CShop& operator= ( const CShop& ) = default;
	~CShop() = default;

	/// Prints image of cards in shop to terminal on given coordinates.
	/// @param[in] y The y vertical coordinate (distance from top).
	/// @param[in] x The x horizontal coordinate (distance from left).
	void print_shop( int y, int x );

	/// Loads all cards from a csv file into the drawing pile and puts top 5 cards to the shop.
	/// @return True on success, False if a problem (I/O, invalid data) occurred.
	/// @param[in] file Stream from which the card definitions are loaded.
	/// @param[in] shuffle Decides whether cards are shuffled BEFORE the split to shop and drawing pile.
	virtual bool load_deck( std::istream& file, bool shuffle = false ) override;

	/// Saves all cards into a csv file from the drawing pile as well as the shop.
	/// @return True on success, False if a problem (I/O) occurred.
	virtual bool save_deck( std::ostream& ) override;

	/// Removes the referenced card from the store and refills with another card from drawing pile.
	/// @exception out_of_range Throws exception in CDeck::remove when card is not found in the shop.
	void sell_card( std::shared_ptr<CCard> );

};


#endif //SEMESTRAL_CSHOP_H
