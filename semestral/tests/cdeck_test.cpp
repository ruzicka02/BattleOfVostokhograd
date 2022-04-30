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
card->print_card(5, pos);
pos += 25;
}

// CShop showcase
CShop shop;

input.open( "examples/decks/start_hand.csv" );
shop.load_deck(input);
input.close();
shop.print_shop(5, 0);

getch();

cout << "Total cards in deck: " << deck.cards().size() << endl;
//	ofstream output("examples/decks/start_hand_comp.csv");
//	deck.save_deck(output);

//	shop.save_deck(cout);