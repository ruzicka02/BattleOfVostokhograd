//
// Created by simon on 17.4.22.
//
#include <iostream>
#include <utility>
#include "CShop.h"

using namespace std;

void CShop::print_shop( int y, int x ) {
	for ( size_t i = 0; i < m_content.size(); i ++ ) {
		m_content.at(i)->print_card(y + 4 * (int)i, x);
	}
}

bool CShop::load_deck( std::istream& file, bool shuffle ) {
	const int SHOP_SIZE = 5;

	bool ret_val = m_drawing.load_deck(file, shuffle);
	for ( int i = 0; i < SHOP_SIZE; i ++ ) {
		// drawing pile is empty
		if (!m_drawing.seek_top())
			return true;

		insert(m_drawing.pop_top());
	}

	// swap cards to original order (saves should be identical)
	for ( int i = 0; i < SHOP_SIZE / 2; i ++ ) {
		swap(m_content.at(i), m_content.at(SHOP_SIZE - 1 - i));
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

void CShop::sell_card( std::shared_ptr<CCardDeckable> card ) {
	// card is removed from visible shop
	remove( std::move(card) );

	// new card from drawing pile (if it is available)
	if ( m_drawing.seek_top() )
		insert(m_drawing.pop_top());
}