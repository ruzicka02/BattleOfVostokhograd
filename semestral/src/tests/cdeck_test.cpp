// Tests various aspects of CDeck and CShop class, mostly import and export to and from file
// Created by simon on 30.4.22.
//

CDisplay screen;

CDeck deck;
ifstream input( "examples/decks/start_hand.csv" );
deck.load_deck(input);
input.close();

int pos = 25;
for ( auto card : deck.cards() ) {
card->print_card(30, pos);
pos += 25;
}

// CShop showcase
CShop shop;

input.open( "examples/decks/start_hand.csv" );
shop.load_deck(input, true);
input.close();
shop.print_shop(5, 0);

getch();

endwin();

cout << "Total cards in deck: " << deck.count() << endl;

input.open( "examples/decks/start_hand.csv" );
stringstream s_file;
s_file << input.rdbuf();
input.close();

ostringstream s_processed;
deck.save_deck(s_processed);

//cout << s_processed.str() << endl;
//cout << s_file.str() << endl;

assert(s_processed.str() == s_file.str());

shop.save_deck(cout);