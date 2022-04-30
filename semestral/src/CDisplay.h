//
// Created by simon on 18.4.22.
//

#ifndef SEMESTRAL_CDISPLAY_H
#define SEMESTRAL_CDISPLAY_H

#include <memory>

#include "CPlayer.h"

class CDisplay {
protected:
	int m_scr_width;
	int m_scr_height;
public:
	/// Initializes an empty ncurses screen.
	CDisplay();

	/// Turns off the screen and deallocates all memory.
	~CDisplay();

	/// Draws the initializing game menu, returns the selected option.
	int menu();

	/// Refreshes the screen with the current card state of these two players.
	/// @param[in] first Player who is currently about to play.
	/// @param[in] second Opponent of the playing player.
	void refresh_board( std::shared_ptr<CPlayer> first, std::shared_ptr<CPlayer> second );

	/// Lets player choose one card from a given deck.
	/// @return Pointer to the selected card.
	std::shared_ptr<CCard> card_selection( const CDeck& );
};


#endif //SEMESTRAL_CDISPLAY_H
