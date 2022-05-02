//
// Created by simon on 1.5.22.
//

init_screen.context_bar("Before card selection:" );
init_screen.info_bar("Press any key to continue." );

CDeck deck;
ifstream input( "examples/decks/start_hand.csv" );
deck.load_deck(input);
input.close();

deck.pop_top()->print_card(10, 4);
deck.pop_top()->print_card(10, 26);
deck.pop_top()->print_card(10, 48);

refresh();
getch();

CDeck selected;
std::shared_ptr<CCard> choice;

init_screen.context_bar("0/3 selected");
choice = init_screen.card_selection(deck.cards());
selected.insert( choice );
deck.remove( choice );

init_screen.context_bar("1/3 selected");
choice = init_screen.card_selection(deck.cards());
selected.insert( choice );
deck.remove( choice );

init_screen.context_bar("2/3 selected");
choice = init_screen.card_selection(deck.cards());
selected.insert( choice );
deck.remove( choice );

init_screen.context_bar("Your selected cards:" );
init_screen.info_bar("Press any key to continue." );

const int y = 10, card_diff = 22;
int x = 4;

for ( auto card : selected.cards() ) {
card->print_card(y, x);
x += card_diff;
}

getch();