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
	CShop*						m_shop;
	CDisplay*					m_display;
public:
	/// Starts the game, creates instance of CDisplay.
	void init();

	/// Prepares the game for one player vs. AI
	void prepare_pve();

	/// Prepares the game for two players
	void prepare_pvp();

	/// Starts playing the game itself.
	void play();
};


#endif //SEMESTRAL_CGAME_H