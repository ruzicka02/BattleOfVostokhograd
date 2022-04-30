//
// Created by simon on 17.4.22.
//

#ifndef SEMESTRAL_CSHOP_H
#define SEMESTRAL_CSHOP_H

#include "CDeck.h"

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
	virtual bool load_deck( std::istream& ) override;

	/// Saves all cards into a csv file from the drawing pile as well as the shop.
	/// @return True on success, False if a problem (I/O) occurred.
	virtual bool save_deck( std::ostream& ) override;

	/// Removes the referenced card from the store and refills with another card from drawing pile.
	/// @exception out_of_range Throws exception in CDeck::remove when card is not found in the shop.
	void sell_card( std::shared_ptr<CCard> );
};


#endif //SEMESTRAL_CSHOP_H
