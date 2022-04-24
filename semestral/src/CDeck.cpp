//
// Created by simon on 17.4.22.
//

#include "CDeck.h"

using namespace std;

void CDeck::load_deck(istream &) {

}

void CDeck::save_deck(ostream &) {

}

CDeck &CDeck::insert(CCard &) {
	return *this;
}

CDeck &CDeck::remove(shared_ptr <CCard>) {
	return *this;
}

shared_ptr <CCard> CDeck::pop_top() {
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
