//
// Created by simon on 1.5.22.
//

mvprintw(5, 0, "Before card selection:" );
init_screen.info_bar("Press any key to continue." );

CDeck deck;
ifstream input( "examples/decks/start_hand.csv" );
deck.load_deck(input);
input.close();

deck.pop_top()->print_card(10, 10);
deck.pop_top()->print_card(10, 35);
deck.pop_top();
deck.pop_top();
deck.pop_top();

refresh();
getch();

CDeck selected;

selected.insert( init_screen.card_selection(deck) );
selected.insert( init_screen.card_selection(deck) );
selected.insert( init_screen.card_selection(deck) );

mvprintw(5, 0, "Your selected cards:" );
init_screen.info_bar("Press any key to continue." );

const int y = 15, card_diff = 22;
int x = 0;

for ( auto card : selected.cards() ) {
card->print_card(y, x);
x += card_diff;
}

getch();