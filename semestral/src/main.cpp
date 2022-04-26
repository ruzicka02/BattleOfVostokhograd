#include <iostream>
#include <ncurses.h>
#include <locale.h>

#include "CCardTroop.h"

using namespace std;

int main () {

//	cout << "Battle of Vostokhograd: The Card RPG\nSimon Ruzicka, 2022" << endl;

	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	start_color();
	printw("Battle of Vostokhograd: The Card RPG\nSimon Ruzicka, 2022");

	refresh();

	auto card = CCardTroop("Name", "Sample description", 1, 2, 3, 4, 5);
	card.print_card(2, 2);

	getch();
	endwin();



	return 0;
}
