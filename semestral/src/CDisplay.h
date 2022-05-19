//
// Created by simon on 18.4.22.
//

#ifndef SEMESTRAL_CDISPLAY_H
#define SEMESTRAL_CDISPLAY_H

#include <memory>
#include <string>

#include "player/CPlayer.h"
#include "CShop.h"

/// Class encapsulation of the majority of interactions with the terminal using the ncurses library. Majority of the
/// methods are used for printing content only, with the exception of card_selection() which returns the selected card.
class CDisplay {
protected:
	int m_scr_y;
	int m_scr_x;
	std::string m_context;

	/// Prints a context bar to the top of the screen, telling more about the current action
	void context_bar_draw() const;

	/// Prints the given collection of cards to the screen next to each other to given coordinates.
	/// @param[in] max Maximum amount of cards that can fit to screen.
	/// @return Amount of unprinted cards (compared to given max).
	[[nodiscard]] int print_cards( const std::vector<std::shared_ptr<CCardDeckable>>& cards, int y, int x, int max ) const;
public:
	/// Initializes an empty ncurses screen.
	CDisplay();

	/// Turns off the screen and deallocates all memory.
	~CDisplay();

	/// Compares the terminal size to what is considered minimum to play the game. Appropriate prompt is printed when
	/// the terminal is too small and ncurses get terminated.
	/// @return True if terminal is large enough, false otherwise (game should be terminated).
	bool terminal_size_check() const;

	/// Draws the game menu selection with variable options.
	/// @param[in] options Selectable options to be displayed in the menu.
	/// @return Index number of selected option in the menu by the user.
	int menu(std::vector<std::string> options) const;

	/// Prints an information bar to the bottom of the screen, telling user what he can do
	void info_bar( const std::string& info ) const;

	/// Changes the content of context bar on top of the screen, telling more about the current action
	void context_bar( const std::string& context );

	/// Refreshes the screen with the current card state of these two players.
	/// @param[in] first Player who is currently about to play.
	/// @param[in] second Opponent of the playing player.
	void refresh_board( std::shared_ptr<CPlayer> first, std::shared_ptr<CPlayer> second, CShop* shop ) const;

	/// Lets player choose one card from a given deck.
	/// @param[in] cards Cards to select from.
	/// @return Pointer to the selected card.
	[[nodiscard]] std::shared_ptr<CCard> card_selection( const std::vector< std::shared_ptr<CCard> >& ) const;

	/// Lazy workaround wrapper to interact with CDisplay::card_selection method by casting to CCard and vice versa
	[[nodiscard]] std::shared_ptr<CCardDeckable> card_selection_deckable ( const std::vector<std::shared_ptr<CCardDeckable>>&) const;

};


#endif //SEMESTRAL_CDISPLAY_H
