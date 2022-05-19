//
// Created by simon on 5.5.22.
//

#ifndef SEMESTRAL_TEST_H
#define SEMESTRAL_TEST_H

#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cassert>

#include "EAbility.h"
#include "card/CCardTroop.h"
#include "card/CCardWarcry.h"
#include "card/CCardGeneral.h"

#include "CDisplay.h"
#include "CShop.h"
#include "player/CPlayerHuman.h"

/// Loads the starting deck, reduces the amount of cards and lets player select 3 cards.
void card_selection_t ();

/// Loads a deck and shop from CSV definition, shows on display and saves it once again. Compares the original and saved
/// version with an assert.
void CDeck_t ();

/// Basic test of various terminal capabilities - prints cards in their wchar and non-wchar versions.
void CDisplay_t ();

/// Prints a preview of the in-game board with "hidden cards" (not fitting to screen), deploys cards from hand to table on clicks.
void refresh_board_t ();

/// Tests the CPlayer::play_card method
void play_card_t ();

#endif //SEMESTRAL_TEST_H