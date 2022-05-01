//
// Created by simon on 18.4.22.
//

#include <string>
#include <sstream>

#include "CDisplay.h"
#include "CPlayerHuman.h"

using namespace std;

void CPlayerHuman::play() {
	m_display->context_bar("Your turn!" );
	m_display->info_bar("Sample controls for playing the game");

//	while (true) {
//
//		return;
//	}
}

void CPlayerHuman::discard_cards (int amount) {

	for ( int i = 0; i < amount; i ++ ) {
		stringstream context;
		context << i << '/' << amount << " discarded";
		m_display->context_bar(context.str());
		m_hand.remove( m_display->card_selection(m_hand) );
	}


}