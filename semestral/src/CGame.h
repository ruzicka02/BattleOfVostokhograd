//
// Created by simon on 18.4.22.
//

#ifndef SEMESTRAL_CGAME_H
#define SEMESTRAL_CGAME_H

#include <memory>

#include "CPlayer.h"
#include "CShop.h"
#include "CDisplay.h"

/// High-level class for managing the creation and successful termination of the game. Handles the way players change turns.
class CGame {
protected:
	std::shared_ptr<CPlayer> 	m_first;
	std::shared_ptr<CPlayer> 	m_second;
	CShop						m_shop;
	CDisplay					m_display;

	/// Prepares the game for one player vs. AI
	void prepare_pve();

	/// Prepares the game for two players
	void prepare_pvp();
public:
	/// Starts the game, automatically creates instance of CDisplay and an empty CShop.
	CGame() = default;

	/// Opens the menu using CDisplay::menu, lets player select action.
	void start();

	/// Starts playing the game itself.
	void play();

	/// Saves the game into file with given name.
	/// @return True on successful operation (no IO error etc)
	bool save_game(std::string name);

	/// Loads the game from file with given name.
	/// @return True on successful operation (no IO error etc)
	bool load_game(std::string name);

	/// Returns names of all game saves in the inherently used directory examples/saves/
	std::vector<std::string> get_saved_games();
};


#endif //SEMESTRAL_CGAME_H
