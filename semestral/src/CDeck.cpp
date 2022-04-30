//
// Created by simon on 17.4.22.
//

#include <iostream>
#include <stdexcept>
#include <string>
#include <random>
#include <algorithm>

#include "CDeck.h"

using namespace std;

bool CDeck::load_deck(istream & file) {

	string line;

	// loads a single card from a line of source file
	while (getline(file, line)) {

		if ( ! file.good() )
			return false;

		// line too short
		if ( line.length() <= 1 )
			continue;

		// comment
		if ( line[0] == '/' && line[1] == '/' )
			continue;

		// creates the shared pointer in CCard::load_card
		shared_ptr<CCard> in = CCard::load_card(line);
		if ( in == nullptr )
			return false;

		insert( in );
	}

	return true;
}

bool CDeck::save_deck(ostream & file) {
	for ( auto card : m_content )
		file << card->save_card() << '\n';

	return file.good();
}

CDeck &CDeck::insert( shared_ptr<CCard> in ) {
	if ( in != nullptr )
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

void CDeck::shuffle_cards() {
	random_device rand;
	shuffle( m_content.begin(), m_content.end(), rand );
}
