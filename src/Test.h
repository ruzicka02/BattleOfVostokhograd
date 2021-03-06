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
#include <filesystem>

/// Loads the starting deck, reduces the amount of cards and lets player select 3 cards.
void card_selection_t ();

/// Loads a deck and shop from CSV definition, shows on display and saves it once again. Compares the original and saved
/// version with an assert.
void CDeck_t ();

/// Basic test of various terminal capabilities - prints cards in their wchar and non-wchar versions.
void CDisplay_t ();

/// Prints a preview of the in-game board with "hidden cards" (not fitting to screen), deploys cards from hand to table on clicks.
void refresh_board_t ();

/// Tests the CPlayer::play_card method.
void play_card_t ();

/// Tests the load/save feature of CGame class.
void CGame_load_t();

/// Minimum actions required to trigger all ncurses-related memory leaks.
void mem_check_t();

#endif //SEMESTRAL_TEST_H