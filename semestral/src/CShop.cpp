//
// Created by simon on 17.4.22.
//
#include <iostream>
#include "CShop.h"

using namespace std;

void CShop::print_shop( int y, int x ) {
	for ( auto card : m_content ) {
		card->print_card(y, x);
		y += 4;
	}
}

bool CShop::load_deck( std::istream& file, bool shuffle ) {
	const int SHOP_SIZE = 5;

	bool ret_val = m_drawing.load_deck(file, shuffle);
	for ( int i = 0; i < SHOP_SIZE; i ++ ) {
		insert(m_drawing.pop_top());
	}

	return ret_val;
}

bool CShop::save_deck( std::ostream& file ) {
	// save the drawing pile to the file first
	bool ret_val = m_drawing.save_deck(file);

	if ( ret_val )
		ret_val = CDeck::save_deck(file);

	return ret_val;
}

void CShop::sell_card( std::shared_ptr<CCard> card ) {
	// card is removed from visible shop
	remove( card );

	// new card from drawing pile (if it is available)
	if ( m_drawing.pop_top() )
		insert(m_drawing.pop_top());
}