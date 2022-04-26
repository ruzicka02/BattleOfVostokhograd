//
// Created by simon on 17.4.22.
//

#include <stdexcept>

#include "CDeck.h"

using namespace std;

void CDeck::load_deck(istream &) {

}

void CDeck::save_deck(ostream &) {

}

CDeck &CDeck::insert( shared_ptr<CCard> in ) {
	m_content.emplace_back(in);

	return *this;
}

CDeck &CDeck::remove( shared_ptr <CCard> in ) {
	bool found = false;

	for ( auto iter = m_content.begin(); iter < m_content.end(); iter ++ )
		if ( *iter == in ) {
			m_content.erase(iter);
			found = true;
			break;
		}

	if ( !found )
		throw out_of_range("CDeck::remove exception: Card not contained in deck.");

	return *this;
}

shared_ptr <CCard> CDeck::pop_top() {
	if ( m_content.empty() )
		return nullptr;

	shared_ptr <CCard> val = m_content.back();
	m_content.pop_back();

	return val;
}

shared_ptr <CCard> CDeck::seek_top() const {
	if ( ! m_content.empty() )
		return m_content.back();
	else
		return nullptr;
}

void CDeck::shuffle() {

}
