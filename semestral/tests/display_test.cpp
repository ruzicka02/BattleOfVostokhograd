// Tests capabilities of the terminal display (color modes, printing wide chars with ncurses etc.)
// Created by simon on 30.4.22.
//

CDisplay screen;

if ( can_change_color() ) printw("Can change color\n");
if ( has_colors() ) printw("Has colors\n");
printw("Normal non-wchar cards\n");

refresh();

// CCard showcase
auto card_t = CCardTroop("Name", "Sample description", 1, 2, 3, 4, 5, null);
auto card_w = CCardWarcry("Warcry Name", "Another sample\ndescription", 1, 2, 3, 4, steal);
auto card_g = CCardGeneral("General Windishgratz", "This general is the best general in the world", 50, 2, 3, 4, 1, null);

card_t.print_card(5, 0);
card_w.print_card(5, 25);
card_g.print_card(5, 50);

card_g.change_life(-8);
card_g.print_card(5, 75);

mvprintw(22, 0, "Cards utilizing wchar capabilities\n");

card_t.print_card_wide(25, 0);
card_w.print_card_wide(25, 25);
card_g.print_card_wide(25, 50);

card_g.change_life(-8);
card_g.print_card(25, 75);

getch();