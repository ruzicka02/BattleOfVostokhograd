//
// Created by simon on 18.4.22.
//

#include "CDisplay.h"

#include <locale.h>
#include <ncurses.h>

CDisplay::CDisplay() {
	setlocale(LC_ALL, "");
	initscr();
	start_color();


	cbreak();
	noecho();
	curs_set(0);

	// gold (11... yellow)
	init_pair(1, COLOR_WHITE, COLOR_YELLOW + 8);

	// life
	init_pair(2, COLOR_WHITE, COLOR_RED);

	// general
	init_pair(3, COLOR_RED, COLOR_WHITE);

	// warcry
	init_pair(4, COLOR_GREEN, COLOR_WHITE);
	init_pair(5, COLOR_WHITE, COLOR_GREEN);

	// troop
	init_pair(6, COLOR_BLUE, COLOR_WHITE);
	init_pair(7, COLOR_WHITE, COLOR_BLUE);

	// game background
	init_pair(8, COLOR_WHITE, COLOR_CYAN + 16);


	bkgd(COLOR_PAIR(8));
}

CDisplay::~CDisplay() {

}

int CDisplay::menu() {
	return 0;
}

void CDisplay::refresh( std::shared_ptr<CPlayer> first, std::shared_ptr<CPlayer> second ) {

}

std::shared_ptr<CCard> CDisplay::card_selection( const CDeck& ) {
	return nullptr;
}