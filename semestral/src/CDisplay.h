//
// Created by simon on 18.4.22.
//

#ifndef SEMESTRAL_CDISPLAY_H
#define SEMESTRAL_CDISPLAY_H

#include <memory>
#include <string>

#include "CPlayer.h"
#include "CShop.h"

/// Class encapsulation of the majority of interactions with the terminal using the ncurses library. Majority of the
/// methods are used for printing content only, with the exception of card_selection() which returns the selected card.
class CDisplay {
protected:
	int m_scr_y;
	int m_scr_x;
	std::string m_context;
public:
	/// Initializes an empty ncurses screen.
	CDisplay();

	/// Turns off the screen and deallocates all memory.
	~CDisplay();

	/// Compares the terminal size to what is considered minimum to play the game. Appropriate prompt is printed when
	/// the terminal is too small and ncurses get terminated.
	/// @return True if terminal is large enough, false otherwise (game should be terminated).
	bool terminal_size_check() const;

	/// Draws the initializing game menu, returns the selected option.
	int menu();

	/// Prints an information bar to the bottom of the screen, telling user what he can do
	void info_bar( const std::string& info ) const;

	/// Prints a context bar to the top of the screen, telling more about the current action
	void context_bar_draw() const;

	/// Changes the content of context bar on top of the screen, telling more about the current action
	void context_bar( const std::string& context );

	/// Refreshes the screen with the current card state of these two players.
	/// @param[in] first Player who is currently about to play.
	/// @param[in] second Opponent of the playing player.
	void refresh_board( CPlayer* first, CPlayer* second, CShop* shop ) const;

	/// Lets player choose one card from a given deck.
	/// @param[in] cards Cards to select from.
	/// @return Pointer to the selected card.
	std::shared_ptr<CCard> card_selection( const std::vector< std::shared_ptr<CCard> >& ) const;

	/// Lets player choose one card from his hand, table or his general. Used when selecting a card to play.
	/// @param[in] player Player who is currently about to play.
	/// @param[in] played Cards that were already played.
	/// @return Pointer to the selected card.
	std::shared_ptr<CCard> card_selection_ingame( CPlayer* player, std::vector<bool>& played ) const;
};


#endif //SEMESTRAL_CDISPLAY_H
